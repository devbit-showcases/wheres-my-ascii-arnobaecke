#include "valuegenerator.h"

namespace AsciiGame {
    ValueGenerator::ValueGenerator(void) {
        FillArray();
    }

    void ValueGenerator::FillArray(void) {
        srand (time(NULL));

        int value = 0;

        for(unsigned int i = 0; i < sizeof(generatedValues); i++) {
            do {
                value = rand() % 4;
            } while(CountOccurrences(value) >= 2);

            generatedValues[i] = value;
        }
    }

    std::array<int, 9> ValueGenerator::GetGeneratedValues(void) {

        return generatedValues;
    }

    int ValueGenerator::CountOccurrences(int value) {
        int occurrences = 0;

        for(unsigned int i = 0; i < sizeof(generatedValues); i++) {
            if(generatedValues[i] == value) {
                occurrences++;
            }
        }

        return occurrences;
    }

    std::array<int, 9> generatedValues[9] = { };
}