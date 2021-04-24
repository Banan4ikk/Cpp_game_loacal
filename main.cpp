#include <iostream>
#include <BearLibTerminal.h>

int main()
{
    terminal_open();

    // Выводим текст
    terminal_printf(12, 17, "Hello, world!");
    terminal_refresh();

    // Ждем, пока пользователь не закроет окно
    while (terminal_read() != TK_CLOSE);

    terminal_close();
}
