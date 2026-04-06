#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main (){
    unsigned width = 1000, height = 1000;
    RenderWindow window (VideoMode({width, height}), "Task_101");
    window.setFramerateLimit(240);
    CircleShape circle(60);
    circle.setOrigin(circle.getGeometricCenter());
    circle.setPosition({width/2.0f, height/2.0f});
    circle.setFillColor(Color::Magenta);
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
        window.clear();
        window.draw(circle);
        window.display();
    }
    return 0;
}