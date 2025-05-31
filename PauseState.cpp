#include "States.h"

PauseState::PauseState(Game& game) : PlayState(game), pauseOverlay(Vector2f(1920, 1080)), pauseResumeText(font, "Resume", 50), pauseQuitText(font, "Quit", 50) {

	pauseOverlay.setFillColor(Color(0, 0, 0, 150));

	pauseResumeText.setFillColor(Color::White);
	pauseResumeText.setPosition(Vector2f(800, 400));

	pauseQuitText.setFillColor(Color::White);
	pauseQuitText.setPosition(Vector2f(800, 500));
}  
void PauseState::draw(RenderWindow& window) {
	PlayState::draw(window);
	window.draw(pauseOverlay);
	window.draw(pauseResumeText);
	window.draw(pauseQuitText);

}
void PauseState::eventHandler(Event& event) {
	PlayState::eventHandler(event);

	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) {};
}
void PauseState::update() {
	PlayState::update();

}