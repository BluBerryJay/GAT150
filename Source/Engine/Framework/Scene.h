#pragma once
#include "Actor.h"
#include <list>
#include <memory>

namespace kiko
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		void ActivateByName(const std::string& name, bool active = true);

		template<typename T>
		T* GetActor();
		template<typename T>
		T* GetActorByName(const std::string& name);
		
		bool Load(const std::string& fileName);
		void Read(const json_t& value);
		
		friend class Actor;

		std::list<res_t<Actor>> m_actors;
	private:
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (actor->name == name)
			{

				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		}
		return nullptr;
	}


}