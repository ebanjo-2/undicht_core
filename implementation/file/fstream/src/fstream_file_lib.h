#ifndef FSTREAM_FILE_LIB_H
#define FSTREAM_FILE_LIB_H


namespace undicht {

    namespace file {

        namespace fstream_file {

            class FStreamFileLib {
                public:

                    static void initialize();

                    static void terminate();

                    FStreamFileLib();
                    virtual ~FStreamFileLib();


            };

        } // fstream_file

    } // file

} // undicht

#endif // FSTREAM_FILE_LIB_H
