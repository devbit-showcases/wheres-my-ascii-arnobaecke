#pragma once

#include <array>
#include <stdlib.h>
#include <time.h>

namespace AsciiGame {
    class ValueGenerator { 
        public:
            ValueGenerator(int numberOfValues, int maxOccurrences);

        public:
            std::array<int, 16> GetGeneratedValues(void);

        private:
            void FillArray(void);
            void AddValue(int value);
        
        private:
            int numberOfValues = 0;
            int maxOccurrences = 0;
            std::array<int, 16> generatedValues = { 0 };
            bool indexTaken[16] = { false };
    };
}