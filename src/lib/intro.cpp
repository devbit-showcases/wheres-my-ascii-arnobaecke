#include "intro.h"
#include <ncurses.h>

namespace AsciiGame {
    void Intro::checkPrerequisites(void) {
        printw("Checking some prerequisites...\n\n");

        if(has_colors()) {
            start_color();
            use_default_colors();

            // Inititalize the color pairs
            init_pair(0, COLOR_RED, -1);
            init_pair(1, COLOR_GREEN, -1);
            init_pair(2, COLOR_BLUE, -1);
            init_pair(3, COLOR_YELLOW, -1);
            init_pair(4, COLOR_CYAN, -1);
            init_pair(5, COLOR_MAGENTA, -1);
        }
        else {
            printw("Sorry. Your terminal does not support colours.");
        }

        printw("\nReady to go!");

        refresh();
        getch();
    }
}