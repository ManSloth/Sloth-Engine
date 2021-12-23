#pragma once

#ifdef SLTH_PLATFORM_WINDOWS

extern Sloth::Application* Sloth::CreateApplication();

int main(int argc, char** argv)
{
	printf("Sloth Engine\n");
	auto app = Sloth::CreateApplication();
	app->Run();
	delete app;
}

#endif