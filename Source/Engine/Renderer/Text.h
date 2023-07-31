#pragma once
#include "Renderer.h"
#include "Font.h"
#include "Core/Color.h"
#include "Core/Core.h"
#include <string>
#include <memory>

namespace kiko
{
	class Text
	{
	public:
		Text() = default;
		Text(std::shared_ptr<Font> font) : m_font{ font } {};
		~Text();
		void Create(Renderer& rend, const std::string& text, const Color& color);
		void Draw(Renderer& rend, int x, int y);
		void DrawV(Renderer& rend, const Vector2& pos);

	private:
		std::shared_ptr<Font> m_font;
		struct SDL_Texture* m_texture = nullptr;

	};
}