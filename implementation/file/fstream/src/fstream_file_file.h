#ifndef FSTREAM_FILE_FILE_H
#define FSTREAM_FILE_FILE_H

#include <file/file.h>
#include <string>
#include <fstream>

namespace undicht {

    namespace file {

        namespace fstream_file {

            class File : public implementation::File {

                public:

                    std::fstream m_file_stream;
                    std::string m_file_name;

                    size_t m_file_size = -1; // -1 for not open

                    const fstream_file::File& operator= (const fstream_file::File& o);

                public:
                    // opening / closing files

                    /** opens a file from the hard drive
                    * @return whether or not the file could be opened */
                    virtual bool open(const std::string& file_name);

                    /// to be called when the file is no longer used
                    virtual void close();

                    /// initializes a File with the file_name provided with the open() function
                    virtual void createFile();

                    /// deletes the file
                    virtual void deleteFile();

                    /// @return the name of the file opened
                    virtual const std::string& getFileName() const;

                public:
                    // reading from the file

                    /// loads the next line from the file (current cursor pos till next line ending)
                    virtual std::string& getLine(std::string& line);
                    virtual std::string getLine();

                    /**  @return the line if it starts with the string provided as the second param
                    * if not, the string will be erased, the "cursor" will still be moved */
                    virtual std::string& getLineWithStart(std::string& line, const std::string& start);
                    virtual std::string getLineWithStart(const std::string& start);

                    /// @return the next character in the file
                    virtual char getChar();

                    /** reads the whole content of the file */
                    virtual std::string& getAll(std::string& loadTo);

                public:
                    // writing to the file

                    /// erases the content from the file
                    virtual void eraseAll();

                    /**  writes the string to the file
                    * the "cursor" will be moved behind the inserted string */
                    virtual void write(const std::string& str);

                public:
                    // getting information about the state of the file

                    /** @return an index into the file
                    * representing the position of the "cursor" which is used to read / write */
                    virtual size_t getPosition();
                    virtual void setPosition(const size_t& position);

                    /** @return whether the "cursor" has reached the end of the file */
                    virtual bool eof()  const;

                    /** @return the size of the file in bytes (equal to the number of characters) */
                    virtual size_t getSize()  const;

                public:

                    File();
                    virtual ~File();

            };

        } // fstream_file

    } // file

} // undicht


#endif // FSTREAM_FILE_FILE_H
