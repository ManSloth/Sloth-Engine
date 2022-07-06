#pragma once

#ifdef SLTH_PLATFORM_WINDOWS

extern Sloth::Application* Sloth::CreateApplication();

int main(int argc, char** argv)
{
	Sloth::Log::Init();

	SLTH_PROFILE_BEGIN_SESSION("Startup", "SlothProfile-Startup.json");
	auto app = Sloth::CreateApplication();
	SLTH_PROFILE_END_SESSION();

	SLTH_PROFILE_BEGIN_SESSION("Runtime", "SlothProfile-Runtime.json");
	app->Run();
	SLTH_PROFILE_END_SESSION();

	SLTH_PROFILE_BEGIN_SESSION("Shutdown", "SlothProfile-Shutdown.json");
	delete app;
	SLTH_PROFILE_END_SESSION();
}

#endif