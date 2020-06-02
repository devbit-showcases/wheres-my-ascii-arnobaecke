#pragma once

#include "valuegenerator.h"
#include <ncurses.h>
#include <string>
#include <vector>

namespace AsciiGame {
    class Game {

        //Constructor
        public:
            Game(int cardsPerAxis);

        public:
            int SelectCard(void);

        private:
            void BuildPlayfield(void);
            bool NavigateAndSelect(void);
            void CheckIfCorrect(void);
            void PrintCard(int cardNumber, int cardValue, bool);
        
        private:
            int cardsPerAxis = 0;
            int cardsOnPlayfield = 0;

            std::vector<int> cardValues;
            bool cardRevealed[16] = {0}; // Max size = 16
            int selectedCard = 0;
            int previouslyChosenCard = -999;
    };
}