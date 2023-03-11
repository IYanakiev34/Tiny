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

#ifdef TN_ENABLE_ASSERTS
#define TN_ASSERT(x,...)(if(!(x)) {TN_ERROR("Assertion Failed: {0}",__VA_ARGS__);})
#define TN_CORE_ASSERT(x,...) (if(!(x)) {TN_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);})
#else
#define TN_CORE_ASSERT(x,...)
#define TN_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)