#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <core/shared_lib_class.h>
#include <core/buffer_layout.h>
#include <vector>


namespace undicht {

    namespace graphics {

        SHARED_LIB_DECL_BASE_CLASS(VertexBuffer, VertexBufferBase, createVertexBuffer, copyVertexBuffer, deleteVertexBuffer);


        SHARED_LIB_CLASS(class VertexBuffer : public VertexBufferBase {
                /** a class that can hold multiple vertices which can be used to build meshes */
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

                /// setting index data will also enable the usage of that data
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

        };)

    } // graphics

} // undicht

#endif // VERTEX_BUFFER_H
