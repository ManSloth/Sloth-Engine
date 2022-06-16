#pragma once

#include <memory>

#ifdef SLTH_PLATFORM_WINDOWS
#if SLTH_DYNAMIC_LINK
	#ifdef SLTH_BUILD_DLL
		#define SLOTH_API __declspec(dllexport)
	#else
		#define SLOTH_API __declspec(dllimport)
	#endif
#else
	#define SLOTH_API
#endif
#else
	#error Sloth only support Windows!
#endif

#ifdef SLTH_ENABLE_ASSERTS
	#define SLTH_ASSERT(x, ...) { if(!x)) {SLTH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SLTH_CORE_ASSERT(x, ...) { if(!x)) {SLTH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SLTH_ASSERT(x, ...)
	#define SLTH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SLTH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Sloth {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}