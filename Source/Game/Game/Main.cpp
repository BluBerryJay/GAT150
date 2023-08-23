#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include "Phsyics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>

using namespace std;


class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};
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

	/*rapidjson::Document document;
	kiko::JSON::Load("json.json", document);
	std::string message;
	kiko::JSON::Read(document, "string", message);
	std::cout << message << endl;
	bool blJson;
	kiko::JSON::Read(document, "bool", blJson);
	std::cout << blJson << endl;
	float floatJson;
	kiko::JSON::Read(document, "float", floatJson);
	std::cout << floatJson << endl;
	kiko::vec2 veccy;
	kiko::JSON::Read(document, "vector2", veccy);
	std::cout << "Vector2" << endl;
	std::cout << veccy << endl;
	int i1;
	kiko::JSON::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;
	int i2;
	kiko::JSON::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;*/
	
	// initialize engine
	kiko::g_renderer.Initialize();	
	kiko::g_renderer.CreateWindow("GAT150", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();

	// create game
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

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

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		game->Draw(kiko::g_renderer);
		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());
			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(kiko::g_renderer);
		}

		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	stars.clear();

	return 0;
}
