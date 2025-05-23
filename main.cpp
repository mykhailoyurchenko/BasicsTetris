#include <SFML/Graphics.hpp>
#include <Menu.h>
#include <sstream>

using namespace sf;
using namespace std;

vector<RectangleShape> rectangles;

void createButton(RectangleShape button, float mouseX,float mouseY) {
	float lBorderB1 = button.getPosition().x;
	float dBorderB1 = button.getPosition().y;
	float rBorderB1 = lBorderB1 + button.getSize().x;
	float uBorderB1 = dBorderB1 + button.getSize().y;
	//перевірка на взаємодію з кноакою
	if ((mouseX >= lBorderB1) && (mouseX <= rBorderB1) && (mouseY >= dBorderB1) && (mouseY <= uBorderB1)) {
		button.setFillColor(Color(20, 90, 0));
		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			RectangleShape tetrisRect(Vector2f(500, 900));
			tetrisRect.setFillColor(sf::Color::Black);
			tetrisRect.setPosition(Vector2f(700, 50));
			rectangles.push_back(tetrisRect);
			button.setFillColor(Color::Yellow);

		}
		else {
			button.setFillColor(Color(0, 0, 0, 12));
		}
	}

}

int main()
{
	RenderWindow window(VideoMode({ 1920, 1080 }), "Tetris");
	window.setFramerateLimit(60);

	
	RectangleShape rect;
	rect.setFillColor(Color(0, 0, 0, 12));
	rect.setPosition(Vector2f(750, 500));
	rect.setSize(Vector2f(400, 550));


	//квадрат/кнопка
	RectangleShape button1;
	button1.setFillColor(Color(0, 100, 100, 128));
	button1.setPosition(Vector2f(850, 500));
	button1.setSize(Vector2f(200, 50));


	RectangleShape button2;
	button2.setFillColor(Color(0, 0, 0, 12));
	button2.setPosition(Vector2f(1450, 500));
	button2.setSize(Vector2f(200, 50));

	//налаштування фону
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("src/texture/background.jpg")) {
		return -1; // Помилка завантаження
	}
	
	Sprite background(backgroundTexture);
	background.setTexture(backgroundTexture);

	//налаштування шрифта
	Font font;
	if (!font.openFromFile("src/fonts/Roboto_Condensed-Black.ttf")) return -1;

	//налаштування тексту
	Text textButton1(font);
	textButton1.setString("play");
	textButton1.setCharacterSize(50);
	textButton1.setFillColor(Color::White);
	textButton1.setPosition(Vector2f(900, 490));

	int score = 0;
	Text scoreText(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(Vector2f(50, 50));

	while (window.isOpen()) {

		//відстежувіння мишки
		float mouseX = Mouse::getPosition(window).x;
		float mouseY = Mouse::getPosition(window).y;

		//кординати кінця і початку кнопки
		createButton(button1, mouseX, mouseY);

		float lBorderB2 = button2.getPosition().x;
		float dBorderB2 = button2.getPosition().y;
		float rBorderB2 = lBorderB2 + button2.getSize().x;
		float uBorderB2 = dBorderB2 + button2.getSize().y;

		if ((mouseX >= lBorderB2) && (mouseX <= rBorderB2) && (mouseY >= dBorderB2) && (mouseY <= uBorderB2)) {
			button2.setFillColor(Color(20, 90, 0));
			if (Mouse::isButtonPressed(Mouse::Button::Left)) {
				if (!rectangles.empty()) {
					rectangles.pop_back(); // Remove last rectangle

				}
				button2.setFillColor(Color::Yellow);
			}
		}
		else {
			button2.setFillColor(Color(0, 0, 0, 12));
		}

		//обробка події закриття
		while (const optional event = window.pollEvent()) {
			if (event->is<Event::Closed>())
				window.close();
		}

		ostringstream ss;
		ss << "Score: " << score;
		scoreText.setString(ss.str());

		//рендер
		window.clear();
		window.draw(background);
		window.draw(button1);
		window.draw(button2);
		window.draw(textButton1);
		window.draw(scoreText);
		for (const auto& tetrisRect : rectangles)
			window.draw(tetrisRect);
		window.display();

	}
}