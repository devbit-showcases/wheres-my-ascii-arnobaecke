#pragma once

#include <iostream>
#include <time.h>
#include <array>

namespace AsciiGame {
    class ValueGenerator { 
        //Constructor
        public:
            ValueGenerator(void);

        public:
            std::array<int, 9> GetGeneratedValues(void);

        private:
            void FillArray(void);
            int CountOccurrences(int value);
        
        private:
            std::array<int, 9> generatedValues = {0};
    };
}