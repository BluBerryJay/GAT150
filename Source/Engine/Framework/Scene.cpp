#include "Scene.h"
#include "Framework/Components/CollisionComponent.h"
#include "Game/Player.h"
#include "Game/Enemy.h"

namespace kiko
{
	bool Scene::Initialize()
	{
		for (auto& actor : m_actors) actor->Initialize();

		return true;
	}
	void Scene::Update(float dt)
	{
		// update and remove destroyed actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			if ((*iter)->active) (*iter)->Update(dt);
			((*iter)->destroyed) ? iter = m_actors.erase(iter) : iter++;
		}

		// check collisions
		/*for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++)
		{
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++)
			{
				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();
				if (!collision1 || !collision2) continue;

				if (collision1->CheckCollision(collision2))
				{
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
		}*/
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			if (actor->active) actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll(bool force)
	{
		auto iter = m_actors.begin();
		while (iter != m_actors.end())
		{
			
			(force || !(*iter)->persistent) ? iter = m_actors.erase(iter) : iter++;
		}
	}
	void Scene::ActivateByName(const std::string& name, bool active)
	{
		for (auto& actor : m_actors)
		{
			if (actor->name == name) actor->active = active;
		}
	}

	bool Scene::Load(const std::string& fileName)
	{
		rapidjson::Document document;
		if (!JSON::Load(fileName, document))
		{
			ERROR_LOG("Could not load scene file: " << fileName);
			return false;
		}
		Read(document);
		return true;
	}
	void Scene::Read(const json_t& value)
	{
		if (HAS_DATA(value, m_actors) && GET_DATA(value, m_actors).IsArray())
		{
			for (auto& actorValue : GET_DATA(value, m_actors).GetArray())
			{
				std::string type;
				READ_DATA(actorValue, type);
				auto actor = CREATE_CLASS_BASE(Actor, type);
				
				actor->Read(actorValue);
				if (actor->prototype)
				{
					std::string name = actor->name;
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				}
				else
				{
					Add(std::move(actor));
				}
			}
		}

	}
}