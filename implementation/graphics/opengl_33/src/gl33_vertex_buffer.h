#ifndef GL33_VERTEX_BUFFER_H
#define GL33_VERTEX_BUFFER_H

#include <graphics/vertex_buffer.h>
#include <core/buffer_layout.h>
#include <core/shared_id.h>


namespace undicht {

    namespace graphics {

        namespace gl33 {

            class VertexBuffer : public implementation::VertexBuffer  {
                public:
                    // data & non api functions

                    core::SharedID m_vbo_id = 0;
                    core::SharedID m_ebo_id = 0;
                    core::SharedID m_vao_id = 0;
                    unsigned int m_size = 0;

                    bool m_uses_indices = false;
                    unsigned int m_indices_size = 0;

                    core::BufferLayout m_layout;

                    void resize(unsigned int size);
                    void resizeIndexBuffer(unsigned int size);

                    void bind();


            public:
                // vertex data

                virtual void setData(const std::vector<float>& data, unsigned int offset = 0);
                virtual void setData(const void* data, unsigned int size, unsigned int offset = 0);

                virtual void getData(std::vector<float>& data, unsigned int num_floats, unsigned int offset = 0);
                virtual void getData(void* data, unsigned int size, unsigned int offset = 0); /// data should have at least #size bytes reserved
            public:
                // additional vertex related data

                virtual void setLayout(const core::BufferLayout& layout);

                virtual unsigned int getSize(); /// returns the number of bytes stored in the buffer
                virtual unsigned int getVertexSize(); /// returns the size of one vertex
                virtual const core::BufferLayout& getLayout(); /// returns the layout of the stored data


            public:
                // indices

                virtual void setIndexData(const std::vector<int>& data, unsigned int offset = 0);
                virtual void setIndexData(const void* data, unsigned int size, unsigned int offset = 0);

                virtual void getIndexData(std::vector<int>& data, unsigned int num_indices, unsigned int offset = 0);
                virtual void getIndexData(void* data, unsigned int size, unsigned int offset = 0); /// data should have at least #size bytes reserved

            public:
                // additional index related data

                virtual unsigned int getIndexBufferSize(); /// returns the number of bytes stored in the indices buffer

                virtual void setUsesIndices(bool use_indices = true);
                virtual bool getUsesIndices();


                    VertexBuffer();
                    virtual ~VertexBuffer();

            };

        } // gl33

    } // graphics

} // undicht

#endif // GL33_VERTEX_BUFFER_H
