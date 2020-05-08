#pragma once

#include <ncurses.h>
#include <string>

namespace AsciiGame {
    class Game {     
        public:
            void printCard(int number, std::string content, bool selected);
    };
}