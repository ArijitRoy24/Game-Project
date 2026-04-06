#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main (){
    unsigned width = 1000, height = 1000;
    RenderWindow window (VideoMode({width, height}), "Task_103");
    window.setFramerateLimit(240);
    // Circle will be stabled, and controled by arrow keys
    // circle1 will be automatically move from left to right
    CircleShape circle(60), circle1(60);
    circle.setOrigin(circle.getGeometricCenter());
    circle1.setOrigin(circle1.getGeometricCenter());
    circle.setPosition({width/2.0f, height/2.0f});
    circle1.setPosition({0+60, height/2.0f});
    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if (event->is<Event::Closed>()){
                window.close();
            }
            else if (auto key = event->getIf<Event::KeyPressed>()){
                if (key->scancode == Keyboard::Scancode::Escape){
                    window.close();
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Scancode::Left)) circle.move({-5,0});
        if (Keyboard::isKeyPressed(Keyboard::Scancode::Right)) circle.move({5,0});
        if (Keyboard::isKeyPressed(Keyboard::Scancode::Up)) circle.move({0,-5});
        if (Keyboard::isKeyPressed(Keyboard::Scancode::Down)) circle.move({0,5});
        circle.setFillColor(Color::Magenta);
        circle1.setFillColor(Color::Green);
        if (circle.getGlobalBounds().findIntersection(circle1.getGlobalBounds())){
            circle1.setFillColor(Color::Red);
            circle.setFillColor(Color::Red);
        }
        if (circle1.getPosition().x-60>width){
            circle1.setPosition({-60, height/2.0f});
        }
        circle1.move({1.0f, 0});
        window.clear();
        window.draw(circle);
        window.draw(circle1);
        window.display();
    }
    return 0;
}