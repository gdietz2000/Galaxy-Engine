#pragma once

#ifdef GX_PLATFORM_WINDOWS
	#ifdef GX_BUILD_DLL
		#define GALAXY_API __declspec(dllexport)
	#else
		#define GALAXY_API __declspec(dllimport)
	#endif
#else
	#error Galaxy only supports windows!
#endif