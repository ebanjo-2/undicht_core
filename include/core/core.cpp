#include "core.h"
#include <iostream>
#include <core/event_logger.h>
#include <window/window.h>
#include <window/graphics_context.h>
#include <core/string_tools.h>

using namespace std::chrono;

namespace undicht {

    namespace core {

const std::string core_file_path = getFilePath(UND_CODE_SRC_FILE, 2); // the file path to the core project

#ifdef UND_UNIX
    // for linux
    std::string Core::s_window_lib_path = core_file_path + "implementation/window/glfw/libwindow_glfw.so";
    std::string Core::s_video_lib_path = core_file_path + "implementation/graphics/opengl_33/libvideo_opengl_33.so";
    std::string Core::s_audio_lib_path = core_file_path + "implementation/audio/openal/libaudio_openal.so";
    std::string Core::s_file_lib_path = core_file_path + "implementation/file/fstream/libfstream_file.so";
#endif // UND_UNIX


#ifdef UND_WINDOWS
    // for windows
    std::string Core::s_window_lib_path = core_file_path + "implementation/window/glfw/window_glfw.dll";
    std::string Core::s_video_lib_path = core_file_path + "implementation/graphics/opengl_33/video_opengl_33.dll";
    std::string Core::s_audio_lib_path = core_file_path + "implementation/audio/openal/audio_openal.dll";
    std::string Core::s_file_lib_path = core_file_path + "implementation/file/fstream/fstream_file.dll";
#endif // UND_WINDOWS


        SharedLib Core::s_window_lib;
        SharedLib Core::s_video_lib;
        SharedLib Core::s_audio_lib;
        SharedLib Core::s_file_lib;

        high_resolution_clock::time_point Core::s_startup_time;

        void Core::setLibraryPaths(const std::string& window, const std::string& video, const std::string& audio, const std::string& file){

            s_window_lib_path = window;
            s_video_lib_path = video;
            s_audio_lib_path = audio;
            s_file_lib_path = file;


        }

        // loads shared libraries
        void Core::initialize(bool init_window, bool init_graphics, bool init_audio, bool init_file) {

            s_startup_time = high_resolution_clock::now();


            // setting some static event messages
            Note::setStaticMessage("EVENT: MESSAGE: EMPTY MESSAGE", 0);
            Note::setStaticMessage("DLL ERROR 126", 126);
            Note::setStaticMessage("DLL ERROR 127 (failed to find procedure)", 127);



            if(init_window) s_window_lib.open(s_window_lib_path);
            if(init_graphics) s_video_lib.open(s_video_lib_path);
            if(init_audio) s_audio_lib.open(s_audio_lib_path);
            if(init_file) s_file_lib.open(s_file_lib_path);

        }

        // closes shared libraries
        void Core::terminate() {
            s_window_lib.close();
            s_video_lib.close();
            s_audio_lib.close();
            s_file_lib.close();
        }

        double Core::getTime() {

            high_resolution_clock::time_point now = high_resolution_clock::now();

            duration<double> time_since_startup = duration_cast<duration<double>>(now - s_startup_time);

            return time_since_startup.count();
        }

    } // core

} // undicht

