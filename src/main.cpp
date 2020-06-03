#include <ncurses.h>

#include "lib/intro.h"
#include "lib/game.h"

using namespace std;

int main(void) {
    AsciiGame::Intro intro;

    int level = intro.AskDifficultyLevel();

    int playfieldSize = 0;
    int cardOccurence = 0;

    switch(level) {
        case 0: // Easy
        default:
            playfieldSize = 3;
            cardOccurence = 2;
            break;
        case 1: // Medium
            playfieldSize = 3;
            cardOccurence = 3;
            break;
        case 2: // Hard
            playfieldSize = 4;
            cardOccurence = 3;
            break;
    }

    AsciiGame::Game game(playfieldSize, cardOccurence);

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