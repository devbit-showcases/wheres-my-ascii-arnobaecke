#include "valuegenerator.h"

#include <ncurses.h>
#include <string>

namespace AsciiGame {
    ValueGenerator::ValueGenerator(int numberOfValues, int maxOccurrences) {
        this->numberOfValues = numberOfValues;
        this->maxOccurrences = maxOccurrences;
        
        FillArray();
    }

    std::array<int, 16> ValueGenerator::GetGeneratedValues(void) {

        return generatedValues;
    }

    void ValueGenerator::FillArray(void) {
        int cardVariants = (numberOfValues - 1 ) / maxOccurrences; // Max 5

        clear();
        endwin();

        // Loop through card variants
        for(int i = 0; i < cardVariants + 1; i++) {
            AddValue(i);
        }
        
    }

    void ValueGenerator::AddValue(int value) {
        // Add value to array 2x or 3x on a random, empty index

        int index = 0;

        for(int i = 0; i < maxOccurrences; i++) {

            srand (time(NULL));

            do {
                index = rand() % (numberOfValues + 1);
            } while(indexTaken[index] != false);
            
            generatedValues[index] = value;
            indexTaken[index] = true;
        }
    }
}
