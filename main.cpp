#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{

    RenderWindow window(VideoMode({1920, 1080}), "Tetris");

    std::vector<sf::RectangleShape> rectagles;

    RectangleShape rect;
    rect.setFillColor(Color(0, 0, 0, 12));
    rect.setPosition(Vector2f(750, 500));
    rect.setSize(Vector2f(400, 550));

        //квадрат/кнопка
        RectangleShape rectButton1;
        rectButton1.setFillColor(Color(0, 100, 100, 128));
        rectButton1.setPosition(Vector2f(850, 500));
        rectButton1.setSize(Vector2f(200, 50));


        RectangleShape rectButton2;
        rectButton2.setFillColor(Color(0, 0, 0, 12));
        rectButton2.setPosition(Vector2f(1450, 500));
        rectButton2.setSize(Vector2f(200, 50));



    window.setFramerateLimit(60);


    //налаштування фону
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("texture/background.jpg");
    Sprite background(backgroundTexture);
    background.setTexture(backgroundTexture);

    //налаштування шрифта
    Font font;
    if (!font.openFromFile("fonts/Roboto_Condensed-Black.ttf"))return 3;

    //налаштування тексту
    Text textButton1(font);
    textButton1.setString("play");
    textButton1.setCharacterSize(50);
    textButton1.setFillColor(Color::White);
    textButton1.setPosition(Vector2f(900, 490));

    int score = 0;
    sf::Text scoreText(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(Vector2f(50, 50));


    //перевірка чи рендериця фон
    if (!backgroundTexture.loadFromFile("texture/background.jpg")) {
        return -1; // Помилка завантаження
    }

    bool showRectangle = false;

    while (window.isOpen()){


        //відстежувіння мишки
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;


        //кординати кінця і початку кнопки
        float x1 = rectButton1.getPosition().x;
        float y1 = rectButton1.getPosition().y;
        float x2 = x1 + rectButton1.getSize().x;
        float y2 = y1 + rectButton1.getSize().y;

        float x11 = rectButton2.getPosition().x;
        float y11 = rectButton2.getPosition().y;
        float x22 = x11 + rectButton2.getSize().x;
        float y22 = y11 + rectButton2.getSize().y;

        //перевірка на взаємодію з кноакою
        if ((mouseX >= x1) && (mouseX <= x2) && (mouseY >= y1)  && (mouseY <= y2)) {
            rectButton1.setFillColor(Color(20, 90, 0));
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                RectangleShape tetrisRect(Vector2f(500, 900));
                tetrisRect.setFillColor(sf::Color::Black);
                tetrisRect.setPosition(Vector2f(700, 50));
                rectagles.push_back(tetrisRect);
                rectButton1.setFillColor(Color::Yellow);

            }
        } else {
            rectButton1.setFillColor(Color((0, 0, 0, 12)));
        }

        if ((mouseX >= x11) && (mouseX <= x22) && (mouseY >= y11) && (mouseY <= y22)) {
            rectButton2.setFillColor(Color(20, 90, 0));
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                if (!rectagles.empty()) {
                    rectagles.pop_back(); // Remove last rectangle

                }
                rectButton2.setFillColor(Color::Yellow);
            }
        }else {
            rectButton2.setFillColor(Color((0, 0, 0, 12)));
        }

        //обробка події закриття
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        std::ostringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());

        //рендер
        window.clear();
        window.draw(background);
        window.draw(rectButton1);
        window.draw(rectButton2);
        window.draw(textButton1);
        window.draw(scoreText);
        for (const auto& tetrisRect : rectagles)
            window.draw(tetrisRect);

        window.display();
    }
}