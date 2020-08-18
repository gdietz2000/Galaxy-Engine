workspace "Galaxy"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Galaxy/vendor/GLFW/include"
IncludeDir["GLAD"] = "Galaxy/vendor/Glad/include"
IncludeDir["ImGui"] = "Galaxy/vendor/ImGui"

include "Galaxy/vendor/GLFW"
include "Galaxy/vendor/Glad"
include "Galaxy/vendor/ImGui"

	project "Galaxy"
		location "Galaxy"
		kind "SharedLib"
		language "C++"
		staticruntime "off"

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
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.ImGui}",
		}

		links
		{
			"GLFW",
			"GLAD",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			cppdialect "C++17"
			systemversion "latest"

			defines 
			{
				"GX_PLATFORM_WINDOWS",
				"GX_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
			}

			postbuildcommands
			{
				("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
			}

		filter "configurations:Debug"
			defines "GX_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "GX_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "GX_DIST"
			runtime "Release"
			optimize "On"

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		staticruntime "off"

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
			systemversion "latest"

			defines 
			{
				"GX_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "GX_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "GX_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "GX_DIST"
			runtime "Release"
			optimize "On"