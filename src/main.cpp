#include <iostream>
#include <ncurses.h>

#include "lib/intro.h"
#include "lib/game.h"

using namespace std;

int main(void) {
    AsciiGame::Intro intro;

    AsciiGame::Game game(3);

    int selectedCard;

    while(true) {
        selectedCard = game.SelectCard();
    }

    //KEEP OPEN
    getch();

    // end ncurses (deallocate memory)
    endwin();
    
    return 0;
}