#include "game.h"

namespace AsciiGame
{
    Game::Game(int cardsPerAxis, int cardOccurence)
        : cardMaker(cardsPerAxis) {
        this->cardsPerAxis = cardsPerAxis;
        this->cardOccurrence = cardOccurence;
        this->cardsOnPlayfield = cardsPerAxis * cardsPerAxis;

        AsciiGame::ValueGenerator valuegenerator(cardsOnPlayfield, cardOccurence);
        this->cardValues = valuegenerator.GetGeneratedValues();

        while(true) {
            SelectCard();
        }
    }

    void Game::SelectCard(void)
    {
        keypad(stdscr, true);

        do {
            BuildPlayfield();
        } while (! selectCard());
        
        if(! cardRevealed[selectedCard]) {
            CheckIfCorrect();
        }
    }

    void Game::BuildPlayfield(void) {
        for(int i = 0; i < cardsOnPlayfield; i++) {
            // Revealed card, selected
            if(cardRevealed[i] && (i == selectedCard)) {
                cardMaker.PrintCard(i, cardValues[i], true);
            }
            // Revealed card, unselected
            else if(cardRevealed[i] && (i != selectedCard)) {
                cardMaker.PrintCard(i, cardValues[i], false);
            }
            // Anonymous card, selected
            else if(! cardRevealed[i] && i == selectedCard) {
                cardMaker.PrintCard(i, -1, true);
            }
            // Anonymous card, unselected
            else {
                cardMaker.PrintCard(i, -1, false);
            }
        }

        std::string status = "Wrong guesses: " + std::to_string(wrongGuesses);
        mvwprintw(stdscr, 5, 120, status.c_str());

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
            wrongGuesses++;
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
}