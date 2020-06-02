#pragma once

#include "valuegenerator.h"
#include <ncurses.h>
#include <string>
#include <vector>

namespace AsciiGame {
    class Game {

        //Constructor
        public:
            Game(void);

        public:
            int SelectCard(void);

        private:
            void BuildPlayfield(void);
            bool NavigateAndSelect(void);
            void CheckIfCorrect(void);
            void PrintCard(int cardNumber, int cardValue, bool);
        
        private:
            std::array<int, 9> cardValues = {0};
            bool cardRevealed[9] = {0};
            int selectedCard = 0;
            int previouslyChosenCard = -999;
    };
}