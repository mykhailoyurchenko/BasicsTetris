#include "Game.h"

// ����������� ����
MenuState::MenuState(Game& game) : GameState(game), playButton(Vector2f(150, 50)), playButtonText(font, "Play", 50) {
	playButton.setFillColor(Color(0, 0, 0, 0.0));
	playButton.setPosition(Vector2f(850, 500));

	playButtonText.setFillColor(Color::White);
	playButtonText.setPosition(Vector2f(900, 490));
}
// ������� ���� �� ���
void MenuState::eventHandler(Event& event) {
	GameState::eventHandler(event);
	const auto* mouseEvent = event.getIf<Event::MouseButtonPressed>();
	if (mouseEvent && mouseEvent->button == Mouse::Button::Left) { // �������� ���������� ����

		Vector2f mousePos = Vector2f(Mouse::getPosition(game->getWindow()));
		if (playButton.getGlobalBounds().contains(mousePos)) {
			game->setState(new PlayState(*game));
		}
	}
}
// ��������� �����
void MenuState::update() {
	Vector2f mousePos = Vector2f(Mouse::getPosition(game->getWindow()));
	// ���� ������� ������ 
	if (playButton.getGlobalBounds().contains(mousePos)) {
		playButtonText.setFillColor(Color::Yellow);
	}
	else playButtonText.setFillColor(Color::White);
}
// ³���������� ����
void MenuState::draw(RenderWindow& window) {
	GameState::draw(window); // ³���������
	window.draw(playButton);
	window.draw(playButtonText);
	window.display();
}	