#pragma once
#include "Framework/Resource/Resource.h"
#include "Core/Logger.h"
#include <string>

struct _TTF_Font;

namespace kiko
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();
		bool Create(std::string fileName, ...) override;
		bool Load(const std::string& filename, int fontSize);

		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}
