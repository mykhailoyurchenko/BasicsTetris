#pragma once

using namespace sf;


class GameState {
	public:
		virtual void handleEvent(Event& event) = 0;
		virtual void update(sf::Time dt) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual ~GameState() = default;
};