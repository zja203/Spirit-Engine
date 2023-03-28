#pragma once

#include "Spirit/log.hpp"

extern Spirit::Application* Spirit::CreateApplication();

int main(int argc, char *argv[]) {
	Spirit::Log::Init();
	SPRT_CORE_WARN("Initialized Log!");
	auto app = Spirit::CreateApplication();
	app->Run();
	delete app;
}
