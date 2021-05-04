#include <iostream>
#include <BearLibTerminal.h>

class Controls{
    bool is_exit;

};

class Player{

};

int main()
{
    terminal_open();

    // Выводим текст
    terminal_printf(12, 17, "Hello, world!");
    terminal_refresh();

    // Ждем, пока пользователь не закроет окно
    while (true){
        if(isExit())
            break;
    };

    terminal_close();
}
