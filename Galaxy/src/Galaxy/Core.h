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

#ifdef GX_ENABLE_ASSERTS
	#define GX_ASSERT(x, ...) ( if(!(x)) {GX_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); })
	#define GX_CORE_ASSERT(x, ...) ( if(!(x)) {GX_CORE_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); })
#else
	#define GX_ASSERT(x, ...)
	#define GX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)