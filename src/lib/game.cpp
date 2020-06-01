#include "game.h"

namespace AsciiGame
{
    Game::Game(void) {
        //AsciiGame::ValueGenerator ValueGenerator;
        //this->cardValues = ValueGenerator.GetGeneratedValues();

        for(int i = 0; i < 9; i++) {
            printw(std::to_string(cardValues[i]).c_str());
        }
        refresh();
    }

    int Game::SelectCard(void)
    {
        keypad(stdscr, true);

        int selectedCard = 0;

        while(true) {
            // Print card layout
            for(int i = 0; i < 9; i++) {
                if(i == selectedCard) {
                    // Selection hand
                    PrintCard(i, -2);
                }
                else {
                    if(cardRevealed[i]) {
                        // Card value
                        PrintCard(i, cardValues[i]);
                    }
                    else {
                        // Card back
                        PrintCard(i, -1);
                    }
                }
            }
            refresh();

            // Navigation
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

        cardRevealed[selectedCard] = true;
        
        return selectedCard;
    }

    void Game::PrintCard(int cardNumber, int cardValue) {

        // Editable parameters
        const int cardSize = 11;
        const int cardsPerAxis = 3;

        // Calculated parameters (do not edit)
        const int ySize = cardSize;
        const int xSize = cardSize * 2;
        const int yShift = ySize + 5;
        const int xShift = xSize + 5;
        
        int cardYPosition = yShift * (cardNumber / cardsPerAxis);
        int cardXPosition = xShift * cardNumber % (cardsPerAxis * xShift);

        // Empty box creation
        WINDOW * card = newwin(ySize, xSize, cardYPosition, cardXPosition);
        refresh();
        box(card, 0, 0);

        int iconYPosition = (cardSize / 2) - 2;
        int iconXPosition = (cardSize ) - 3;

        // Adding decoration to the box
        mvwprintw(card, (ySize - 2), (xSize - 3), "_|");

        // Adding visuals to the box
        // > Selection hand
        if(cardValue == -2) {
            wattron(card, COLOR_PAIR(4));
            mvwprintw(card, (iconYPosition + 0), (iconXPosition - 3), "   .._,-/`)");
            mvwprintw(card, (iconYPosition + 1), (iconXPosition - 3), "   .// / / )");
            mvwprintw(card, (iconYPosition + 2), (iconXPosition - 3), "   // / / / )");
            mvwprintw(card, (iconYPosition + 3), (iconXPosition - 3), " /`/ / / / /");
            mvwprintw(card, (iconYPosition + 4), (iconXPosition - 3), "/ /     ` /");
            mvwprintw(card, (iconYPosition + 5), (iconXPosition - 3), "\\        /");
            mvwprintw(card, (iconYPosition + 6), (iconXPosition - 3), " )     .'");
            mvwprintw(card, (iconYPosition + 7), (iconXPosition - 3), "/     /");
            wattroff(card, COLOR_PAIR(4));
        }
        // > Back
        if(cardValue == -1) {
            wattron(card, COLOR_PAIR(5));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, ".......");
            wattroff(card, COLOR_PAIR(5));
        }
        // > Heart
        else if(cardValue == 0) {
            wattron(card, COLOR_PAIR(0));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, " _ _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "( v )");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, " \\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  *");
            wattroff(card, COLOR_PAIR(0));
        }
        // > Clubs
        else if(cardValue == 1) {
            wattron(card, COLOR_PAIR(1));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "   _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " _(_)_");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "(_) (_)");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "   |");
            wattroff(card, COLOR_PAIR(1));
        }
        // > Spades
        else if(cardValue == 2) {
            wattron(card, COLOR_PAIR(2));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "  .");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " / \\");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "(   )");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  | ");
            wattroff(card, COLOR_PAIR(2));
        }
        // > Diamonds
        else if(cardValue == 3) {
            wattron(card, COLOR_PAIR(3));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, " .");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "/ \\");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "\\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, " °");
            wattroff(card, COLOR_PAIR(3));
        }
        // > Empty
        else if(cardValue == 4) {
            wattron(card, COLOR_PAIR(0));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "_  _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "\\\\//");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "//\\\\");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "EMPTY");
            wattroff(card, COLOR_PAIR(0));
        }

        wrefresh(card);
    }

    std::array<int, 9> cardValues = {0};
    bool cardRevealed[9] = { };
}