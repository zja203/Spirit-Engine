#pragma once

#include "Spirit/window.hpp"
#include <GLFW/glfw3.h>

namespace Spirit {
	class LinuxWindow : public Window {
	public:
		LinuxWindow(const WindowProps& props);
		virtual ~LinuxWindow();

		void OnUpdate() override;

		inline unsigned int getWidth() const override { return m_Data.Width; }
		inline unsigned int getHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}
