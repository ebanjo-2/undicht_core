#include <glad/glad.h>
#include "gl33_shader.h"
#include "gl_tools.h"
#include <core/event_logger.h>
#include "gl33_texture.h"
#include "gl33_uniform.h"


using namespace undicht::core;

namespace undicht {

    namespace graphics {

        namespace gl33 {

            unsigned int bound_shader = 0;

            Shader::Shader() {

                // creating the opengl shading program
                m_id = glCreateProgram();

            }

            Shader::~Shader() {

                if(m_id.removeUser()) {
                    glDeleteProgram(m_id);
                }

            }


            void Shader::loadSource(const std::string& source) {

                std::string vert_src, frag_src, geom_src;

                splitShaderSrc(source, vert_src, frag_src, geom_src);


                // creating the opengl shaders
                unsigned int vert_shader = createGLShader(vert_src, GL_VERTEX_SHADER);
                unsigned int frag_shader = createGLShader(frag_src, GL_FRAGMENT_SHADER);
                unsigned int geom_shader = createGLShader(geom_src, GL_GEOMETRY_SHADER);


                if(vert_shader) // there has to be one...
                    glAttachShader(m_id, vert_shader);

                if(frag_shader)
                    glAttachShader(m_id, frag_shader);

                if(geom_shader)
                    glAttachShader(m_id, geom_shader);

                glLinkProgram(m_id);

                glDeleteShader(vert_shader);
                glDeleteShader(frag_shader);
                glDeleteShader(geom_shader);

                undCheckGLError(UND_CODE_ORIGIN);

            }

            void Shader::loadUniform(const graphics::Uniform& u) {
                // loading the uniform to the shader

                //undCheckGLError(UND_CODE_ORIGIN);

                bind();

                gl33::Uniform* real_u = (gl33::Uniform*)u.m_shared_lib_object;

                if(!real_u->m_ubo_id) {

                    int location = glGetUniformLocation(m_id, u.getName().data());

                    int type = u.getType();


                    if(type == UND_INT) {
                        glUniform1i(location, *(int*)u.getData());
                    } else if(type == UND_FLOAT ) {
                        glUniform1f(location, *(float*)u.getData());
                    } else if(type == UND_VEC4F) {
                        glUniform4fv(location, 1, (float*)u.getData());
                    } else if(type == UND_VEC3F) {
                        glUniform3fv(location, 1, (float*)u.getData());
                    } else if(type == UND_VEC3I) {
                        glUniform3iv(location, 1, (int*)u.getData());
                    } else if(type == UND_VEC2F) {
                        glUniform2fv(location, 1, (float*)u.getData());
                    } else if(type == UND_MAT4F) {
                        glUniformMatrix4fv(location, 1, GL_FALSE, (float*)u.getData());
                    } else if(type == UND_MAT3F) {
                        glUniformMatrix3fv(location, 1, GL_FALSE, (float*)u.getData());
                    }

                } else {

                    //undCheckGLError(UND_CODE_ORIGIN);

                    // ubo (using the method from learnopengl.com, i have no idea how and if this works
                    // since i am to lazy rn to read and understand everything described there about ubos)

                    unsigned int uniform_block_index = glGetUniformBlockIndex(m_id, u.getName().data());

                    glUniformBlockBinding(m_id, uniform_block_index, 0);
                }



            }

            void Shader::loadTexture(const graphics::Texture& t) {

                gl33::Texture* real_texture = (gl33::Texture*)t.m_shared_lib_object;

                if(real_texture->m_type && real_texture->m_id) {
                    // binding the texture and setting the sampler uniform in the shader
                    real_texture->bind();
                    int texture_id = getTextureID(real_texture->m_name);
                    graphics::Uniform u;
                    u.setData(&texture_id, UND_INT);
                    u.setName(real_texture->m_name);
                    loadUniform(u);
                }


            }


            /////////////////////////////////////// non api functions ///////////////////////////////////////

            int Shader::getTextureID(const std::string& texture_name) {

                // checking if the texture name already has an id associated with it
                for (int i = 0; i < m_textures.size(); i++) {

                    if(!m_textures.at(i).compare(texture_name)) {

                        return i;
                    }

                }


                // adding the texture to the list of textures loaded to the shader
                m_textures.push_back(texture_name);

                return m_textures.size() - 1;
            }


            void Shader::bind() {

                if(m_id != bound_shader) {

                    glUseProgram(m_id);
                    bound_shader = m_id;

                }

            }

            void Shader::bind(int id) {

                if(id != bound_shader) {

                    glUseProgram(id);
                    bound_shader = id;

                }

            }

            void Shader::splitShaderSrc(const std::string& source, std::string& vert_src, std::string& frag_src, std::string& geom_src ) {
                /// splits the shader source into glsl shaders

                size_t vert_start = source.find("#vertex");
                size_t frag_start = source.find("#fragment");
                size_t geom_start = source.find("#geometry");
                size_t source_end = source.size();

                if(geom_start != std::string::npos) {
                    geom_src = source.substr(geom_start + 9, source_end - geom_start - 9);
                } else {
                    geom_start = source_end;
                }

                vert_src = source.substr(vert_start + 7, frag_start - vert_start - 7);
                frag_src = source.substr(frag_start + 9, geom_start - frag_start - 9);


            }

            unsigned int Shader::createGLShader(const std::string& source, unsigned int type) {

                unsigned int shader_id = glCreateShader(type);
                const char* src = source.data();
                const int src_size = source.length();

                if(!src_size)
                    return 0;

                glShaderSource(shader_id, 1, &src, &src_size);
                glCompileShader(shader_id);

                //check if compiling the Shader was successfull
                int  success;
                char info_log[512];
                glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

                if(!success) {
                    glGetShaderInfoLog(shader_id, 512, NULL, info_log);
                    EventLogger::storeNote(Note(UND_ERROR, toStr("ERROR: SHADER: ") + toStr(info_log), UND_CODE_ORIGIN));
                    return 0;
                }

                return shader_id;
            }


            SHARED_LIB_EXPORT implementation::Shader* createShader() {

                return new gl33::Shader;
            }

            SHARED_LIB_EXPORT void copyShader(implementation::Shader* c, implementation::Shader* o) {

                Shader* c_shader = (Shader*)c;

                if(c_shader->m_id.removeUser()) {
                    glDeleteProgram(c_shader->m_id);
                }

                *c_shader = *(Shader*)o;
            }

            SHARED_LIB_EXPORT void deleteShader(implementation::Shader* shader) {

                delete shader;
            }


        } // gl33

    } // graphics

} // undicht



