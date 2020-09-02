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
IncludeDir["glm"] = "Galaxy/vendor/glm"
IncludeDir["stb_image"] = "Galaxy/vendor/stb_image"

group "Dependencies"
	include "Galaxy/vendor/GLFW"
	include "Galaxy/vendor/Glad"
	include "Galaxy/vendor/ImGui"
group ""

	project "Galaxy"
		location "Galaxy"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "gxpch.h"
		pchsource "Galaxy/src/gxpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/stb_image/**.h",
			"%{prj.name}/vendor/stb_image/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl",
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.GLAD}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.stb_image}"
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

		links
		{
			"GLFW",
			"GLAD",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			systemversion "latest"

			defines 
			{
				"GX_PLATFORM_WINDOWS",
				"GX_BUILD_DLL",
				"GLFW_INCLUDE_NONE"
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

	project "Galaxy-Editor"
		location "Galaxy-Editor"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17" 
		staticruntime "on"

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
			"Galaxy/vendor/spdlog/include",
			"%{IncludeDir.glm}",
			"Galaxy/vendor"
		}

		links
		{
			"Galaxy"
		}

		filter "system:windows"
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

	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17" 
		staticruntime "on"

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
			"Galaxy/vendor/spdlog/include",
			"%{IncludeDir.glm}",
			"Galaxy/vendor"
		}

		links
		{
			"Galaxy"
		}

		filter "system:windows"
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