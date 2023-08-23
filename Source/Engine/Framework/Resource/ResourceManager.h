#pragma once
#include "Resource.h"
#include "Framework/Singleton.h"
#include <map>
#include <memory>
#include <string>

#define GET_RESOURCE(type, fileName, ...) kiko::ResourceManager::Instance().Get<type>(fileName, __VA_ARGS__)
namespace kiko
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T, typename ... TArgs>
		res_t<T> Get(const std::string& fileName, TArgs ... args);


	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};
	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& fileName, TArgs ... args)
	{
		if (m_resources.find(fileName) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[fileName]);
		}
		std::shared_ptr<T> resource = std::make_shared<T>();
		resource->Create(fileName, args...);
		m_resources[fileName] = resource;
		return resource;

	}
}