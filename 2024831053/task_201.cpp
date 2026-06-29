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
    int speed = 10;
    window.setFramerateLimit(speed);

    deque<Vector2i> snake;

    snake.push_back({10,10});
    snake.push_back({9,10});
    snake.push_back({8,10});

    Direction dir = RIGHT;

    Vector2i food(rand()%COLS, rand()%ROWS);
    Vector2i bigFood;

    bool showBigFood = false;

    int normalFoodCount = 0;

    bool gameOver = false;

    RectangleShape block(Vector2f(CELL-1,CELL-1));
    block.setFillColor(Color::Green);

    RectangleShape foodShape(Vector2f(CELL-1,CELL-1));
    foodShape.setFillColor(Color::Red);

    RectangleShape bigFoodShape(Vector2f(CELL-1,CELL-1));
    bigFoodShape.setFillColor(Color::Yellow);

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
                normalFoodCount++;
                if(speed < 30)   // Maximum speed
                {
                    speed++;
                    window.setFramerateLimit(speed);
                }

                bool ok = false;

                while(!ok){
                    ok = true;

                    food.x = rand()%COLS;
                    food.y = rand()%ROWS;

                    for(auto &p : snake){
                        if(p == food){
                            ok = false;
                            break;
                        }
                    }
                }

                if(normalFoodCount == 5){
                    showBigFood = true;
                    normalFoodCount = 0;

                    bool ok2 = false;

                    while(!ok2){
                        ok2 = true;

                        bigFood.x = rand()%COLS;
                        bigFood.y = rand()%ROWS;

                        for(auto &p : snake){
                            if(p == bigFood){
                                ok2 = false;
                                break;
                            }
                        }
                    }
                }
            }
            else if(showBigFood && head==bigFood){
                showBigFood = false;

                if(speed < 30){
                    speed += 2;

                    if(speed > 30)
                        speed = 30;

                    window.setFramerateLimit(speed);
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

        if(showBigFood){
            bigFoodShape.setPosition(Vector2f(bigFood.x*CELL,bigFood.y*CELL));
            window.draw(bigFoodShape);
        }

        window.display();
    }

    return 0;
}