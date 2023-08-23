#pragma once
#include "Component.h"
#include "Framework/Resource/Resource.h"
namespace kiko
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& rend) = 0;
		virtual float GetRadius() { return 0.0f; }
	private:
	};
}