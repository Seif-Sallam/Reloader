#include "Reloader/MainCharacter.h"

namespace Reloader
{
	MainCharacter::MainCharacter(Entity* parent, sf::Vector2f torsoPosition)
		: Entity(parent)
	{
		// BAD make it dynamic using dev tools and imgui
		std::array<sf::Vector2f, 6> partsSize = {
			sf::Vector2f{25.f, 25.f},
			sf::Vector2f{50.f, 100.f},
			sf::Vector2f{15.f, 80.f},
			sf::Vector2f{15.f, 80.f},
			sf::Vector2f{15.f, 120.f},
			sf::Vector2f{15.f, 120.f},
		};
		for (size_t i = 0; i < mBodyParts.size(); ++i)
		{
			auto& part = mBodyParts[i];
			part = new BodyPart(this, partsSize[i]);
		}
	}

	MainCharacter::~MainCharacter()
	{
	}

	void MainCharacter::OnDraw(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}
}