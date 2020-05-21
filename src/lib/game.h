#pragma once

#include "valuegenerator.h"
#include <ncurses.h>
#include <string>

namespace AsciiGame {
    class Game {     
        public:
            int SelectCard(void);
            void RevealCard(int cardNumber);
        
        private:
            void PrintCard(int cardNumber, std::string content);
    };
}