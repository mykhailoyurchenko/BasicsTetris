#include "Game.h"


PauseState::PauseState(Game& game) : PlayState(game), pauseOverlay(Vector2f(1920, 1080)), ResumeText(font, "Resume", 50), 
MainMenuText(font, "Main Menu", 50), box(Vector2f(400,600)){
	Vector2u winSize = game.getWindow().getSize();
	
	box.setPosition(Vector2f(750, 200)); // Саня, побачиш - виправиш
	box.setFillColor(Color(40, 39, 39, 255));
	
	pauseOverlay.setFillColor(Color(0, 0, 0, 155));

	// Кнопка Resume
	ResumeText.setFillColor(Color::White);
	ResumeText.setPosition({ winSize.x * 0.49f, winSize.y * 0.40f });
	centerOrigin(ResumeText);

	// Кнопка MainMenu
	MainMenuText.setFillColor(Color::White);
	MainMenuText.setPosition({ winSize.x * 0.49f, winSize.y * 0.50f });
	centerOrigin(MainMenuText);
	
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
			game->setState(GameStateType::Menu);
			return;
		}
		if (ResumeText.getGlobalBounds().contains(game->getMousePos())) {
			game->setState(GameStateType::Play);
		}
	};
}
void PauseState::update(const Time& delta) {
	if (MainMenuText.getGlobalBounds().contains(game->getMousePos())) {
		MainMenuText.setFillColor(Color::Yellow);
	}
	else MainMenuText.setFillColor(Color::White);

	if (ResumeText.getGlobalBounds().contains(game->getMousePos())) {
		ResumeText.setFillColor(Color::Yellow);
	}
	else ResumeText.setFillColor(Color::White);
}