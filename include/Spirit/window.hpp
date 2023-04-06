#pragma once

#include "Spirit/sprtpch.hpp"
#include "Spirit/core/base.hpp"
#include "Spirit/events/event.hpp"

namespace Spirit {
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Spirit Engine",
			        unsigned int width = 1280,
			        unsigned int height = 720)
			: Title(title), Width(width), Height(height) { }
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;

		virtual void* getNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
