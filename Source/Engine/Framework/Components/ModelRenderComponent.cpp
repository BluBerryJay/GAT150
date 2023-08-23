#include "ModelRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"
namespace kiko
{
	CLASS_DEFINITION(ModelRenderComponent)
	void kiko::ModelRenderComponent::Update(float dt)
	{
	}

	bool ModelRenderComponent::Initialize()
	{
		m_model = GET_RESOURCE(Model, modelName);
		return true;
	}

	void kiko::ModelRenderComponent::Draw(Renderer& rend)
	{
		m_model->Draw(rend, m_owner->transform);
	}
	void ModelRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}

}
