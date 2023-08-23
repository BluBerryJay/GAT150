#include "TextRenderComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Renderer/Renderer.h"
namespace kiko
{
    CLASS_DEFINITION(TextRenderComponent);

    TextRenderComponent::TextRenderComponent(const TextRenderComponent* other)
    {
        text = other->text;
        fontName = other->fontName;

        m_changed = true;
        m_text = std::make_unique<Text>(*other->m_text.get());
    }

    bool TextRenderComponent::Initialize()
    {
        if (!fontName.empty())
        {
            m_text = std::make_unique<Text>(GET_RESOURCE(Text, fontName, fontSize));
        }
        return true;
    }

    void TextRenderComponent::Update(float dt)
    {
    }

    void TextRenderComponent::Draw(Renderer& renderer)
    {
        if (m_changed)
        {
            m_changed = false;
            m_text->Create(renderer, text, { 1, 1, 1, 1 });
        }
        m_text->Draw(renderer, );
    }

    void TextRenderComponent::SetText(const std::string& string)
    {
        if (string != text)
        {
            text = string;
            m_changed = true;
        }
       
    }
    void TextRenderComponent::Read(const json_t& value)
    {
        READ_DATA(value, text);
        READ_DATA(value, fontName);
        READ_DATA(value, fontSize);
    }
}
