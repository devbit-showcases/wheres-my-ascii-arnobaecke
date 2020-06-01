#include <iostream>
#include <ncurses.h>

#include "lib/intro.h"
#include "lib/game.h"

using namespace std;

int main(void) {

    // initialize ncurses (allocate memory and clear console)
    initscr();
    
    AsciiGame::Intro intro;
    intro.checkPrerequisites();

    AsciiGame::Game game;

     int selectedCard;
    
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();
    selectedCard = game.SelectCard();


    //KEEP OPEN
    getch();

    // end ncurses (deallocate memory)
    endwin();
    
    return 0;
}