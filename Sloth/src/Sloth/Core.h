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