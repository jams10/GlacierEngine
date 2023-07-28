#pragma once

#ifdef GR_PLATFORM_WINDOWS

extern Glacier::Application* Glacier::CreateApplication();

int main(int argc, char** argv)
{
	Glacier::Log::Init();
	GR_CORE_WARN("Initialize Log!");
	int a = 5;
	GR_INFO("Hello! Var={0}", a);

	auto app = Glacier::CreateApplication();
	app->Run();
	delete app;
}

#endif