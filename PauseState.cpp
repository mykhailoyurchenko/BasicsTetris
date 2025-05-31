#include "States.h"
#include "Game.h"


PauseState::PauseState(Game& game) : PlayState(game), pauseOverlay(Vector2f(1920, 1080)), ResumeText(font, "Resume", 50), MainMenuText(font, "MainMenu", 50),
box(Vector2f(400,600)){
	
	box.setPosition(Vector2f(750, 200));
	box.setFillColor(Color(40, 39, 39, 255));
	
	pauseOverlay.setFillColor(Color(0, 0, 0, 155));

	ResumeText.setFillColor(Color::White);
	ResumeText.setPosition(Vector2f(800, 400));

	MainMenuText.setFillColor(Color::White);
	MainMenuText.setPosition(Vector2f(800, 500));
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

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {
		if (MainMenuText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<MenuState>();
			return;
		}
		if (ResumeText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState<PlayState>();
			
		}
	};
}
void PauseState::update() {
	if (MainMenuText.getGlobalBounds().contains(game->getMousePos())) {
		MainMenuText.setFillColor(Color::Yellow);
	}
	else MainMenuText.setFillColor(Color(255, 255, 255, 255));

	if (ResumeText.getGlobalBounds().contains(game->getMousePos())) {
		ResumeText.setFillColor(Color::Yellow);
	}
	else ResumeText.setFillColor(Color(255, 255, 255, 255));
}