workspace "Galaxy"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Galaxy/vendor/GLFW/include"

include "Galaxy/vendor/GLFW"

	project "Galaxy"
		location "Galaxy"
		kind "SharedLib"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "gxpch.h"
		pchsource "Galaxy/src/gxpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}"
		}

		links
		{
			"GLFW",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines 
			{
				"GX_PLATFORM_WINDOWS",
				"GX_BUILD_DLL"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
			}

		filter "configurations:Debug"
			defines "GX_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "GX_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "GX_DIST"
			optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"Galaxy/src",
			"Galaxy/vendor/spdlog/include"	
		}

		links
		{
			"Galaxy"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines 
			{
				"GX_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "GX_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "GX_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "GX_DIST"
			optimize "On"