#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <SFML/System/Sleep.hpp>

#include "GUI/gui.hpp"
//#include <Mouse.hpp>

void foo_test(gui::coordinate a)
{
    printf("coord is (%f, %f)\n", a.x_, a.y_);
}

int main()
{
    gui::CanvasMaster canvas_master({1000, 1000});
    
    //gui::coordinate a(0.1, 0.1);
    //foo_test(a);
    //std::cout<<"0.1 -> Pixels: "<<canvas_master.locationToPosition(a).x_<<std::endl;
    canvas_master.createAll();
    canvas_master.drawAll();

    canvas_master.loop();
    /*sf::RenderWindow window(sf::VideoMode(1200, 800), "SFML works!");
    sf::CircleShape shape(400.f);
    shape.setFillColor(sf::Color::Green);
    //sf::CircleShape circle_click(10.f);
    
    sf::CircleShape quadro;
    //quadro.setSize({40.f, 40.f});
    quadro.setRadius(20.f);
    quadro.setFillColor(sf::Color::Red);
    //quadro.setPosition({0.f, 0.f});
    window.draw(quadro);
    while (window.isOpen())
    {
        sf::sleep(sf::milliseconds(300));
        sf::Event event;
        //quadro.setPosition({1.f, 1.f});
        
        while (window.pollEvent(event))
        {
            /*if (event.type == sf::Event::MouseButtonPressed)
            {
                //quadro.setFillColor(sf::Color::Blue);
                
                //circle_click.setFillColor(sf::Color::Blue);
                //quadro.setPosition(sf::Vector2f(sf::Mouse::getPosition().x - window.getPosition().x - 10, sf::Mouse::getPosition().y - window.getPosition().y - 23));
                quadro.setPosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                std::cout<<event.mouseButton.x<<" "<<event.mouseButton.y<<std::endl;
                //window.draw(circle_click);
                //window.close();
                window.draw(quadro);
            }*//*
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.clear();
        //window.draw(shape);
        window.display();
    }*/

    return 0;
}