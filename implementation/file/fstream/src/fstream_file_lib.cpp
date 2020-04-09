#include "fstream_file_lib.h"
#include <core/shared_lib.h>

namespace undicht {

    namespace file {

        namespace fstream_file {


            FStreamFileLib::FStreamFileLib() {


            }

            FStreamFileLib::~FStreamFileLib() {


            }


            void FStreamFileLib::initialize() {
                // just here for the sake of completeness

            }

            void FStreamFileLib::terminate() {


            }


            /////////////////////// functions that can be accessed from outside the shared lib //////////

            SHARED_LIB_EXPORT void initialize() {

                FStreamFileLib::initialize();

            }

            SHARED_LIB_EXPORT void terminate() {

                FStreamFileLib::terminate();

            }


        } // fstream_file

    } // file

} // undicht
