#include "Game.h"


//����������� 
GameState::GameState(Game& game) : game(&game), tetrisText(tetrisFont, "Tetris", 70), background(backgroundTexture) {
	//���� � ������
	const filesystem::path path1 = "src/texture/background.jpg";
	const filesystem::path path2 = "src/fonts/Roboto_Condensed-Black.ttf";
	const filesystem::path path3 = "src/fonts/Oi-Regular.ttf";
	//�������� �������,������
	if (!backgroundI.loadFromFile(path1)) cerr << "������� ������� �� �����: " << path1 << endl;
	if (!font.openFromFile(path2)) cerr << "������� ������� �� �����: " << path2 << endl;
	if (!tetrisFont.openFromFile(path3)) cerr << "������� ������� �� �����: " << path3 << endl;

	//��������� ������
	tetrisText.setFillColor(Color::White);
	tetrisText.setPosition(Vector2f(200, 500));
	background.setTexture(backgroundTexture);
}
void GameState::eventHandler(Event& event) {
	if (event.is<Event::Closed>()) {
		game->getWindow().close();
	}
}
void GameState::draw(RenderWindow& window) {
	window.clear();
	window.draw(background);//��������� background
	window.draw(tetrisText);
}