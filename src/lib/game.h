#pragma once

#include "valuegenerator.h"
#include <ncurses.h>
#include <string>
#include <vector>

namespace AsciiGame {
    class Game {

        //Constructor
        public:
            Game(int cardsPerAxis, int cardOccurence);

        public:
            int SelectCard(void);

        private:
            void BuildPlayfield(void);
            bool selectCard(void);
            void CheckIfCorrect(void);
            bool chosenCardsIdentical(void);
            void UnrevealChosenCards(void);
            void PrintCard(int cardNumber, int cardValue, bool);
        
        private:
            int cardsPerAxis = 0;
            int cardsOnPlayfield = 0;
            int cardOccurrence = 0;

            std::vector<int> cardValues;
            std::vector<int> chosenCards;
            bool cardRevealed[16] = {0}; // Max size = 16
            int selectedCard = 0;
    };
}