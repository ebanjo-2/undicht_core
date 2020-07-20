#include "vertex_buffer.h"

namespace undicht {

    namespace graphics {

        SHARED_LIB_DEF_BASE_CLASS(VertexBuffer, createVertexBuffer, copyVertexBuffer, deleteVertexBuffer);

        SHARED_LIB_API_IMPL(VertexBuffer::VertexBuffer()) {
            //ctor
        }

        SHARED_LIB_API_IMPL(VertexBuffer::~VertexBuffer()) {
            //dtor
        }


        //////////////////////////////////////////////// vertex data ////////////////////////////////////////////////


        SHARED_LIB_API_IMPL(void VertexBuffer::setData(const std::vector<float>& data, unsigned int offset)) {
            /** stores the content of data in the vertex buffer
            * @param offset: (in bytes) at what point in the buffer the data should be stored (0: first byte of first vertex) */

            m_shared_lib_object->setData(data,offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::setData(const void* data, unsigned int size, unsigned int offset)) {
            /** @param size: (in bytes) the size of the data to copy from the data buffer */

            m_shared_lib_object->setData(data,size,offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::getData(std::vector<float>& data, unsigned int num_floats, unsigned int offset)) {
            /** retrieve the data from the vertex buffer and store it in the vector
            * @param num_float: how many floats to copy from the buffer (not vertices !)
            * @param offset: (in bytes) at what point in the buffer to start copying */

            m_shared_lib_object->getData(data,num_floats,offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::getData(void* data, unsigned int size, unsigned int offset)) {
            /** data should have at least #size bytes reserved */

            m_shared_lib_object->getData(data,size,offset);
        }

        //////////////////////////////////////////////// additional vertex related data ////////////////////////////////////////////////

        SHARED_LIB_API_IMPL(void VertexBuffer::setLayout(const core::BufferLayout& layout)) {
            /** determines how many and what types of components belong to a vertex
            * also determines how the data can be accessed in a vertex shader
            * example for a vertex: 3D position, 2D texture coordinate, 3D normal
            * translates into layout: UND_VEC3F, UND_VEC2F, UND_VEC3F */

            m_shared_lib_object->setLayout(layout);
        }

        SHARED_LIB_API_IMPL(unsigned int VertexBuffer::getSize()) {
            /** returns the number of bytes stored in the buffer */

            return m_shared_lib_object->getSize();
        }

        SHARED_LIB_API_IMPL(unsigned int VertexBuffer::getVertexSize()) {
            /** returns the size of one vertex */

            return m_shared_lib_object->getVertexSize();
        }

        SHARED_LIB_API_IMPL(const core::BufferLayout& VertexBuffer::getLayout()) {
            /** returns the layout of the stored vertices */

            return m_shared_lib_object->getLayout();
        }

        //////////////////////////////////////////////// indices ////////////////////////////////////////////////

        SHARED_LIB_API_IMPL(void VertexBuffer::setIndexData(const std::vector<int>& data, unsigned int offset)) {
            /** @brief an index array determines the order in which vertices are read from the vertex buffer
            * @param offset: (in bytes) the position to copy the data to */

            m_shared_lib_object->setIndexData(data, offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::setIndexData(const void* data, unsigned int size, unsigned int offset)) {
            /** @param size: the size (in bytes) of index data to copy from the data buffer */

            m_shared_lib_object->setIndexData(data, size, offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::getIndexData(std::vector<int>& data, unsigned int num_indices, unsigned int offset)) {
            /** @brief retrieve data from the index array
            * @param num_indices: number of indices to copy
            * @param offset: (in bytes) position in the index array to copy from */

            m_shared_lib_object->getIndexData(data, num_indices, offset);
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::getIndexData(void* data, unsigned int size, unsigned int offset)) {
            /** @param data should have at least #size bytes reserved
            * @param the number of bytes to copy (number of indices * sizeof(int)) */

            m_shared_lib_object->getIndexData(data, size, offset);
        }

        //////////////////////////////////////////////// additional index related data ////////////////////////////////////////////////


        SHARED_LIB_API_IMPL(unsigned int VertexBuffer::getIndexBufferSize()) {
            /** @return the number of bytes stored in the indices buffer */

            return m_shared_lib_object ->getIndexBufferSize();
        }

        SHARED_LIB_API_IMPL(void VertexBuffer::setUsesIndices(bool use_indices)) {

            m_shared_lib_object->setUsesIndices(use_indices);
        }

        SHARED_LIB_API_IMPL(bool VertexBuffer::getUsesIndices()) {

            return m_shared_lib_object->getUsesIndices();
        }


    } // graphics

} // undicht
