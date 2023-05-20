#include <Spirit.hpp>
#include <filesystem>

using Spirit::Ref;

class TestLayer : public Spirit::Layer {
	public:
		TestLayer() : Layer("Test") {

		}

		void OnUpdate() override {
		}

		void OnAttach() override {
		}

		void OnDetach() override {
		}
};

class Sandbox : public Spirit::Application {
	public:
		Sandbox() : Application(false) {
			pushLayer(new TestLayer());
		}

		~Sandbox() { }
};

Spirit::Application* Spirit::CreateApplication() {
	return new Sandbox();
}
