#include <SFML/Graphics.hpp>
#include <deque>
#include <optional>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

const int WIDTH = 1500;
const int HEIGHT = 1000;
const int CELL = 25;

const int COLS = WIDTH / CELL;
const int ROWS = HEIGHT / CELL;

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int main(){
    srand(time(nullptr));

    RenderWindow window(VideoMode({WIDTH, HEIGHT}), "Task_201");
    window.setFramerateLimit(10);

    deque<Vector2i> snake;

    snake.push_back({10,10});
    snake.push_back({9,10});
    snake.push_back({8,10});

    Direction dir = RIGHT;

    Vector2i food(rand()%COLS, rand()%ROWS);

    bool gameOver = false;

    RectangleShape block(Vector2f(CELL-1,CELL-1));
    block.setFillColor(Color::Green);

    RectangleShape foodShape(Vector2f(CELL-1,CELL-1));
    foodShape.setFillColor(Color::Red);

    while(window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<Event::Closed>()){
                window.close();
            }
            if (auto key = event->getIf<sf::Event::KeyPressed>()){
                if (key->code == sf::Keyboard::Key::Escape){
                    window.close();
                }
                else if (key->code == Keyboard::Key::Up){
                    if (dir != DOWN) dir = UP;
                }
                else if (key->code == Keyboard::Key::Down){
                    if (dir != UP) dir = DOWN;
                }
                else if (key->code == Keyboard::Key::Left){
                    if (dir != RIGHT) dir = LEFT;
                }
                else if (key->code == Keyboard::Key::Right){
                    if (dir != LEFT) dir = RIGHT;
                }
            }
        }

        if(!gameOver){
            Vector2i head = snake.front();

            if(dir==UP) head.y--;
            if(dir==DOWN) head.y++;
            if(dir==LEFT) head.x--;
            if(dir==RIGHT) head.x++;

            if(head.x<0 || head.x>=COLS || head.y<0 || head.y>=ROWS) gameOver=true;

            for(size_t i=0;i<snake.size();i++){
                if(head==snake[i]){
                    gameOver=true;
                    break;
                }
            }

            snake.push_front(head);

            if(head==food){
                bool ok=false;

                while(!ok){
                    ok=true;
                    food.x=rand()%COLS;
                    food.y=rand()%ROWS;

                    for(auto &p:snake){
                        if(p==food){
                            ok=false;
                            break;
                        }
                    }
                }
            }
            else{
                snake.pop_back();
            }
        }

        window.clear(Color::Black);

        for(auto &p:snake){
            block.setPosition(Vector2f(p.x*CELL,p.y*CELL));
            window.draw(block);
        }

        foodShape.setPosition(Vector2f(food.x*CELL,food.y*CELL));

        window.draw(foodShape);

        window.display();
    }

    return 0;
}