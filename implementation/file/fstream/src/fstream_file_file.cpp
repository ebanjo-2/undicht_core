#include "fstream_file_file.h"
#include <sys/stat.h> // to check if a file exists
#include <stdio.h> // to delete files

#include <core/event_logger.h>

using namespace undicht::core;

/// the implementation of the "file" class using fstream, which is a default c++ class

namespace undicht {

    namespace file {

        namespace fstream_file {


            File::File() {

            }

            File::~File() {

            }

            ////////////////////////////////////// opening / closing files ////////////////////////////////////


            bool File::open(const std::string& file_name) {
                /** opens a file from the hard drive
                * @return whether or not the file could be opened */

                m_file_name = file_name;

                // checking if the file already exists
                // source https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
                struct stat buffer;

                if((stat (file_name.c_str(), &buffer) == 0)) {

                    m_file_size = -1; // not open
                    return false;
                }

                // opening the file
                m_file_stream.open(file_name); // open for both input and output


                // getting the size of the file opened
                m_file_stream.seekg(std::fstream::end);
                m_file_size = getPosition();
                setPosition(0);

                return false;
            }


            void File::close() {
                /// to be called when the file is no longer used

                m_file_stream.close();
            }


            void File::createFile() {
                /// initializes a File with the file_name provided with the open() function

                if(!m_file_stream.is_open()) {

                    // creating the file
                    m_file_stream.open(m_file_name); // open for both input and output


                    // getting the size of the file opened
                    m_file_stream.seekg(std::fstream::end);
                    m_file_size = getPosition();
                    setPosition(0);

                }

            }


            void File::deleteFile() {
                /// deletes the file

                close();
                if(remove(m_file_name.data()) != 0 ) {
                    // something went wrong

                    EventLogger::storeNote(Note(UND_ERROR, "FILE:ERROR: failed to delete file " + m_file_name, UND_CODE_ORIGIN));

                }
            }


            const std::string& File::getName() const {
                /// @return the name of the file opened

                return m_file_name;
            }


            //////////////////////////////////// reading from the file ////////////////////////////////////


            std::string& File::getLine(std::string& line) {
                /// loads the next line from the file (current cursor pos till next line ending)

                std::getline(m_file_stream, line);

                return line;
            }


            std::string File::getLine() {
                // the string containing the line content is local
                std::string line;

                return getLine(line);
            }


            std::string& File::getLineWithStart(std::string& line, const std::string& start) {
                /**  @return the line if it starts with the string provided as the second param
                * if not, the string will be erased, the "cursor" will still be moved */

                // getting the line
                getLine(line);

                // checking if it starts with the start
                if(line.substr(0, start.length()).compare(start)) {
                    // line does not start with the start string
                    line.clear();
                }

                return line;
            }


            std::string File::getLineWithStart(const std::string& start) {

                std::string line;
                getLineWithStart(line, start);

                return line;
            }


            char File::getChar() {
                /// @return the next character in the file

                char c;
                m_file_stream.get(c);

                return c;
            }


            //////////////////////////////////// writing to the file ////////////////////////////////////


            void File::eraseAll() {
                /// erases the content from the file

                close();
                m_file_stream.open(m_file_name, std::ofstream::out | std::ofstream::in |std::ofstream::trunc); // deletes all its content
                m_file_size = 0;
            }


            void File::write(const std::string& str) {
                /**  writes the string to the file
                * the "cursor" will be moved behind the inserted string */

            }


            //////////////////////////////////// getting information about the state of the file ////////////////////////////////////


            size_t File::getPosition() {
                /** @return an index into the file
                * representing the position of the "cursor" which is used to read / write */

                return m_file_stream.tellg();
            }

            void File::setPosition(const size_t& position) {

                m_file_stream.seekg(position);
            }


            bool File::eof()  const {
                /** @return whether the "cursor" has reached the end of the file */

                return m_file_stream.eof();
            }


            size_t File::getSize()  const {
                /** @return the size of the file in bytes (equal to the number of characters) */

                return m_file_size;
            }



            //////////////////////////////////////// functions to load objects from the shared library ///////////////////////////////////////


            const fstream_file::File& File::operator= (const fstream_file::File& o) {
                // needed because of the fstream object

                open(o.m_file_name);
                // tellg for some reasen is not const, elsewise the position would also be copied
                return *this;
            }


            SHARED_LIB_EXPORT implementation::File*createFile() {

                return new fstream_file::File;
            }

            SHARED_LIB_EXPORT void copyFile(implementation::File* c, implementation::File* o) {

                *(File*)c = *(File*)o;
            }

            SHARED_LIB_EXPORT void deleteFile(implementation::File* object) {

                delete (File*)object;
            }


        } // fstream_file

    } // file

} // undicht
