#pragma once

#include <ncurses.h>
#include <string>

namespace AsciiGame {
    class Intro {
        public:
            Intro(void);

        private:
            void prepareNcurses(void);
            void PrintLogo(void);
            void PrintInstructions(void);

        public:
            int AskDifficultyLevel(void);

    };
}