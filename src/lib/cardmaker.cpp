#include "cardmaker.h"

namespace AsciiGame
{
    CardMaker::CardMaker(int cardsPerAxis) {
        this->cardsPerAxis = cardsPerAxis;
    }

    void CardMaker::PrintCard(int cardNumber, int cardValue, bool selected) {

        // Editable parameters
        const int cardSize = 11;

        // Calculated parameters (do not edit)
        const int ySize = cardSize;
        const int xSize = cardSize * 2;
        const int yShift = ySize + 2;
        const int xShift = xSize + 5;
        
        int cardYPosition = yShift * (cardNumber / cardsPerAxis);
        int cardXPosition = xShift * cardNumber % (cardsPerAxis * xShift);

        int iconYPosition = (cardSize / 2) - 2;
        int iconXPosition = cardSize - 3;

        // Empty box creation
        WINDOW * card = newwin(ySize, xSize, cardYPosition, cardXPosition);
        refresh();
        box(card, 0, 0);

        // Adding decoration to the box
        mvwprintw(card, (ySize - 2), (xSize - 3), "_|");

        // Adding visuals to the box
        // > Anonymous
        if(cardValue == -1) {
            wattron(card, COLOR_PAIR(5));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, ".......");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, ".......");
            wattroff(card, COLOR_PAIR(5));
        }
        // > Cross
        else if(cardValue == 0) {
            wattron(card, COLOR_PAIR(0));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "_  _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "\\\\//");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "//\\\\");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "~~~~");
            wattroff(card, COLOR_PAIR(0));
        }
        // > Clubs
        else if(cardValue == 1) {
            wattron(card, COLOR_PAIR(1));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "   _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " _(_)_");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "(_) (_)");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "   |");
            wattroff(card, COLOR_PAIR(1));
        }
        // > Spades
        else if(cardValue == 2) {
            wattron(card, COLOR_PAIR(2));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "  .");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " / \\");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "(   )");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  |");
            wattroff(card, COLOR_PAIR(2));
        }
        // > Diamonds
        else if(cardValue == 3) {
            wattron(card, COLOR_PAIR(3));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, "  .");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, " / \\");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, " \\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  *");
            wattroff(card, COLOR_PAIR(3));
        }
        // > Heart
        else if(cardValue == 4) {
            wattron(card, COLOR_PAIR(4));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, " _ _");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "( v )");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, " \\ /");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  *");
            wattroff(card, COLOR_PAIR(4));
        }
        // > Cat
        else if(cardValue == 5) {
            wattron(card, COLOR_PAIR(5));
            mvwprintw(card, (iconYPosition + 0), iconXPosition, " /\\_/\\");
            mvwprintw(card, (iconYPosition + 1), iconXPosition, "( o o )");
            mvwprintw(card, (iconYPosition + 2), iconXPosition, "==_Y_==");
            mvwprintw(card, (iconYPosition + 3), iconXPosition, "  `-'");
            wattroff(card, COLOR_PAIR(5));
        }

        // > Cursor (big or small)
        if(selected && cardValue == -1) {
            wattron(card, COLOR_PAIR(4));
            mvwprintw(card, (iconYPosition + 0), (iconXPosition - 3), "   .._,-/`)");
            mvwprintw(card, (iconYPosition + 1), (iconXPosition - 3), "   .// / / )");
            mvwprintw(card, (iconYPosition + 2), (iconXPosition - 3), "   // / / / )");
            mvwprintw(card, (iconYPosition + 3), (iconXPosition - 3), " /`/ / / / /");
            mvwprintw(card, (iconYPosition + 4), (iconXPosition - 3), "/ /     ` /");
            mvwprintw(card, (iconYPosition + 5), (iconXPosition - 3), "\\        /");
            mvwprintw(card, (iconYPosition + 6), (iconXPosition - 3), " )     .'");
            mvwprintw(card, (iconYPosition + 7), (iconXPosition - 3), "/     /");
            wattroff(card, COLOR_PAIR(4));
        }
        else if(selected && cardValue != -1) {
            wattron(card, COLOR_PAIR(4));
            mvwprintw(card, (ySize - 3), 2, "XXX");
            mvwprintw(card, (ySize - 2), 2, "XXX");
            wattron(card, COLOR_PAIR(4));
        }

        wrefresh(card);
    }
}