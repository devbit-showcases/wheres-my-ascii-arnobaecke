#include "valuegenerator.h"

namespace AsciiGame {
    void ValueGenerator::AssignValues(void) {
        srand (time(NULL));

        int value = 0;

        for(unsigned int i = 0; i < sizeof(cardValues); i++) {
            do {
                value = rand() % 4;
            } while(CountOccurrences(value) >= 2);

            cardValues[i] = value;
        }
    }

    int ValueGenerator::CountOccurrences(int value) {
        int occurrences = 0;

        for(unsigned int i = 0; i < sizeof(cardValues); i++) {
            if(cardValues[i] == value) {
                occurrences++;
            }
        }

        return occurrences;
    }

    int cardValues[9] = { };
}