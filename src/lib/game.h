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
            int cardValues[9];
            bool cardRevealed[9];
    };
}