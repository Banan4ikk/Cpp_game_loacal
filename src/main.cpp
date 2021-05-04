#include <iostream>
#include <BearLibTerminal.h>

class Controls{
    bool is_exit = false;
public:
    bool isExit() const {
        return is_exit;
    }

    int updateX(int x,int speed){
        while (terminal_has_input()){
            auto key = terminal_read();
            switch (key) {
                case TK_D: x-=speed;
                case TK_A: x+=speed;
                default: continue;
            }
        }
        return x;
    }

    int updateY(int y, int speed){
        while (terminal_has_input()){
            auto key = terminal_read();
            switch (key) {
                case TK_W: y-=speed;
                case TK_S: y+=speed;
                default: continue;
            }
        }
        return y;
    }
    void chekExit(){
        auto key = NULL;
        if(terminal_has_input())
            key = terminal_read();
        if(key == TK_CLOSE)
            is_exit = true;
    }
};

class Player{
    Controls& controls;
    int speed_x=1;
    int speed_y=1;
    const char symbol ='@';
    int x;
    int y;
public:
    Player(Controls &controls, int x, int y) : controls(controls), x(x), y(y) {}

private:
    void move(){
        controls.updateX(x,speed_x);
        controls.updateY(y,speed_y);
    }
    void render(){
        terminal_put(x,y,symbol);
    }

public:
    void update(){
        controls.chekExit();
        move();
        render();
    }
};

int main()
{
    terminal_open();
    terminal_refresh();

    Controls controls{};
    Player player{controls,5,5};

    while (!controls.isExit()){
        player.update();
        terminal_refresh();
    }

    terminal_close();
}
