#include "Spirit/window.hpp"
#include "Spirit/platform/linux/linux_window.hpp"
#include "Spirit/platform/windows/windows_window.hpp"

namespace Spirit {
	Window* Window::Create(const WindowProps& props) {
#if defined(SPRT_PLATFORM_WINDOWS)
		return new WindowsWindow(props);
#elif defined(SPRT_PLATFORM_LINUX)
		return new LinuxWindow(props);
#endif
	}
}
