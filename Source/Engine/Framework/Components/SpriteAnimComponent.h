#pragma once
#include "SpriteComponent.h"
namespace kiko
{
	class SpriteAnimComponent : public SpriteComponent
	{
	public:
		CLASS_DECLARATION(SpriteAnimComponent);
		struct AnimSequence
		{
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};
	public:
		
		bool Initialize() override;
		void SetSequence(const std::string name, bool update = true);
		void UpdateSource();
		void Update(float dt) override;
		virtual float GetRadius() override { return m_texture->GetSize().Length() * 0.5f; }
	public:
		int frame = 0;
		float frameTimer = 0;
	private:
		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> m_sequences;
		AnimSequence* m_sequence = nullptr;
		
	};
}