#pragma once

#ifdef SLTH_PLATFORM_WINDOWS
	#ifdef SLTH_BUILD_DLL
		#define SLOTH_API __declspec(dllexport)
	#else
		#define SLOTH_API __declspec(dllimport)
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