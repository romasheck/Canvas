
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <SFML/System/Sleep.hpp>

#include "GUI/gui.hpp"
#include "GEO/Figure.hpp"

using namespace geo;

int main()
{
/*
    gui::CanvasMaster canvas_master({1000, 1000});
    
    canvas_master.createAll();
    canvas_master.drawAll();

    canvas_master.loop();
*/
    
    Line    lne1(0, 0, 3, 0);
    Line    lne2(0, 3, 3, 3);
    Circle  cir1(sqrt(5), 1.f, 2.f);
    Circle  cir2(sqrtf(2), 3, 2.f);

    DebugTwoPoints(findIsctDots[lne1.type_][lne2.type_](&lne1, &lne2));

    return 0;

}
/*
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Circle");

    sf::CircleShape circle(500.f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1.f);
    circle.setPointCount(50); 
    circle.setPosition(100.f, 100.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}*/