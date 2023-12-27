#include <iostream>
#include <vector>
#include <string>
#include <imgui-SFML.h>


#include <SFML/Graphics.hpp>

#include "Reloader/Entity.h"

struct EntityA : public Reloader::Entity
{
	sf::CircleShape shape;
	EntityA(Reloader::Entity* parent = nullptr)
		: Reloader::Entity(parent)
	{
		shape.setRadius(5);
		this->setPosition(50, 60);
	}

	inline void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(shape, states);
	}

	inline const char* GetName() override
	{
		return "EntityA";
	}
};

int main(int argc, const char* argv[])
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	EntityA a;
	auto b = a.AddChild<EntityA>();
	auto c = a.AddChild<EntityA>();
	b->setPosition(42, 41);
	c->setPosition(131, 49);
	sf::RenderWindow window(sf::VideoMode(800, 600), "App", sf::Style::Default, settings);
	Util::Logger::Debug("{}", a.GetName());

	ImGui::SFML::Init(window, true);

	sf::Clock clk;
	while (window.isOpen())
	{
		auto dt = clk.restart();
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
				break;
			}
			ImGui::SFML::ProcessEvent(event);
		}

		ImGui::SFML::Update(window, dt);

		if (ImGui::Begin("Debug Window"))
		{
			if (ImGui::Button("Press me"))
			{
				Util::Logger::Info("Button Pressed");
			}
			ImGui::End();
		}
		Util::Logger::Draw("Log Window");


		window.clear();
		window.draw(a);

		ImGui::SFML::Render(window);
		window.display();
	}
	return 0;
}