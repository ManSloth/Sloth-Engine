#pragma once

#ifdef SLTH_PLATFORM_WINDOWS

extern Sloth::Application* Sloth::CreateApplication();

int main(int argc, char** argv)
{
	Sloth::Log::Init();
	SLTH_CORE_WARN("Initialized Log!");
	int a = 5;
	SLTH_INFO("Hello! Var={0}", a);

	//printf("Sloth Engine\n");
	auto app = Sloth::CreateApplication();
	app->Run();
	delete app;
}

#endif