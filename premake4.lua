-- the premake4 file used to build the undicht core project

solution "undicht_core"
	
    language "C++"
    buildoptions "-std=c++11"
    configurations { "debug - windows","debug - linux", "release - windows", "release - linux" }

    -- basically include
    dofile "premake4_include_core_projects.lua"


    
