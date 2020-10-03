project "window_glfw"
    
    kind "SharedLib" 

    files { "src/**.*" }
	
	
    includedirs { "../../../include", "src", "../../../vendor/glfw/include", "../../../vendor/EGL-Registry/api"}
	
	configuration "debug - linux"
		libdirs {  "../../../vendor/glfw/build/src"}
		links { "glfw3", "core", "pthread", "dl", "Xxf86vm", "Xrandr", "Xinerama", "Xcursor", "X11" }
		flags { "Symbols" }
		
	configuration "release - linux"
		libdirs { "../../../vendor/glfw/undicht/GLFW/linux",  "../../../vendor/glfw/build/src" }
		links { "glfw3", "core", "pthread", "dl", "Xxf86vm", "Xrandr", "Xinerama", "Xcursor", "X11" }
		flags { "OptimizeSpeed" }
		
	configuration "debug - windows"
		libdirs { "../../../vendor/glfw/undicht/GLFW/windows",  "../../../vendor/glfw/build/src" }
		links { "glfw3", "gdi32", "opengl32", "core" }
		flags { "Symbols" }
		
	configuration "release - windows"
		libdirs { "../../../vendor/glfw/undicht/GLFW/windows",  "../../../vendor/glfw/build/src" }
		links { "glfw3", "gdi32", "opengl32", "core" }
		flags { "OptimizeSpeed"}




