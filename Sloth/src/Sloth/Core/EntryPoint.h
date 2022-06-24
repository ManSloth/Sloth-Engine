#pragma once

#ifdef SLTH_PLATFORM_WINDOWS

extern Sloth::Application* Sloth::CreateApplication();

int main(int argc, char** argv)
{
	Sloth::Log::Init();
	SLTH_CORE_WARN("Initialized Log!");

	auto app = Sloth::CreateApplication();
	app->Run();
	delete app;
}

#endif