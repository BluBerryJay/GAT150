#pragma once
#include "Component.h"
#include "Framework/Resource/Resource.h"
namespace kiko
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& rend) = 0;
	private:
	};
}