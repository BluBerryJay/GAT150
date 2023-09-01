#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Phsyics/PhysicsSystem.h"
#include "StardewBrawl.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>

using namespace std;

void SimonSaysNum(std::string text, ...)
{
	va_list args;

	va_start(args, text);
	int fontSize = va_arg(args, int);
	va_end(args);
	std::cout << text << ": " << fontSize << endl;

}

int main(int argc, char* argv[])
{

	kiko::PhysicsSystem::Instance().Initialize();
	INFO_LOG("Initializing Engine...")
	SimonSaysNum("My name jeff", 21);
	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");


	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("GAT150", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();

	// create game
	unique_ptr<StardewBrawl> game = make_unique<StardewBrawl>();
	game->Initialize();



	// main game loop
	bool quit = false;
	while (!quit)
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);

		// begin frame
		kiko::g_renderer.BeginFrame();
		game->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);
		// end frame
		kiko::g_renderer.EndFrame();
	}



	return 0;
}
