#pragma once

#include "core/base.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Spirit {
	class Log {
		public:
			static void Init();

			inline static Ref<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
			inline static Ref<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
		private:
			static Ref<spdlog::logger> s_CoreLogger;
			static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define SPRT_CORE_TRACE(...)    ::Spirit::Log::getCoreLogger()->trace(__VA_ARGS__)
#define SPRT_CORE_INFO(...)     ::Spirit::Log::getCoreLogger()->info(__VA_ARGS__)
#define SPRT_CORE_WARN(...)     ::Spirit::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SPRT_CORE_ERROR(...)    ::Spirit::Log::getCoreLogger()->error(__VA_ARGS__)
#define SPRT_CORE_CRITICAL(...) ::Spirit::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SPRT_TRACE(...)        ::Spirit::Log::getClientLogger()->trace(__VA_ARGS__)
#define SPRT_INFO(...)         ::Spirit::Log::getClientLogger()->info(__VA_ARGS__)
#define SPRT_WARN(...)         ::Spirit::Log::getClientLogger()->warn(__VA_ARGS__)
#define SPRT_ERROR(...)        ::Spirit::Log::getClientLogger()->error(__VA_ARGS__)
#define SPRT_CRITICAL(...)     ::Spirit::Log::getClientLogger()->critical(__VA_ARGS__)

// Asserts
#ifdef SPRT_ENABLE_ASSERTS
       #define SPRT_ASSERT(x, ...) { if(!(x)) { SPRT_ERROR("Assertion Failed: {0}", __VA_ARGS__); SPRT_BREAKDEBUGGER(); } }
       #define SPRT_CORE_ASSERT(x, ...) { if(!(x)) { SPRT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); SPRT_BREAKDEBUGGER; } }
#else
	#define SPRT_ASSRT(x, ...)
	#define SPRT_CORE_ASSERT(x, ...)
#endif
