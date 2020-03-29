#include <glad/glad.h>

#include "gl33_renderer.h"
#include <core/event_logger.h>

using namespace undicht::core;

namespace undicht {

    namespace graphics {

        namespace gl33 {

            bool Renderer::s_depth_test_enabled = false;
            bool Renderer::s_culling_enabled = false;

            Renderer::Renderer() {
                //ctor
            }

            Renderer::~Renderer() {
                //dtor
            }

            void Renderer::submit(graphics::VertexBuffer* vbo) {

                m_current_vbo = (gl33::VertexBuffer*)vbo->m_shared_lib_object;


            }

            void Renderer::submit(graphics::Shader* shader) {

                m_current_shader = (gl33::Shader*)shader->m_shared_lib_object;

            }

            void Renderer::submit(graphics::FrameBuffer* fbo) {

                if(fbo) {

                    m_current_fbo = (gl33::FrameBuffer*)fbo->m_shared_lib_object;
                    m_current_fbo->checkStatus();
                } else {
                    m_current_fbo = 0;
                }

            }

            void Renderer::clearFramebuffer(float r, float g, float b, float alpha) {

                if(m_current_fbo){
                    m_current_fbo->clearAttachments();
                } else {
                    FrameBuffer::bind(0);
                    glClearColor(r,g,b,alpha);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                }


            }


            void Renderer::draw(unsigned int instance_count) {

                if(m_current_shader) {

                    m_current_shader->bind();

                } else {

                    EventLogger::storeNote(Note(UND_ERROR, "ERROR: draw call failed, no shader submitted", UND_CODE_ORIGIN));
                    return;
                }

                if(m_current_vbo) {

                    m_current_vbo->bind();
                } else {

                    EventLogger::storeNote(Note(UND_ERROR, "ERROR: draw call failed, no vertex buffer submitted", UND_CODE_ORIGIN));
                    return;
                }

                useFbo();

                // std::cout << "drawing " << m_current_vbo->getSize() / m_current_vbo->getVertexSize() << " vertices" << "\n";


                if(instance_count == 1) {

                    glDrawArrays(GL_TRIANGLES, 0, m_current_vbo->getSize() / m_current_vbo->getVertexSize());

                } else {

                    glDrawArraysInstanced(GL_TRIANGLES, 0, m_current_vbo->getSize() / m_current_vbo->getVertexSize(), instance_count);

                }

            }

            void Renderer::setViewport(int width, int height, int offset_x, int offset_y){

                glViewport(offset_x, offset_y, width, height);
            }

            void Renderer::enableDepthTest(bool enable){


                if(s_depth_test_enabled != enable) {

                    if(enable) {
                        glEnable(GL_DEPTH_TEST);
                    } else {
                        glDisable(GL_DEPTH_TEST);
                    }

                    s_depth_test_enabled = enable;
                }



            }

            void Renderer::enableBackFaceCulling(bool enable){

                if(s_culling_enabled != enable) {

                    if(enable) {
                        glEnable(GL_CULL_FACE);
                    } else {
                        glDisable(GL_CULL_FACE);
                    }

                    s_culling_enabled = enable;
                }

            }




                        /////////////////////////////////////////////////// opengl only functions //////////////////////////////////////////


            void Renderer::useFbo() {
                /// binding the submitted fbo

                if(m_current_fbo) {
                    m_current_fbo->bind();
                } else {
                    // using the default framebuffer
                    FrameBuffer::bind(0);
                }

            }

            /////////////////////////////////////////// functions to load objects from the shared lib //////////////////////////


            SHARED_LIB_EXPORT implementation::Renderer* createRenderer() {

                return new gl33::Renderer;
            }

            SHARED_LIB_EXPORT void copyRenderer(implementation::Renderer* c, implementation::Renderer* o) {
                //std::cout << "copying rendering info" << "\n";
                ((gl33::Renderer*)c)->m_current_vbo = ((gl33::Renderer*)o)->m_current_vbo;
                ((gl33::Renderer*)c)->m_current_shader = ((gl33::Renderer*)o)->m_current_shader;
                ((gl33::Renderer*)c)->m_current_fbo = ((gl33::Renderer*)o)->m_current_fbo;
            }

            SHARED_LIB_EXPORT void deleteRenderer(implementation::Renderer* renderer) {

                delete renderer;
            }

            // static function callers

            SHARED_LIB_EXPORT void setViewport(int width, int height, int offset_x, int offset_y){

                Renderer::setViewport(width, height, offset_x, offset_y);
            }

            SHARED_LIB_EXPORT void enableDepthTest(bool enable){

                Renderer::enableDepthTest(enable);
            }

            SHARED_LIB_EXPORT void enableBackFaceCulling(bool enable){

                Renderer::enableBackFaceCulling(enable);
            }


        } // gl33

    } // graphics

} // undicht


