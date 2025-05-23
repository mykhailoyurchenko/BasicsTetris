#include <SFML/Graphics.hpp>
#include <Menu.h>
#include <random>
#include <sstream>

using namespace sf;
using namespace std;


int main()
{
	vector<RectangleShape> rectangles;

	RenderWindow window(VideoMode({ 1920, 1080 }), "Tetris", Style::Default,State::Fullscreen);
	window.setFramerateLimit(60);

	RectangleShape game(Vector2f(400, 550));
	RectangleShape button1(Vector2f(200, 50));
	RectangleShape button2(Vector2f(200, 50));

	Texture backgroundTexture("src/texture/background.jpg");
	Sprite background(backgroundTexture);
	Font font;

	if (!backgroundTexture.loadFromFile("src/texture/background.jpg")) return -1; // Помилка завантаження
	if (!font.openFromFile("src/fonts/Roboto_Condensed-Black.ttf")) return -1;

	game.setFillColor(Color(0, 0, 0, 12));
	game.setPosition(Vector2f(750, 500));
	//квадрат/кнопка
	button1.setFillColor(Color(0, 100, 100, 128));
	button1.setPosition(Vector2f(850, 500));

	button2.setFillColor(Color(0, 0, 0, 70));
	button2.setPosition(Vector2f(1450, 500));
	

	//налаштування тексту
	Text textButton1(font,"Play",50);
	Text goBack(font, "Go back", 50);
	Text scoreText(font, "0", 40);

	textButton1.setFillColor(Color::White);
	textButton1.setPosition(Vector2f(900, 490));

	goBack.setFillColor(Color::White);
	goBack.setPosition(Vector2f(1475, 490));

	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(50, 50));


	int scoreCounrter = 0;
	while (window.isOpen()) {

		//відстежувіння мишки
		//float mouseX = Mouse::getPosition(window).x;
		//float mouseY = Mouse::getPosition(window).y;

		Vector2f mousePos = Vector2f(Mouse::getPosition(window));

		if (button1.getGlobalBounds().contains(mousePos)) {
			button1.setFillColor(Color(20, 90, 0));
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				RectangleShape tetrisRect(Vector2f(500, 900));
				tetrisRect.setFillColor(sf::Color::Black);
				tetrisRect.setPosition(Vector2f(700, 50));
				rectangles.push_back(tetrisRect);
				button1.setFillColor(Color::Yellow);

			}
			else {
				button1.setFillColor(Color(0, 0, 0, 12));
			}
		}

		if (button2.getGlobalBounds().contains(mousePos)) {
			button2.setFillColor(Color(20, 90, 0));
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				if (!rectangles.empty()) {
					rectangles.pop_back(); // Remove last rectangle

				}
				button2.setFillColor(Color::Yellow);
			}
		}
		else {
			button2.setFillColor(Color(0, 20, 100, 70));
		}

		//обробка події закриття
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>())
				window.close();
		}

		ostringstream scoreLeadOut;
		scoreLeadOut << "Score: " << scoreCounrter;
		scoreText.setString(scoreLeadOut.str());

		//рендер
		window.clear();
		window.draw(background);
		window.draw(button1);
		window.draw(button2);
		window.draw(textButton1);
		window.draw(scoreText);
		window.draw(goBack);



		for (const auto& tetrisRect : rectangles) {
			window.draw(tetrisRect);
		}
		window.display();

	}
}