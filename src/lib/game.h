#pragma once

#include "valuegenerator.h"
#include "cardmaker.h"
#include <ncurses.h>
#include <string>
#include <vector>

namespace AsciiGame {
    class Game {
        public:
            Game(int cardsPerAxis, int cardOccurence);

        public:
            int GetScore(void);

        private:
            void SelectCard(void);
            void BuildPlayfield(void);
            bool selectCard(void);
            void CheckIfCorrect(void);
            bool chosenCardsIdentical(void);
            void UnrevealChosenCards(void);
        
        private:
            AsciiGame::CardMaker cardMaker;

            int cardsPerAxis = 0;
            int cardsOnPlayfield = 0;
            int cardOccurrence = 0;

            std::array<int, 16> cardValues;
            std::vector<int> chosenCards;

            bool cardRevealed[16] = {0};
            int selectedCard = 0;

            int wrongGuesses = 0;
            int rightGuesses = 0;
    };
}