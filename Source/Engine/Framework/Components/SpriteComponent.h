#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
namespace kiko
{
	class SpriteComponent : public RenderComponent
	{
	public:
		void Update(float dt) override;
		void Draw(Renderer& rend) override;
	public:
		res_t<Texture> m_texture;
	};
}