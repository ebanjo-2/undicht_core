#include "file_lib.h"
#include <file/file.h>
#include <core/core.h>

namespace undicht {

    namespace file {

        FileLib::FileLib() {

        }

        FileLib::~FileLib() {

        }

        void FileLib::initialize() {

            ((void(*)())core::Core::s_file_lib.getFunction("initialize")) ();

            // initializing the functions to load audio objects from the shared lib
            createFile = (implementation::File*(*)())core::Core::s_file_lib.getFunction("createFile");
            copyFile = (void(*)(implementation::File*,implementation::File*))core::Core::s_file_lib.getFunction("copyFile");
            deleteFile = (void(*)(implementation::File*))core::Core::s_file_lib.getFunction("deleteFile");

        }

        void FileLib::terminate() {

            ((void(*)())core::Core::s_file_lib.getFunction("terminate")) ();

        }



    } // file

} // undicht
