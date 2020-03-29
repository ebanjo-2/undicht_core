#include <glad/glad.h>
#include "gl33_uniform.h"
#include <core/shared_lib.h>


namespace undicht {

    namespace graphics {

        namespace gl33 {


            Uniform::Uniform() {
                //ctor
            }

            Uniform::~Uniform() {
                //dtor
                if(m_memory_watcher.deleteUser()) {
                    if(m_data && (!m_data_copied))
                        delete[] m_data;
                }
                m_data = 0;

                if(m_ubo_id.removeUser()) {
                    glDeleteBuffers(1, &m_ubo_id.m_id);
                }
            }


            void Uniform::setData(const void* data, int type, bool copy_data) {
                /** the uniform stores a single type,
                * see core/types.h for options */

                m_layout.m_types = std::vector<int>(type);
                int type_size = core::getSizeOfType(type);

                if(m_data && (!m_data_copied)) {
                    if(m_memory_watcher.deleteUser())
                        delete[] m_data;

                }

                if(copy_data) {

                    if(core::getSizeOfType(m_type) != type_size) {

                        m_memory_watcher.createNewUserCount();
                        m_data = new char[type_size];

                    }

                    std::copy((char*)data, ((char*)data) + type_size, m_data);

                } else {

                    m_data = (char*)data;
                }


                m_type = type;
                m_data_copied = copy_data;

            }

            void Uniform::setData(const void* data, core::BufferLayout layout, int num_of_elements) {
                /** stores the data in a buffer accessable in the shader */
                // once again, using learnopengl.com as the source

                if(!m_ubo_id) {
                    // creating the ubo
                    unsigned int temp_id;
                    glGenBuffers(1, &temp_id);
                    m_ubo_id.setID(temp_id);

                }

                glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_id);
                glBufferData(GL_UNIFORM_BUFFER, layout.getTotalSize() * num_of_elements, data, GL_STATIC_DRAW);

                glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo_id, 0, num_of_elements * layout.getTotalSize());

            }

            void Uniform::setName(const std::string& name) {
                /** sets the name with which the uniforms data can be accessed in the shader */

                m_name = name;

            }

            const std::string& Uniform::getName() const {

                return m_name;
            }


            int Uniform::getType() const {

                return m_type;
            }

            const void* Uniform::getData() const {

                return m_data;
            }

            const core::BufferLayout& Uniform::getLayout() const {

                return m_layout;
            }


            /////////////////////////////////////////////// functions to export objects from the shared lib ////////////////////////////

            SHARED_LIB_EXPORT implementation::Uniform* createUniform() {

                return new gl33::Uniform;
            }


            SHARED_LIB_EXPORT void copyUniform(implementation::Uniform* c, implementation::Uniform* o) {

                Uniform* c_uniform = (Uniform*)c;

                if(c_uniform->m_ubo_id.removeUser()){
                    glDeleteBuffers(1, &c_uniform->m_ubo_id.m_id);
                }

                *c_uniform = *(Uniform*)o;
            }

            SHARED_LIB_EXPORT void deleteUniform(implementation::Uniform* uniform) {

                delete (gl33::Uniform*)uniform;
            }

        } // gl33

    } // graphics

} // undicht
