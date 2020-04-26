#include <file/file.h>
#include <iostream>


namespace undicht {

    namespace file {

        SHARED_LIB_DEF_BASE_CLASS( File, createFile, copyFile, deleteFile);

        SHARED_LIB_API_IMPL(File::File()) {
            // ctor
        }

        SHARED_LIB_API_IMPL(File::File(const std::string& file_name)) {

            open(file_name);
        }

        SHARED_LIB_API_IMPL(File::~File()) {
            // dtor
        }

        //////////////////////// opening / closing files /////////////////////////////////


        SHARED_LIB_API_IMPL(bool File::open(const std::string& file_name)) {
            /// opens a file from the hard drive
            m_shared_lib_object->open(file_name);
        }


        SHARED_LIB_API_IMPL(void File::close()) {
            /// to be called when the file is no longer used

            m_shared_lib_object->close();
        }





        SHARED_LIB_API_IMPL(void File::createFile()) {
            /// initializes a File with the file_name provided with the open() function

            m_shared_lib_object->createFile();
        }


        SHARED_LIB_API_IMPL(void File::deleteFile()) {
            /// deletes the file

            m_shared_lib_object->deleteFile();
        }


        SHARED_LIB_API_IMPL(const std::string& File::getName() const) {
            /// @return the name of the file opened

            return m_shared_lib_object->getName();
        }


        /////////////////////////////////// reading from the file //////////////////////////////////////


        SHARED_LIB_API_IMPL(std::string& File::getLine(std::string& line)) {
            /// loads the next line from the file (current cursor pos till next line ending)

            return m_shared_lib_object->getLine(line);
        }

        SHARED_LIB_API_IMPL(std::string File::getLine()) {

            return m_shared_lib_object->getLine();
        }


        SHARED_LIB_API_IMPL(std::string& File::getLineWithStart(std::string& line, const std::string& start)) {
            /**  @return the line if it starts with the string provided as the second param
            * if not, the string will be erased, the "cursor" will still be moved */

            return m_shared_lib_object->getLineWithStart(line, start);
        }

        SHARED_LIB_API_IMPL(std::string File::getLineWithStart(const std::string& start)) {

            return m_shared_lib_object->getLineWithStart(start);
        }


        SHARED_LIB_API_IMPL(char File::getChar()) {
            /// @return the next character in the file

            return m_shared_lib_object->getChar();
        }


        /////////////////////////////////// writing to the file ///////////////////////////////////


        SHARED_LIB_API_IMPL(void File::eraseAll()) {
            /// erases the content from the file

            m_shared_lib_object->eraseAll();
        }


        SHARED_LIB_API_IMPL(void File::write(const std::string& str)) {
            /**  writes the string to the file
            * the "cursor" will be moved behind the inserted string */

            m_shared_lib_object->write(str);
        }


        /////////////////////////////////// getting information about the state of the file ///////////////////////////////////


        SHARED_LIB_API_IMPL(size_t File::getPosition()) {
            /** @return an index into the file
            * representing the position of the "cursor" which is used to read / write */

            return m_shared_lib_object->getPosition();
        }


        SHARED_LIB_API_IMPL(void File::setPosition(const size_t& position)) {

            m_shared_lib_object->setPosition(position);
        }


        SHARED_LIB_API_IMPL(bool File::eof() const) {
            /** @return whether the "cursor" has reached the end of the file */

            return m_shared_lib_object->eof();
        }


        SHARED_LIB_API_IMPL(size_t File::getSize() const) {
            /** @return the size of the file in bytes (equal to the number of characters) */

            return m_shared_lib_object->getSize();
        }

    } // file

} // undicht
