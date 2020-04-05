project "fstream_file"
    
    kind "SharedLib" 

    files { "src/**.*" }
    
    links { "core" }

    includedirs { "../../../include", "src" }
	
	configuration "debug - linux"
		flags { "Symbols" }
		
	configuration "release - linux"
		flags { "OptimizeSpeed" }
		
	configuration "debug - windows"
		flags { "Symbols" }

	configuration "release - windows"
		flags { "OptimizeSpeed"}
