#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace kiko
{
	class ModelRenderComponent : public RenderComponent
	{
		public:
			void Update(float dt) override;
			void Draw(Renderer& rend) override;
		public:
			res_t<Model> m_texture;
	};
}