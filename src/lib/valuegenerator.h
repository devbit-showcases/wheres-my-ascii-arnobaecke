#pragma once

#include <iostream>
#include <time.h>

namespace AsciiGame {
    class ValueGenerator { 
        //Constructor
        public:
            ValueGenerator(void);

        public:
            int* GetCardValues(void);

        private:
            void FillArray(void);
            int CountOccurrences(int value);
        
        private:
            int cardValues[9];
    };
}