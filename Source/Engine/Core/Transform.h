#pragma once
#include "../Core/Core.h"
#include "../Core/Vector2.h"

namespace kiko 
{
	class Transform 
	{
	public:
		Vector2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const Vector2 position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

	private:

	};
}