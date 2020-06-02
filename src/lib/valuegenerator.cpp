#include "valuegenerator.h"

namespace AsciiGame {
    ValueGenerator::ValueGenerator(int numberOfValues) {
        this->numberOfValues = numberOfValues;
        FillArray();
    }

    void ValueGenerator::FillArray(void) {
        const int CARD_VARIANTS = 4;
        int maxOccurences = numberOfValues / CARD_VARIANTS;

        srand (time(NULL));

        int value = 0;

        for(unsigned int i = 0; i < numberOfValues; i++) {
            do {
                value = rand() % (CARD_VARIANTS + 1);
            } while(CountOccurrences(value) >= maxOccurences);

            generatedValues.push_back(value);
        }
    }

    std::vector<int> ValueGenerator::GetGeneratedValues(void) {

        return generatedValues;
    }

    int ValueGenerator::CountOccurrences(int value) {
        int occurrences = 0;

        for(unsigned int i = 0; i < generatedValues.size(); i++) {
            if(generatedValues[i] == value) {
                occurrences++;
            }
        }

        return occurrences;
    }

    std::vector<int> generatedValues;
}