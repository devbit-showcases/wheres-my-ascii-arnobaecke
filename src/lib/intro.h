#pragma once

#include <ncurses.h>
#include <string>

namespace AsciiGame {
    class Intro {
        //Constructor   
        public:
            Intro(void);

        private:
            void PrintLogo(void);
            void PrintInstructions(void);

        public:
            int AskDifficultyLevel(void);

    };
}