#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"
#include "Framework/Factory.h"

namespace kiko
{
	class ModelRenderComponent : public RenderComponent
	{
		public:
			CLASS_DECLARATION(ModelRenderComponent)
			void Update(float dt) override;
			bool Initialize() override;
			void Draw(Renderer& rend) override;
			virtual float GetRadius() override { return m_model->GetRadius(); }
		public:
			std::string modelName;
			res_t<Model> m_model;
	};
}