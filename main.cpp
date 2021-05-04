#include <iostream>
#include <BearLibTerminal.h>
#include <vector>
#include <cmath>
using namespace std;

int to_pos(float x){

    return static_cast<int>(round(x));
}
class Controls{
    bool isJump_ = false;
    bool isExit_ = false;
public:
    bool isJump() const{
        return isJump_;
    }

    bool isExit() const {
        return isExit_;
    }

    void update(){
        isJump_ = false;
        isExit_ = false;
        while(terminal_has_input()){


            auto key = terminal_read();
            if(key == TK_SPACE){
                isJump_ = true;
            }
            if(key == TK_CLOSE){
                isExit_ = true;
            }
        }
    }
};

class Player{
    float speed_y = 0;
    char symbol = '@';

    const Controls& controls;

private:
    float x_;
    float y_;
    float max_jump_height_;
    float max_speed_y;
    float ground_y;
    float gravity;

    bool isFlying() const{
        return  y_ < ground_y;
    }

    void Render(){
        terminal_put(to_pos(x_),to_pos(y_),symbol);
    }
    void Move(){
        if(controls.isJump() && !isFlying()){
            speed_y = max_speed_y;
        }
        if(y_ >= ground_y){
            y_ = ground_y;
        }
        if(y_<= ground_y- max_jump_height_){
            speed_y = 0;
        }
        y_-= speed_y;
        y_ += gravity;
    }

public:
    Player(const Controls &controls, float x, float y, float maxJumpHeight, float maxSpeedY, float ground_y,float gravity) : controls(controls), x_(x), y_(y),
                                                                                                                           max_jump_height_(maxJumpHeight),
                                                                                                                           max_speed_y(maxSpeedY),ground_y(ground_y),gravity(gravity) {}
    void update(){
        Move();
        Render();
    }

    int GetX() const {
        return to_pos(x_);
    }

    int GetY() const {
        return to_pos(y_);
    }

};
class Obstacle{
    char symbol = '#';
public:
    float x;
    float y;

    Obstacle(float x, float y) : x(x), y(y) {}

    void update(){
        terminal_put(to_pos(x), to_pos(y),symbol);
    }
};

class ObstacleManager{
    const Player& player_;
    float ground_y;
    int world_width;
    float speed_x;
    vector<Obstacle> obstacles{{20,ground_y},{40,ground_y },{70,ground_y}};
public:
    ObstacleManager(const Player player,float groundY, int worldWidth, float speedX) : player_(player),ground_y(groundY), world_width(worldWidth),speed_x(speedX) {}

    void update(){
        for (auto& o: obstacles) {
            o.x-=speed_x;
            if(o.x<=0)
                o.x = world_width;

            if(player_.GetX() == to_pos(o.x) && player_.GetY() == to_pos(ground_y)){
                terminal_print(1,1,"BUM");
                //game_over = true;
            }
            o.update();
        }
    }
};
class Ground{
    char symbol_;
    int width_;
    int y_;
public:
    Ground(char symbol, int width, int y) : symbol_(symbol), width_(width), y_(y) {}
public:
    void update(){
        for (int i = 0; i < width_; ++i) {
            terminal_put(i, y_ + 1, symbol_);
        }
    }
};

int main()
{
    terminal_open();
    terminal_refresh();


    const int ground_y = 15;
    const int width = 80;
    const float gravity = 0.15;

    Controls controls;
    Player player{controls,2,ground_y,4.5,gravity*3,ground_y,gravity};
    ObstacleManager manager{player,ground_y,width,0.15};
    Ground ground{'^',width,ground_y};

    // Ждем, пока пользователь не закроет окно
    while (true){
        terminal_clear();

        controls.update();

        if(controls.isExit())
            break;

        manager.update();

//        if(game_over){
//            terminal_print(1,1,"GAME OVER");
//            terminal_refresh();
//            continue;
//        }

        player.update();
        ground.update();

        terminal_refresh();
    }
    terminal_close();
}
