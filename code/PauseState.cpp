#include "Game.h"

PauseState::PauseState(Game& game) : PlayState(game), 
	pauseOverlay(Vector2f(game.getWindow().getSize())), 
	ResumeText(font, "Resume", 50), 
	MainMenuText(font, "Main Menu", 50), 
	box(Vector2f(400, 600)) // Reverted to fixed size
{
	Vector2u winSize = game.getWindow().getSize();
	
	// Keep relative positioning for the box and buttons
	box.setPosition(Vector2f(winSize.x * 0.39f, winSize.y * 0.18f)); // Саня, побачиш - виправиш
	box.setFillColor(Color(40, 39, 39, 255));
	
	pauseOverlay.setFillColor(Color(0, 0, 0, 155));

	// Кнопка Resume
	ResumeText.setPosition({ winSize.x * 0.49f, winSize.y * 0.40f });

	// Кнопка MainMenu
	MainMenuText.setPosition({ winSize.x * 0.49f, winSize.y * 0.50f });	
}  
void PauseState::draw(RenderWindow& window) {
	PlayState::draw(window);
	window.draw(pauseOverlay);
	window.draw(box);
	window.draw(MainMenuText);
	window.draw(ResumeText);
}
void PauseState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	Vector2f mousePos = game->getMousePos();

	if (MainMenuText.isClicked(mousePos, event)) {
		game->setState<MenuState>();
	}
	else if (ResumeText.isClicked(mousePos, event)) {
		game->setState<PlayState>();
	}
}
void PauseState::update(const Time& delta) {
	Vector2f mousePos = game->getMousePos();
	MainMenuText.update(mousePos);
	ResumeText.update(mousePos);
}