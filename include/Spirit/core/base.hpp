#pragma once

#include <memory>

#if defined(__linux__) || defined(__linux) || defined(linux)
	#define SPRT_PLATFORM_LINUX
#elif defined(_WIN64)
	#define SPRT_PLATFORM_WINDOWS
#endif

#ifdef SPRT_PLATFORM_WINDOWS
	#define SPRT_BREAKDEBUGGER __debugbreak();
#elif defined(SPRT_PLATFORM_LINUX)
	#include <signal.h>
	#define SPRT_BREAKDEBUGGER raise(SIGTRAP)
#else
	#error Spirit only supports (64 bit) Windows and Linux!
#endif

#define BIT(x) (1 <<x )

namespace Spirit {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
