#pragma once

#include <memory>

#ifdef GX_PLATFORM_WINDOWS
	#if GX_DYNAMIC_LINK
		#ifdef GX_BUILD_DLL
			#define GALAXY_API __declspec(dllexport)
		#else
			#define GALAXY_API __declspec(dllimport)
		#endif
	#else
		#define GALAXY_API
	#endif
#else
	#error Galaxy only supports windows!
#endif

#ifdef GX_DEBUG
	#define GX_ENABLE_ASSERTS
#endif


#ifdef GX_ENABLE_ASSERTS
	#define GX_ASSERT(x, ...) { if(!(x)) { GX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GX_CORE_ASSERT(x, ...) { if(!(x)) { GX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GX_ASSERT(x, ...)
	#define GX_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define GX_BIND(x) std::bind(&x, this, std::placeholders::_1)

namespace Galaxy
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	/*template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}*/

	template<typename T>
	using Ref = std::shared_ptr<T>;
	/*template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}*/
}