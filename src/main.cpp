#include <iostream>
#include <BearLibTerminal.h>

class Controls{
    bool is_exit = false;
    enum sides{
        left = 1,
        right,
        down,
        up
    };
public:
    bool isExit() const {
        return is_exit;
    }

    int getSide(){
        int side=0;
            auto key = terminal_read();
            switch (key) {
                case TK_UP: side = up;break;
                case TK_DOWN: side = down;break;
                case TK_LEFT: side = left;break;
                case TK_RIGHT: side = right;break;
            }
        return side;
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

    const int MAX_X = 80;
    const int MAX_Y = 25;

    int speed=1;
    const char symbol ='@';
    int x;
    int y;
    void render(){
        terminal_put(x,y,symbol);
    }

    void move(){
        int side = controls.getSide();
        switch (side) {
            case 1: x-=speed;break;//left
            case 2: x+=speed;break;//right
            case 3: y+=speed;break;//up
            case 4: y-=speed;break;//down
        }
        if(x>=MAX_X)
            x=MAX_X-1;
        if(x<=0)
            x=0;
        if(y>=MAX_Y)
            y=MAX_Y-1;
        if(y<=0)
            y = 0;
    }

public:
    Player(Controls &controls, int x, int y) : controls(controls), x(x), y(y) {}
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
        terminal_clear();
        player.update();
        terminal_refresh();
    }

    terminal_close();
}
