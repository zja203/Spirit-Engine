#pragma once

#include <string>
#include <memory>

#include "log.hpp"
#include "core/base.hpp"
#include "layer.hpp"

#if defined(SPRT_PLATFORM_WINDOWS)
	#include <Windows.h>
#elif defined(SPRT_PLATFORM_LINUX)
	#include <stdlib.h>
#endif
