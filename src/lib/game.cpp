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

        do {
            SelectCard();
        } while(rightGuesses < (cardsOnPlayfield / cardOccurence));

        attron(A_BOLD);
        attron(A_UNDERLINE);
        mvwprintw(stdscr, 10, 120, std::string("Game finished. Please press the enter-key to view the scoreboard.").c_str());
        attroff(A_BOLD);
        attron(A_UNDERLINE);

        int userInput = 0;

        do {
            //Wait
            userInput = wgetch(stdscr);
        } while(userInput != 10);
    }

    int Game::GetScore(void) {
        int score = 100 - (wrongGuesses * 10);

        if(score < 0) {
            score = 0;
        }

        return score;
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

        mvwprintw(stdscr, 3, 120, std::string("Right guesses: " + std::to_string(rightGuesses)).c_str());
        mvwprintw(stdscr, 5, 120, std::string("Wrong guesses: " + std::to_string(wrongGuesses)).c_str());

        refresh();
    }

    bool Game::selectCard(void) {
        int userInput = wgetch(stdscr);

        if(userInput == KEY_LEFT && ((selectedCard - 1) % cardsPerAxis) < (cardsPerAxis - 1) && (selectedCard -1) >= 0) {
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
            mvwprintw(stdscr, 10, 120, std::string("That's right! Well done! Let's try another one.").c_str());
            chosenCards.clear();
            rightGuesses++;
        }
        // Wrong guess
        else if(! chosenCardsIdentical()) {
            mvwprintw(stdscr, 10, 120, std::string("That was a wrong guess. Better luck next time.").c_str());
            getch();
            UnrevealChosenCards();
            chosenCards.clear();
            wrongGuesses++;
            mvwprintw(stdscr, 10, 120, std::string("Search wisely for a new card.\t\t\t").c_str());
        }
        else {
            mvwprintw(stdscr, 10, 120, std::string("Now find the matching one.\t\t\t").c_str());
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