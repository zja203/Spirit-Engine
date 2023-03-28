#include "Spirit/sprtpch.hpp"
#include "Spirit/core/application.hpp"
#include "Spirit/log.hpp"
#include "Spirit/events/event.hpp"
#include <filesystem>

namespace Spirit {
	Application* Application::s_Instance = nullptr;

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application() {
		s_Instance = this;

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

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			for (Layer *layer : m_LayerStack)
				layer->OnUpdate();
		}
	}
}
