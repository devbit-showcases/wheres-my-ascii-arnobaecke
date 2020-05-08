#include "game.h"
#include <ncurses.h>

namespace AsciiGame {
    void Game::printCard(int cardNumber, std::string content, bool selected) {

        // Editable parameters
        const int cardSize = 11;
        const int cardsPerAxis = 3;

        // Calculated parameters (do not edit)
        const int ySize = cardSize;
        const int xSize = cardSize * 2;
        const int yShift = ySize + 5;
        const int xShift = xSize + 5;
        
        int start_y = yShift * (cardNumber / cardsPerAxis);
        int start_x = xShift * cardNumber % (cardsPerAxis * xShift);

        // Box creation
        WINDOW * win = newwin(ySize, xSize, start_y, start_x);
        refresh();
        box(win, 0, 0);

        // Converting content string to const char pointer
        const char *boxContent = content.c_str();

        // Adding content and decoration to box (window, y pos, x pos, content)
        mvwprintw(win, (ySize / 2), (xSize / 2), boxContent);
        mvwprintw(win, (ySize - 2), (xSize - 3), "_|");

        // Adding a selected hand to the box
        if(selected) {
            mvwprintw(win, (ySize - 9), 2, "     _.-/`)");
            mvwprintw(win, (ySize - 8), 2, "    // / / )");
            mvwprintw(win, (ySize - 7), 2, "   // / / / )");
            mvwprintw(win, (ySize - 6), 2, " /`/ / / / /");
            mvwprintw(win, (ySize - 5), 2, "/ /     ` /");
            mvwprintw(win, (ySize - 4), 2, "\\        /");
            mvwprintw(win, (ySize - 3), 2, " )     .'");
            mvwprintw(win, (ySize - 2), 2, "/     /");
        }

        wrefresh(win);
    }
}