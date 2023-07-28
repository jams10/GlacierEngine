#pragma once

#define GLACIER_API
#define GR_ENABLE_ASSERTS

#ifdef GR_ENABLE_ASSERTS
	#define GR_ASSERT(x, ...) { if(!(x)) { GR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GR_CORE_ASSERT(x, ...) { if(!(x)) { GR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GR_ASSERT(x, ...)
	#define GR_CORE_ASSERT(x, ...)
#endif