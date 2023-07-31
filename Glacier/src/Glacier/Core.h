#pragma once

#define GLACIER_API
#define USE_WIN32_WINDOWS
#define GR_ENABLE_ASSERTS

#ifdef GR_ENABLE_ASSERTS
	#define GR_ASSERT(x, ...) { if(!(x)) { GR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GR_CORE_ASSERT(x, ...) { if(!(x)) { GR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GR_ASSERT(x, ...)
	#define GR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define BIND_EVENT_CALLBACK(x) std::bind(x, this, std::placeholders::_1))