workspace "Galaxy"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "Galaxy"
		location "Galaxy"
		kind "SharedLib"
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
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include"	
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