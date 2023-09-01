#include "StardewBrawl.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"


bool StardewBrawl::Initialize()
{
	// create font / text objects
	
	

	// load audio
	kiko::g_audioSystem.AddAudio("coinCollect", "Audio/coin pickup.wav");
	kiko::g_audioSystem.AddAudio("bushSounds", "Audio/foliage sound.mp3");
	kiko::g_audioSystem.AddAudio("enemyStinger", "Audio/enemy sound.mp3");
	kiko::g_audioSystem.AddAudio("groundHit", "Audio/ground hit.mp3");
	kiko::g_audioSystem.AddAudio("startGame", "Audio/start sound.mp3");
	kiko::g_audioSystem.AddAudio("introSound", "Audio/intro stinger.mp3");
	kiko::g_audioSystem.AddAudio("jumpSound", "Audio/jump sound.mp3");
	kiko::g_audioSystem.AddAudio("hitSound", "Audio/hit sound.mp3");
	kiko::g_audioSystem.AddAudio("deathSound", "Audio/death sfx.mp3");
	
	
	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scenes/stardewScene.json");
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Initialize();
	//m_scene->SetGame(this);
	m_scene->GetActorByName<kiko::Actor>("Title")->active = false;
	m_scene->GetActorByName<kiko::Actor>("StartTitle")->active = false;
	m_scene->GetActorByName<kiko::Actor>("ScoreTimer")->active = false;
	m_scene->GetActorByName<kiko::Actor>("LivesCounter")->active = false;
	m_scene->GetActorByName<kiko::Player>("Player")->active = false;
	m_scene->GetActorByName<kiko::Actor>("Coin")->active = false;
	m_scene->GetActorByName<kiko::Enemy>("Enemy")->prototype = true;
	m_scene->GetActorByName<kiko::Enemy>("Enemy")->active = false;
	
	
	EVENT_SUBSCRIBE("AddPoints", StardewBrawl::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", StardewBrawl::OnPlayerDead);
	std::cout << "Num of actors: " << m_scene->m_actors.size() << std::endl;
	m_titleTimer = 0;
	titleActive = false;
	return true;
}

void StardewBrawl::Shutdown()
{
}

void StardewBrawl::Update(float dt)
{
	
	

	switch (m_state)
	{
	case StardewBrawl::eState::Title:
		
		m_titleTimer += dt;
		m_startTimer += dt;
		if (m_titleTimer >= 3 && !titleActive)
		{

			std::cout << "Loaded Title..." << std::endl;
			m_scene->GetActorByName<kiko::Actor>("Title")->active = true;
			kiko::g_audioSystem.PlayOneShot("introSound", false);
			titleActive = true;
			m_titleTimer = 0;
		}
		if (titleActive && m_startTimer <= 0.5f && !enterActive)
		{
			
			std::cout << "Title On" << std::endl;
			m_scene->GetActorByName<kiko::Actor>("StartTitle")->active = true;
			enterActive = true;
		}
		else if(m_scene->GetActorByName<kiko::Actor>("StartTitle")->active && m_startTimer >= 0.5f && enterActive)
		{
			m_scene->GetActorByName<kiko::Actor>("StartTitle")->active = false;
			std::cout << "Title Off" << std::endl;
			enterActive = false;
					
			
		}
		else if (m_startTimer > 1)
		{
			m_startTimer = 0;
		}
	
		
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_RETURN))
		{
			m_state = eState::StartGame;
			kiko::g_audioSystem.PlayOneShot("startGame", false);
			
			m_scene->GetActorByName<kiko::Actor>("Title")->active = false;
			m_scene->GetActorByName<kiko::Actor>("StartTitle")->active = false;
			
		}
		
		break;

	case StardewBrawl::eState::StartGame:
		m_score = 0;
		
		m_scene->GetActorByName<kiko::Actor>("Player")->active = true;
		m_scene->GetActorByName<kiko::Actor>("Coin")->active = true;
		m_state = eState::StartLevel;
		break;

	case StardewBrawl::eState::StartLevel:
		m_scene->GetActorByName<kiko::Actor>("LivesCounter")->active = true;
		m_scene->GetActorByName<kiko::Actor>("ScoreTimer")->active = true;
		
		m_state = eState::Game;
		break;
	case StardewBrawl::eState::Game:
		
		m_aliveTimer += dt;
		
		
		m_scene->GetActorByName<kiko::Actor>("ScoreTimer")->GetComponent<kiko::TextRenderComponent>()->SetText("Time: " + std::to_string((int)m_aliveTimer));
		m_scene->GetActorByName<kiko::Actor>("LivesCounter")->GetComponent<kiko::TextRenderComponent>()->SetText("Lives: " + std::to_string((int)m_scene->GetActorByName<kiko::Player>("Player")->lives));
		
		m_spawnTimer += dt;
		if (m_spawnTimer > 6 && !m_scene->GetActorByName<kiko::Actor>("Enemy")->active)
		{
			kiko::g_audioSystem.PlayOneShot("enemyStinger", false);
			m_scene->GetActorByName<kiko::Actor>("Enemy")->active = true;
			m_spawnTimer = 0;
		}
		
		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case StardewBrawl::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case StardewBrawl::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void StardewBrawl::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
	
}

void StardewBrawl::AddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void StardewBrawl::OnPlayerDead(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}



