#pragma once
#pragma once
#include "Framework/Game.h"
#include "Framework/Event/EventManager.h"
#include "Renderer/Text.h"

class StardewBrawl : public kiko::Game, kiko::IEventListener
{
public:

	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};

public:
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
	void AddPoints(const kiko::Event& event);
	void OnPlayerDead(const kiko::Event& event);
	void World1Active();
	void World2Active();
	void World1Deactive();
	void World2Deactive();

private:
	eState m_state = eState::Title;
	float m_titleTimer = 0;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;
	bool titleActive = false;
	bool enterActive = false;
	
	
	float m_aliveTimer = 0;
	float m_stateTimer = 0;
	float m_startTimer = 0;
	

};
