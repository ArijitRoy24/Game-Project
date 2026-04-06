#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main (){
    unsigned width = 1000, height = 1000;
    RenderWindow window (VideoMode({width, height}), "Task_102");
    window.setFramerateLimit(240);
    float radius = 60;
    CircleShape circle(radius);
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
        radius+=1;
        circle.setRadius(radius);
        circle.setOrigin(circle.getGeometricCenter());
        if (radius == min(height,width)/2){
            radius = 60;
        }
        window.clear();
        window.draw(circle);
        window.display();
    }
    return 0;
}