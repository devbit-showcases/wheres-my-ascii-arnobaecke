#pragma once

#include <iostream>
#include <time.h>
#include <vector>

namespace AsciiGame {
    class ValueGenerator { 
        //Constructor
        public:
            ValueGenerator(int numberOfValues);

        public:
            std::vector<int> GetGeneratedValues(void);

        private:
            void FillArray(void);
            int CountOccurrences(int value);
        
        private:
            int numberOfValues = 0;
            std::vector<int> generatedValues;
    };
}