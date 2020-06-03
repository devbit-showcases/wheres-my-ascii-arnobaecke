#include "game.h"

namespace AsciiGame
{
    Game::Game(int cardsPerAxis, int cardOccurence) {
        this->cardsPerAxis = cardsPerAxis;
        this->cardOccurrence = cardOccurence;
        this->cardsOnPlayfield = cardsPerAxis * cardsPerAxis;

        AsciiGame::ValueGenerator valuegenerator(cardsOnPlayfield, cardOccurence);
        this->cardValues = valuegenerator.GetGeneratedValues();
    }

    int Game::SelectCard(void)
    {
        keypad(stdscr, true);

        do {
            BuildPlayfield();
        } while (! selectCard());
        
        if(! cardRevealed[selectedCard]) {
            CheckIfCorrect();
        }

        return selectedCard;
    }

    void Game::BuildPlayfield(void) {
        for(int i = 0; i < cardsOnPlayfield; i++) {
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

    bool Game::selectCard(void) {
        int userInput = wgetch(stdscr);

        if(userInput == KEY_LEFT && (selectedCard - 1) % cardsPerAxis < (cardsPerAxis - 1) && (selectedCard -1) >= 0) {
            selectedCard--;
        }
        else if(userInput == KEY_RIGHT && (selectedCard + 1) % cardsPerAxis > 0) {
            selectedCard++;
        }
        else if(userInput == KEY_UP && (selectedCard - cardsPerAxis) >= 0) {
            selectedCard -= cardsPerAxis;
        }
        else if(userInput == KEY_DOWN && (selectedCard + cardsPerAxis) < cardsOnPlayfield) {
            selectedCard += cardsPerAxis;
        }

        bool selectThisCard = false;

        // *-key (easter egg)
        if(userInput == 42 && ! cardRevealed[selectedCard]) {
            cardRevealed[selectedCard] = true;
            BuildPlayfield();
            getch();
            cardRevealed[selectedCard] = false;
        }
        // Enter-key (select)
        else if(userInput == 10) {
            selectThisCard = true;
        }

        return selectThisCard;
    }

    void Game::CheckIfCorrect(void) {
        cardRevealed[selectedCard] = true;
        chosenCards.push_back(selectedCard);
        BuildPlayfield();

        // All identical cards found
        if(chosenCardsIdentical() && (chosenCards.size() == cardOccurrence)) {
            chosenCards.clear();
        }
        // Wrong guess
        else if(! chosenCardsIdentical()) {
            getch();
            UnrevealChosenCards();
            chosenCards.clear();
        }
        else {
            // Do nothing
        }
    }

    bool Game::chosenCardsIdentical(void) {
        bool allIdentical = true;

        int reference = chosenCards[0];
        int compariser = 0;

        for(unsigned int i = 0; i < chosenCards.size(); i++) {
            compariser = chosenCards[i];

            if(cardValues[compariser] != cardValues[reference]) {
                allIdentical = false;
            }
        }

        return allIdentical;
    }

    void Game::UnrevealChosenCards(void) {
        for(unsigned int i = 0; i < chosenCards.size(); i++) {
            int cardNumber = chosenCards[i];
            cardRevealed[cardNumber] = false;
        }
    }

    void Game::PrintCard(int cardNumber, int cardValue, bool selected) {

        // Editable parameters
        const int cardSize = 11;

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