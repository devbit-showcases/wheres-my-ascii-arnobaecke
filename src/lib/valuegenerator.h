#pragma once

#include <iostream>
#include <time.h>

namespace AsciiGame {
    class ValueGenerator { 
        public:
            void AssignValues(void);

        private:
            int CountOccurrences(int value);
        
        private:
            int cardValues[9];
    };
}