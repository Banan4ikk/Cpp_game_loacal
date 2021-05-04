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
                case TK_LEFT: x-=speed;
                case TK_RIGHT: x+=speed;
                default: continue;
            }
        }
        return x;
    }

    int updateY(int y, int speed){
        while (terminal_has_input()){
            auto key = terminal_read();
            switch (key) {
                case TK_LEFT: y-=speed;
                case TK_RIGHT: y+=speed;
                default: continue;
            }
        }
        return y;
    }
    void exit(){
        auto key = NULL;
        if(terminal_has_input())
            key = terminal_read();
        if(key == TK_CLOSE)
            is_exit = true;
    }
};

class Player{
    Controls controls;
    int speed_x=1;
    int speed_y=1;
    const char symbol ='@';
    int x;
    int y;

    void move(){
        controls.updateX(x,speed_x);
        controls.updateY(y,speed_y);
    }
    void render(){
        terminal_put(x,y,symbol);
    }
public:
    Player(int x, int y) : x(x), y(y) {}

    void update(){
        move();
        render();
    }
};

int main()
{
    terminal_open();

    // Выводим текст
    terminal_printf(12, 17, "Hello, world!");
    terminal_refresh();

    Controls controls{};
    Player player{5,5};
    // Ждем, пока пользователь не закроет окно
    while (!controls.isExit()){
        player.update();
    };

    terminal_close();
}
