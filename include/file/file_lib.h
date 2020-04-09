#ifndef FILE_LIB_H
#define FILE_LIB_H

#include <core/shared_lib_class.h>


namespace undicht {

    namespace file {


        SHARED_LIB_CLASS(class FileLib {
            public:

                static void initialize();

                static void terminate();

                FileLib();
                virtual ~FileLib();


        };)


    } // file

} // undicht

#endif // FILE_LIB_H
