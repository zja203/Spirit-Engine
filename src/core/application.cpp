#include "Spirit/sprtpch.hpp"
#include "Spirit/core/application.hpp"
#include <GL/glew.h>
#include "Spirit/log.hpp"
#include "Spirit/events/event.hpp"
#include <filesystem>

namespace Spirit {
	Application* Application::s_Instance = nullptr;

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_FN(OnEvent));
		m_Specification.WorkingDir = std::filesystem::current_path();
		SPRT_CORE_INFO("Current Directory: {0}", m_Specification.WorkingDir);
	}

	void Application::pushLayer(Layer *layer) {
		m_LayerStack.pushLayer(layer);
		layer->OnAttach();
	}

	void Application::pushOverlay(Layer *layer) {
		m_LayerStack.pushOverlay(layer);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	Application::~Application() {}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		if (e.getWidth() == 0 || e.getHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		return false;
	}

	void Application::Run() {
		while (m_Running) {
			for (Layer *layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}
