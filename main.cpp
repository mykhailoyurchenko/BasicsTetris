#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;








int main()
{


    RenderWindow window(VideoMode({1920, 1080}), "Tetris");

    std::vector<sf::CircleShape> circles;

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
        rectButton2.setPosition(Vector2f(850, 900));
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
    textButton1.setString("text");
    textButton1.setCharacterSize(50);
    textButton1.setFillColor(Color::White);
    textButton1.setPosition(Vector2f(850, 500));

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

        //перевірка на взаємодію з кноакою
        if ((mouseX >= x1)and(mouseX <= x2) and (mouseY >= y1)  and (mouseY <= y2)) {
            rectButton1.setFillColor(Color(20, 90, 0));
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                sf::CircleShape circle(30.f);
                circle.setFillColor(sf::Color::Green);
                circle.setPosition(Vector2f(400, 300));
                circles.push_back(circle);
                rectButton1.setFillColor(Color::Yellow);
            }
        } else {
            rectButton1.setFillColor(Color((0, 0, 0, 12)));
        }


        //обробка події закриття
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();
        }

        //рендер
        window.clear();
        window.draw(background);
        window.draw(rectButton1);
        window.draw(rectButton2);
        window.draw(textButton1);

        for (const auto& circle : circles)
            window.draw(circle);

        window.display();
    }
}