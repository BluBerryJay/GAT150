#include "Text.h"
#include "Font.h"

#include <SDL2-2.28.0/include/SDL_ttf.h>
namespace kiko
{
	Text::~Text()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);

	}
	void Text::Create(Renderer& rend, const std::string& text, const Color& color)
	{
		SDL_Color c{ Color::ToInt(color.r), Color::ToInt(color.g), Color::ToInt(color.b), Color::ToInt(color.a) };
		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
		m_texture = SDL_CreateTextureFromSurface(rend.m_renderer, surface);

		SDL_FreeSurface(surface);
	}
	void Text::Draw(Renderer& rend, int x, int y)
	{
		int width, height;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
		SDL_Rect rect{ x, y, width, height };
		SDL_RenderCopy(rend.m_renderer, m_texture, NULL, &rect);

	}
	void Text::DrawV(Renderer& rend, const Vector2& pos)
	{
		int width, height;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
		SDL_Rect rect{ (int)pos.x - 35, (int)pos.y+20, width, height };
		SDL_RenderCopy(rend.m_renderer, m_texture, NULL, &rect);
	}
}