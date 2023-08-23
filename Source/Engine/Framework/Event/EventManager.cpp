#include "EventManager.h"
#include "Core/Logger.h"
namespace kiko
{

	void EventManager::Update(float dt)
	{
		
	}

	void EventManager::Subscribe(Event::id_t id, IEventListener* listener, event_func function)
	{
		EventDispatcher dispatch;
		dispatch.listener = listener;
		dispatch.func = function;
		INFO_LOG("Event Subscribed: " << id);
		m_dispatchers[id].push_back(dispatch);
	}

	void EventManager::Unsubscribe(Event::id_t id, IEventListener* listener)
	{
	}

	void EventManager::DispatchEvent(Event::id_t id, Event::data_t data)
	{
		Event event{ id, data };
		if (m_dispatchers.find(id) != m_dispatchers.end())
		{
			auto& dispatchers = m_dispatchers[id];
			for (auto& dispatcher : dispatchers)
			{
				dispatcher.func(event);
			}
		}
	}
}
