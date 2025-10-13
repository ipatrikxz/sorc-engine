workspace "SorcEngine"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "SorcEngine"

    -- output directory format
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- include directories
    IncludeDir = {}
    IncludeDir["GLFW"] = 			"%{wks.location}/SorcEngine/vendor/include/GLFW/include"
    IncludeDir["Glad"] = 			"%{wks.location}/SorcEngine/vendor/include/Glad/include"
    IncludeDir["glm"] = 			"%{wks.location}/SorcEngine/vendor/include/glm"
    IncludeDir["stb_image"] = 		"%{wks.location}/SorcEngine/vendor/include/stb_image"
    IncludeDir["imgui"] = 			"%{wks.location}/SorcEngine/vendor/include/imgui"
	IncludeDir["imgui_plugins"] = 	"%{wks.location}/SorcEngine/vendor/include/imgui_plugins"
    IncludeDir["assimp"] =          "%{wks.location}/SorcEngine/vendor/include/assimp"

	include "SorcEngine/vendor/include/GLFW"
    include "SorcEngine/vendor/include/Glad"

    project "SorcEngine"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "Off"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        -- source files
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
            "%{prj.name}/vendor/include/stb_image/*.h",
		    "%{prj.name}/vendor/include/stb_image/*.cpp",
            "%{prj.name}/vendor/include/imgui/*.h",
            "%{prj.name}/vendor/include/imgui/*.cpp",
            "%{prj.name}/vendor/include/imgui_plugins/*.h"
        }

        -- include directories
        includedirs {
            "%{prj.name}/src",
            "%{IncludeDir.GLFW}",
            "%{IncludeDir.Glad}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.stb_image}",
            "%{IncludeDir.imgui}",
            "%{IncludeDir.imgui_plugins}",
            "%{IncludeDir.assimp}"
        }

        libdirs {
            "SorcEngine/vendor/lib/assimp",
            "SorcEngine/vendor/lib/GLFW"
        }

        -- link libraries
        links {
            "GLFW",
            "Glad",
            "opengl32.lib",
			"assimp-vc143-mtd.lib"
        }

        defines
        {
            "_CRT_SECURE_NO_WARNINGS",
		    "GLFW_INCLUDE_NONE"
        }

         -- Copy resources, DLLs, and imgui.ini to output directory
        postbuildcommands {
            "{COPY} \"%{prj.name}/res\" \"%{cfg.targetdir}/res\"",
            "{COPY} \"%{wks.location}/SorcEngine/vendor/lib/assimp/*.dll\" \"%{cfg.targetdir}\"",
            "{COPY} \"%{wks.location}/SorcEngine/vendor/include/imgui/imgui.ini\" \"%{cfg.targetdir}\""
        }

        debugdir "%{cfg.targetdir}"

        -- windows-specific
        filter "system:windows"
            systemversion "latest"

        filter "configurations:Debug"
            defines { "DEBUG" }
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            runtime "Release"
            optimize "On"
