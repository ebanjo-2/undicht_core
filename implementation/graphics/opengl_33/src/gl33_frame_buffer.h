#ifndef GL33_FRAME_BUFFER_H
#define GL33_FRAME_BUFFER_H

#include <graphics/frame_buffer.h>
#include "gl33_texture.h"
#include <core/shared_id.h>

namespace undicht {

    namespace graphics {

        namespace gl33 {

            class FrameBuffer : public implementation::FrameBuffer {

                public:
                    // opengl only members / functions

                    int m_width = 0;
                    int m_height = 0;

                    core::SharedID m_id;
                    int m_type; // will always be GL_FRAMEBUFFER

                    std::vector<int> m_attachment_types;
                    std::vector<gl33::Texture*> m_attachments;

                    virtual int getColorOutputCount();

                    virtual void updateColorOutputs();

                    virtual void checkStatus();

                    virtual void bind();

                    static void bind(int id);

                public:

                    /** setting the size of the framebuffer and all of its attachments */
                    virtual void setSize(int width, int height);

                    virtual void getSize(int& width, int& height);

                    /** @param texture: the framebuffer can only be used while the texture object exists
                    * @param texture: it should have a pixel layout set before attachment, if not, default 24 bit rgb is going to be used for color attachments
                    * @param attachment_type: UND_COLOR_ATTACHMENT, UND_DEPTH_ATTACHMENT_WRITE_ONLY or UND_DEPTH_ATTACHMENT_READ_AND_WRITE */
                    virtual void addAttachment(graphics::Texture& texture, int attachment_type);

                    /** @brief removes the attachment from the framebuffer */
                    virtual void removeAttachment(graphics::Texture& texture);

                    virtual void clearAttachments();


                public:


                    FrameBuffer();
                    virtual ~FrameBuffer();

            };

        } // gl33

    } // graphics

} // undicht


#endif // GL33_FRAME_BUFFER_H
