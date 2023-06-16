#pragma once

#include <SFML/Graphics.hpp>

#include <Utils/Logger.h>

#include <type_traits>
#include <string>
#include <string_view>
#include <vector>

#include "Reloader/ID.h"

namespace Reloader
{
	struct Entity : public sf::Drawable, public sf::Transformable
	{
		std::string_view id;
		Entity* parent;
		std::vector<Entity*> children;

		inline Entity(Entity* parent = nullptr)
			: id(generateID()), parent(parent)
		{
		}

		template<typename T>
		inline T* AddChild()
		{
			if (!std::is_base_of<Entity, T>::value)
				return nullptr;
			T* newChild = new T(this);
			children.push_back(newChild);
			return newChild;
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override
		{
			state.transform *= this->getTransform();
			OnDraw(target, state);
			for (auto& child : children)
				target.draw(*child, state);
		}

		virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates state) const = 0;

		virtual inline ~Entity()
		{
			for(auto& child : children)
				delete child;
		}

		virtual inline const char* GetName()
		{
			return id.data();
		}
	};

}