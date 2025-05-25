#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameState {
	public:
		virtual void eventHandler(Event& event) {};
		virtual void update(Time dt) {};
		virtual void draw(RenderWindow& window) {};
		virtual ~GameState() = default;
};