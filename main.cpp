#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(VideoMode({1920, 1080}), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        //window.clear();
        //window.draw(shape);
        //window.display();
    }
}