#pragma once

#include <array>

#include "Entity.h"

namespace Reloader
{
	class BodyPart : public Entity
	{
	public:
		BodyPart(Entity* parent = nullptr, sf::Vector2f size = {10, 10})
			: Entity(parent), mPart(size)
		{
		}

		void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(mPart, states);
		}

		sf::RectangleShape mPart;
	};

	class MainCharacter : public Entity
	{
	public:
		MainCharacter(Entity* parent = nullptr, sf::Vector2f torsoPosition = {});
		~MainCharacter();

		void OnDraw(sf::RenderTarget& target, sf::RenderStates state) const override;

	private:
		enum
		{
			HEAD = 0,
			TORSO,
			RIGHT_ARM,
			LEFT_ARM,
			RIGHT_LEG,
			LEFT_LEG
		};
		std::array<BodyPart*, 6> mBodyParts;
	};
}