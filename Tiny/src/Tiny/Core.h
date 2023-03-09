#pragma once

#ifdef TN_WINDOWS_PLATFORM
	#ifdef TINY_BUILD_DLL
		#define TINY_API __declspec(dllexport)
	#else
		#define TINY_API __declspec(dllimport)
	#endif
#else
	#error TINY only supports windows
#endif 
