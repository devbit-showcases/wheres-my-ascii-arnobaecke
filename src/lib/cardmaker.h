#pragma once

#include <ncurses.h>

namespace AsciiGame {
    class CardMaker { 
        public:
            CardMaker(int cardsPerAxis);
        
        public:
            void PrintCard(int cardNumber, int cardValue, bool);

        private:
            int cardsPerAxis = 0;
    };
}