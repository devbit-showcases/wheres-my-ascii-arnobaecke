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
            void RevealCard(int cardNumber);
        
        private:
            void PrintCard(int cardNumber, int cardValue);
        
        private:
            std::array<int, 9> cardValues = {0};
            bool cardRevealed[9] = {0};
    };
}