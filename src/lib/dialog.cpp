#include "dialog.h"
#include <ncurses.h>

namespace AsciiGame {
    void Dialog::Hello(void) {
        printw("Hello world\n");

        refresh();

        int c = getch();

        printw("%d", c);

        getch();
    }
}