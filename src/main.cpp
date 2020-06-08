#include <ncurses.h>

#include "lib/intro.h"
#include "lib/game.h"
#include "lib/scoreboard.h"

using namespace std;

int main(void) {
    cout << "\nWHERE'S MY ASCII?" << endl;
    cout << "-----------------\n" << endl;
    cout << "Note: Please maximize this console window now. It is important that it doesn't get resized when the game is running.\n" << endl;

    string nickname = "";
    cout << "Before we can start. What is your name? ";
    cin >> nickname;

    AsciiGame::Intro intro;
    int level = intro.AskDifficultyLevel();

    int playfieldSize = 0;
    int cardOccurrence = 0;

    switch(level) {
        case 0: // Easy
        default:
            playfieldSize = 3;
            cardOccurrence = 2;
            break;
        case 1: // Medium
            playfieldSize = 3;
            cardOccurrence = 3;
            break;
        case 2: // Hard
            playfieldSize = 4;
            cardOccurrence = 3;
            break;
    }

    AsciiGame::Game game(playfieldSize, cardOccurrence);

    clear();

    // end ncurses (deallocate memory)
    endwin();
    int score = game.GetScore();

    AsciiGame::Scoreboard("./scores.txt", score, nickname);

    cout << "\nEnd of game. Goodbye!\n\nUse the enter-key to continue . . ." << endl;
    cin.ignore();
    
    return 0;
}