#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <States.h>


using namespace sf;
using namespace std;


int mainOld()
{
	if (true) return 1;
	vector<RectangleShape*> rectangles;
	vector<Text*> texts;

	RenderWindow window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default, State::Fullscreen);
	window.setFramerateLimit(60);
	Image icon;
	if (!icon.loadFromFile("src/texture/icon.png")) return -1; // Помилка завантаження
	window.setIcon(icon);

	RectangleShape game(Vector2f(500, 900));
	RectangleShape playButton(Vector2f(150, 50));
	RectangleShape backButton(Vector2f(150, 50));


	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("src/texture/background.jpg")) return -1; // Помилка завантаження
	Sprite background(backgroundTexture);

	Font tetrisFont;
	Font font;

	if (!font.openFromFile("src/fonts/Roboto_Condensed-Black.ttf")) return -1;
	if (!tetrisFont.openFromFile("src/fonts/Oi-Regular.ttf")) return -1; // Помилка завантаження

	game.setFillColor(Color::Black);
	game.setPosition(Vector2f(700, 50));

	//квадрат/кнопка
	playButton.setFillColor(Color(0, 0, 0, 0.0));
	playButton.setPosition(Vector2f(850, 500));
	rectangles.push_back(&playButton);

	backButton.setFillColor(Color(0, 0, 0, 0.0));
	backButton.setPosition(Vector2f(1750, 50));
	rectangles.push_back(&backButton);

	//налаштування тексту
	Text playButtonText(font, "Play", 50);
	Text backButtonText(font, "Go back", 50);
	Text scoreText(font, "0", 40);
	Text tetrisText(tetrisFont, "Tetris", 70);


	playButtonText.setFillColor(Color::White);
	playButtonText.setPosition(Vector2f(900, 490));
	texts.push_back(&playButtonText);

	backButtonText.setFillColor(Color::White);
	backButtonText.setPosition(Vector2f(1475, 490));
	texts.push_back(&backButtonText);

	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(50, 50));
	texts.push_back(&scoreText);

	tetrisText.setFillColor(Color::White);
	tetrisText.setPosition(Vector2f(200, 500));
	texts.push_back(&tetrisText);


	int scoreCounrter = 0;
	while (window.isOpen()) {

		//відстежувіння мишки
		//float mouseX = Mouse::getPosition(window).x;
		//float mouseY = Mouse::getPosition(window).y;

		Vector2f mousePos = Vector2f(Mouse::getPosition(window));

		if (playButton.getGlobalBounds().contains(mousePos)) {
			playButtonText.setFillColor(Color::Yellow);
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				rectangles.push_back(&game);
				auto i = find(texts.begin(), texts.end(), &playButtonText);
				if (i != texts.end()) {
					texts.erase(i);
				}
				auto j = find(rectangles.begin(), rectangles.end(), &playButton);
				if (j != rectangles.end()) {
					rectangles.erase(j);
				}
			}
		}
		else {
			playButtonText.setFillColor(Color::White);
		}
		if (backButton.getGlobalBounds().contains(mousePos)) {
			backButton.setFillColor(Color(20, 90, 0));
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				auto i = find(rectangles.begin(), rectangles.end(), &game);
				if (i != rectangles.end()) {
					rectangles.erase(i);
				}
				texts.push_back(&playButtonText);
				rectangles.push_back(&playButton);
				backButton.setFillColor(Color::Yellow);
			}
		}
		else {
			backButton.setFillColor(Color(0, 20, 100, 70));
		}

		//обробка події закриття
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>()) {
				window.close();
			}
			if (event->is<Event::KeyPressed>()) {

			}
		}

		ostringstream scoreLeadOut;
		scoreLeadOut << "Score: " << scoreCounrter;
		scoreText.setString(scoreLeadOut.str());

		//рендер
		window.clear();
		window.draw(background);

		for (const auto& tetrisRect : rectangles) {
			window.draw(*tetrisRect);
		}
		for (const auto& tetrisText : texts) {
			window.draw(*tetrisText);
		}

		window.display();
	}
	rectangles.clear();
	texts.clear();
}