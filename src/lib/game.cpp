#include "game.h"

namespace AsciiGame
{
    Game::Game(void) {
        AsciiGame::ValueGenerator ValueGenerator;
        this->cardValues = ValueGenerator.GetGeneratedValues();

        this->previouslyChosenCard = -999;
    }

    int Game::SelectCard(void)
    {
        keypad(stdscr, true);

        while(true) {
            BuildPlayfield();
            
            bool selection = NavigateAndSelect();
            if(selection) {
                break;
            }
        }
        
        if(selectedCard != previouslyChosenCard && ! cardRevealed[selectedCard]) {
            CheckIfCorrect();
        }

        return selectedCard;
    }

    void Game::BuildPlayfield(void) {
        for(int i = 0; i < 9; i++) {
            // Revealed card, selected
            if(cardRevealed[i] && (i == selectedCard)) {
                PrintCard(i, cardValues[i], true);
            }
            // Revealed card, unselected
            else if(cardRevealed[i] && (i != selectedCard)) {
                PrintCard(i, cardValues[i], false);
            }
            // Anonymous card, selected
            else if(! cardRevealed[i] && i == selectedCard) {
                PrintCard(i, -1, true);
            }
            // Anonymous card, unselected
            else {
                PrintCard(i, -1, false);
            }
        }
        refresh();
    }

    bool Game::NavigateAndSelect(void) {
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

        bool selectThisCard = false;

        // Enter key
        if(userInput == 10) {
            selectThisCard = true;
        }

        return selectThisCard;
    }

    void Game::CheckIfCorrect(void) {
        // New guess
        if(previouslyChosenCard == -999) {
            cardRevealed[selectedCard] = true;
            previouslyChosenCard = selectedCard;
        }
        // Correct guess
        else if(cardValues[selectedCard] == cardValues[previouslyChosenCard]) {
            cardRevealed[selectedCard] = true;
            previouslyChosenCard = -999;
        }
        // Wrong guess
        else {
            cardRevealed[selectedCard] = true;
            BuildPlayfield();
            getch();
            cardRevealed[selectedCard] = false;
            cardRevealed[previouslyChosenCard] = false;
            previouslyChosenCard = -999;
        }
    }

    void Game::PrintCard(int cardNumber, int cardValue, bool selected) {

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
        int iconXPosition = cardSize - 3;

        // Adding decoration to the box
        mvwprintw(card, (ySize - 2), (xSize - 3), "_|");

        // Adding visuals to the box
        // > Anonymous
        if(cardValue == -1) {
            wattron(card, COLOR_PAIR(5));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, ".......");
            wattroff(card, COLOR_PAIR(5));
        }
        // > Empty
        else if(cardValue == 0) {
            wattron(card, COLOR_PAIR(0));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "_  _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "\\\\//");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "//\\\\");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "EMPTY");
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
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "  .");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " / \\");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, " \\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  °");
            wattroff(card, COLOR_PAIR(3));
        }
        // > Heart
        else if(cardValue == 4) {
            wattron(card, COLOR_PAIR(0));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, " _ _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "( v )");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, " \\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  *");
            wattroff(card, COLOR_PAIR(0));
        }

        // > Cursor
        if(selected && cardValue == -1) {
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
        else if(selected && cardValue != -1) {
            wattron(card, COLOR_PAIR(4));
            mvwprintw(card, (ySize - 3), 2, "XXX");
            mvwprintw(card, (ySize - 2), 2, "XXX");
            wattron(card, COLOR_PAIR(4));
        }

        wrefresh(card);
    }
}