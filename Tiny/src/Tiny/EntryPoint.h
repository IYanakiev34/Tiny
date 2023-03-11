#pragma once

#ifdef TN_WINDOWS_PLATFORM

extern Tiny::Application* Tiny::CreateApplication();

int main(int argc, char **argv)
{
	Tiny::Log::Init();
	auto app = Tiny::CreateApplication();
	app->Run();
	delete app;
}

#endif 