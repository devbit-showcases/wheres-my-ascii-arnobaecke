#pragma once

#include "valuegenerator.h"
#include <ncurses.h>
#include <string>

namespace AsciiGame {
    class Game {
        public:
            Game(void);

        public:
            int SelectCard(void);
            void RevealCard(int cardNumber);
        
        private:
            void PrintCard(int cardNumber, int cardValue);
        
        private:
            std::array<int, 9> cardValues;
            std::array<bool, 9> cardRevealed;
    };
}