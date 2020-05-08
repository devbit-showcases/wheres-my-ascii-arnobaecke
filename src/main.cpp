#include <iostream>
#include <ncurses.h>

#include "lib/dialog.h"
#include "lib/game.h"

using namespace std;

int main(void) {

    // initialize ncurses (allocate memory and clear console)
    initscr();

    AsciiGame::Game game;

    int selectedcard = 5;

    for(int i = 0; i < 9; i++) {
        if(i == selectedcard) {
            game.printCard(i, "?", true);
        }
        else {
            game.printCard(i, "?", false);
        }        
    }

    refresh();


    //KEEP OPEN
    int c = getch();

    // end ncurses (deallocate memory)
    endwin();
    
    return 0;
}