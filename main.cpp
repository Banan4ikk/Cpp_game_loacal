#include <iostream>
#include <BearLibTerminal.h>
#include <vector>
#include <cmath>
using namespace std;

int to_pos(float x){

    return static_cast<int>(round(x));
}

class Obstacle{
public:
    float x;
};



int main()
{
    terminal_open();
    terminal_refresh();

    const int ground_y = 15;
    const int width = 80;

    float speed_x = 0.15;

    const float gravity = 0.15;
    float player_y = ground_y;
    const int player_x = 2;
    const float max_jump = ground_y-5;
    float speed_y = 0;
    float max_speed_y = gravity*3;

    vector<Obstacle> obstacles{
            {20},
            {40},
            {70}
    };

    bool game_over = false;
    // Ждем, пока пользователь не закроет окно
    while (true){
        terminal_clear();

        if(terminal_has_input()){
            auto event = terminal_read();
            if(event == TK_CLOSE)
                break;
            if(!game_over)
            if(event == TK_SPACE && player_y >= ground_y){
                speed_y = max_speed_y;
            }
        }
        if(game_over){
            terminal_print(1,1,"GAME OVER");
            terminal_refresh();
            continue;
        }
        player_y -=speed_y;
        player_y +=gravity;

        terminal_put(player_x, to_pos(player_y),'@');

        if(player_y >= ground_y)
            player_y = ground_y;

        if(player_y <= max_jump)
            speed_y = 0;

        for (auto& o: obstacles) {
            o.x-=speed_x;
            if(o.x<=0)
                o.x = width;

            if(player_x == to_pos(o.x) && to_pos(player_y) == to_pos(ground_y)){
                terminal_print(1,1,"BUM");
                game_over = true;
            }
            terminal_put(to_pos(o.x),ground_y,'#');
        }

        for (int i = 0; i < width; ++i) {
            terminal_put(i,ground_y+1,'^');
        }


        terminal_refresh();
    }
    terminal_close();
}
