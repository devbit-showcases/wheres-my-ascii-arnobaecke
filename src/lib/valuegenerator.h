#pragma once

#include <vector>

namespace AsciiGame {
    class ValueGenerator { 
        public:
            ValueGenerator(int numberOfValues, int maxOccurrences);

        public:
            std::vector<int> GetGeneratedValues(void);

        private:
            void FillArray(void);
            int CountOccurrences(int value);
        
        private:
            int numberOfValues = 0;
            int maxOccurrences = 0;
            std::vector<int> generatedValues;
    };
}