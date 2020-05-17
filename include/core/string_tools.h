#ifndef STRING_TOOLS_H_INCLUDED
#define STRING_TOOLS_H_INCLUDED

#include <sstream>

// some simple string tools

namespace undicht {

    namespace core {

#define UND_CODE_SRC_FILE replaceAllChars(undicht::core::toStr(__FILE__), '\\', '/') /** on windows you might get '\' between directory names, which would break things */

        /** gives you a string containing data about
        * the location of the line this makro is used in
        * (file_path : line_number) */
#define UND_CODE_ORIGIN UND_CODE_SRC_FILE + undicht::core::toStr(" : ") + undicht::core::toStr(__LINE__)


        /** tries to convert everything into a string */
        template <typename T>
        std::string toStr(const T& t) {
            std::stringstream s;
            s << t;
            return s.str();
        }


        /**@brief checks if the file_name has the type (with type being the file's ending, like ".obj" or ".jpg" */
        bool hasFileType(std::string file_name, std::string type);

        /** removes the file name (*.*), and returns the remaining path including the last '/'
        * @param go_back: how many directories to cut at the end of the file path*/
        std::string getFilePath(std::string file_name, int go_back = 0);

        /** @brief replace all chars with an other char */
        std::string replaceAllChars(std::string str, char to_be_replaced, char replace_with);


    }

}



#endif // STRING_TOOLS_H_INCLUDED
