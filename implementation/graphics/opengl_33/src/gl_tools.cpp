#include <glad/glad.h>
#include "gl_tools.h"
#include <core/event_logger.h>

using namespace undicht::core;


namespace undicht {

    namespace graphics {

        namespace gl33 {


            void undCheckGLError(const std::string& origin) {
                /** calls glGetError and translates the error code into text form
                * if not 0, the error get stored as a Note (UND_ERROR) */

                unsigned int gl_error = glGetError();

                if(gl_error)
                    EventLogger::storeNote(Note(UND_ERROR, gl_error, origin));

            }

        } //gl33

    } // graphics

} // undicht
