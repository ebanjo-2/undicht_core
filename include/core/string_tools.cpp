#include "string_tools.h"

namespace undicht {

    namespace core {


        bool hasFileType(std::string file_name, std::string type) {
            /**@brief checks if the file_name has the type (with type being the files ending, like ".obj" or ".jpg" */

            int start_of_ending = file_name.find('.', 0); // finding the file - ending

            return !file_name.compare(start_of_ending, type.length(), type);
        }


        /** removes the file name (*.*), and returns the remaining path */
        std::string getFilePath(std::string file_name, int go_back) {

            // where the file path ends
            size_t path_end = file_name.size();

            // cutting the file name / directories from the file path
            for(int i = 0; i <= go_back; i++) {

                path_end = file_name.rfind("/", path_end - 1);

            }

            // resizing the file_name
            if(path_end != std::string::npos) {
                file_name.resize(path_end + 1);
            }

            return file_name;
        }

    } // core

} // undicht
