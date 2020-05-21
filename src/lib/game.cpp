#include "game.h"

namespace AsciiGame
{
    int Game::SelectCard(void)
    {
        keypad(stdscr, true);

        int selectedCard = 0;

        while(true) {
            // Initial layout
            for(int i = 0; i < 9; i++) {
                if(i == selectedCard) {
                    PrintCard(i, "SEL");
                }
                else {
                    PrintCard(i, "BACK");
                }        
            }
            refresh();

            int userInput = wgetch(stdscr);

            if(userInput == KEY_LEFT && (selectedCard - 1) % 3 < 2 && (selectedCard -1) >= 0) {
                selectedCard--;
            }
            else if(userInput == KEY_RIGHT && (selectedCard + 1) % 3 > 0) {
                selectedCard++;
            }
            else if(userInput == KEY_UP && (selectedCard - 3) >= 0) {
                selectedCard -= 3;
            }
            else if(userInput == KEY_DOWN && (selectedCard + 3) <= 8) {
                selectedCard += 3;
            }

            // Enter key
            if(userInput == 10) {
                break;
            }
        }
        
        return selectedCard;
    }

    void Game::RevealCard(int cardNumber) {
        PrintCard(cardNumber, "EMPTY");
    }

    void Game::PrintCard(int cardNumber, std::string content) {

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
        WINDOW * card = newwin(ySize, xSize, start_y, start_x);
        refresh();
        box(card, 0, 0);

        // Converting content string to const char pointer
        const char *boxContent = content.c_str();

        // Adding content and decoration to box (window, y pos, x pos, content)
        mvwprintw(card, (ySize - 2), (xSize - 3), "_|");

        // Content starting points
        int iconYPosition = (cardSize / 2) - 2;
        int iconXPosition = (cardSize ) - 3;

        // Adding visuals to the box
        if(content == "SEL") {
            wattron(card, COLOR_PAIR(1));
            mvwprintw(card, (iconYPosition + 0), (iconXPosition - 3), "   .._,-/`)");
            mvwprintw(card, (iconYPosition + 1), (iconXPosition - 3), "   .// / / )");
            mvwprintw(card, (iconYPosition + 2), (iconXPosition - 3), "   // / / / )");
            mvwprintw(card, (iconYPosition + 3), (iconXPosition - 3), " /`/ / / / /");
            mvwprintw(card, (iconYPosition + 4), (iconXPosition - 3), "/ /     ` /");
            mvwprintw(card, (iconYPosition + 5), (iconXPosition - 3), "\\        /");
            mvwprintw(card, (iconYPosition + 6), (iconXPosition - 3), " )     .'");
            mvwprintw(card, (iconYPosition + 7), (iconXPosition - 3), "/     /");
            wattroff(card, COLOR_PAIR(1));
        }
        if(content == "BACK") {
            wattroff(card, COLOR_PAIR(5));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, ".......");
            wattroff(card, COLOR_PAIR(5));
        }
        else if(content == "0") {
            wattron(card, COLOR_PAIR(0));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, " _ _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "( v )");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, " \\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  *");
            wattroff(card, COLOR_PAIR(0));
        }
        else if(content == "1") {
            wattron(card, COLOR_PAIR(1));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "   _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " _(_)_");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "(_) (_)");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "   |");
            wattron(card, COLOR_PAIR(1));
        }
        else if(content == "2") {
            wattron(card, COLOR_PAIR(2));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "  .");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " / \\");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "(   )");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  | ");
            wattroff(card, COLOR_PAIR(2));
        }
        else if(content == "3") {
            wattron(card, COLOR_PAIR(3));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, " .");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "/ \\");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "\\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, " °");
            wattroff(card, COLOR_PAIR(3));
        }
        else if(content == "EMPTY") {
            wattron(card, COLOR_PAIR(0));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "_  _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "\\\\//");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "//\\\\");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "EMPTY");
            wattroff(card, COLOR_PAIR(0));
        }

        wrefresh(card);
    }
}