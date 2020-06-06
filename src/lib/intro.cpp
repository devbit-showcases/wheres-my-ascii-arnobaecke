#include "intro.h"

namespace AsciiGame {
    Intro::Intro(void) {
        // Initialize ncurses (allocate memory and clear console)
        initscr();

        // Initialize the color pairs
        if(has_colors()) {
            start_color();
            use_default_colors();

            // Inititalize the color pairs
            init_pair(0, COLOR_RED, -1);
            init_pair(1, COLOR_GREEN, -1);
            init_pair(2, COLOR_YELLOW, -1);
            init_pair(3, COLOR_BLUE, -1);
            init_pair(4, COLOR_CYAN, -1);
            init_pair(5, COLOR_MAGENTA, -1);
        }
        else {
            printw("Sorry. Your terminal does not support colors. Press any key to continue.");
            refresh();
            getch();
        }

        // Show the logo
        PrintLogo();

        // Show the instructions
        PrintInstructions();
    }

    void Intro::PrintLogo(void) {
        std::string logo =
            std::string("           _                   _                       \n") +
            std::string("          | |                 ( )                      \n") +
            std::string(" __      _| |__   ___ _ __ ___|/ ___   _ __ ___  _   _ \n") +
            std::string(" \\ \\ /\\ / / '_ \\ / _ \\ '__/ _ \\ / __| | '_ ` _ \\| | | |\n") +
            std::string("  \\ V  V /| | | |  __/ | |  __/ \\__ \\ | | | | | | |_| |\n") +
            std::string("   \\_/\\_/ |_| |_|\\___|_|  \\___| |___/ |_| |_| |_|\\__, |\n") +
            std::string("                                                  __/ |\n") +
            std::string("                                                 |___/ \n") +
            std::string(" .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n") +
            std::string("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n") +
            std::string("| |      __      | || |    _______   | || |     ______   | || |     _____    | || |     _____    | |\n") +
            std::string("| |     /  \\     | || |   /  ___  |  | || |   .' ___  |  | || |    |_   _|   | || |    |_   _|   | |\n") +
            std::string("| |    / /\\ \\    | || |  |  (__ \\_|  | || |  / .'   \\_|  | || |      | |     | || |      | |     | |\n") +
            std::string("| |   / ____ \\   | || |   '.___`-.   | || |  | |         | || |      | |     | || |      | |     | |\n") +
            std::string("| | _/ /    \\ \\_ | || |  |`\\____) |  | || |  \\ `.___.'\\  | || |     _| |_    | || |     _| |_    | |\n") +
            std::string("| ||____|  |____|| || |  |_______.'  | || |   `._____.'  | || |    |_____|   | || |    |_____|   | |\n") +
            std::string("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n") +
            std::string(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n") +
            std::string("\t\t\t\t\t\t____ ____ ____ ___     ____ ___  _ ___ _ ____ _  _\n") +
            std::string("\t\t\t\t\t\t|    |__| |__/ |  \\    |___ |  \\ |  |  | |  | |\\ | \n") +
            std::string("\t\t\t\t\t\t|___ |  | |  \\ |__/    |___ |__/ |  |  | |__| | \\|\n") +
            std::string("\n\n\n\t\t\t\tPRESS ANY KEY TO CONTINUE...\n");

            attron(COLOR_PAIR(2));
            printw(logo.c_str());
            attroff(COLOR_PAIR(2));

            getch();
            clear();
    }

    void Intro::PrintInstructions(void) {
        std::string instructions = std::string("\n\n") +
            std::string(" +----------------------------------------------+\t\t+----------------------------------------------+\n") +
            std::string(" |            Some quick instructions           |\t\t|                About this game               |\n") +
            std::string(" +----------------------------------------------+\t\t+----------------------------------------------+\n") +
            std::string(" | In the next step, you will see a playing     |\t\t| Everyone knows the classic memory game from  |\n") +
            std::string(" | field with a number of cards. When you flip  |\t\t| their childhood. Well, now you can play it   |\n") +
            std::string(" | over a card, you should find the card with   |\t\t| on the computer also, because, as you know,  |\n") +
            std::string(" | the same drawing. If you pick the wrong      |\t\t| everything is more fun on the PC.            |\n") +
            std::string(" | card, both cards will be flipped over again  |\t\t| This game makes memory cool again, thanks    |\n") +
            std::string(" | and you get a new try. You should find all   |\t\t| to the use of the use of the modern Linux-   |\n") +
            std::string(" | combinations in as few steps as possible.    |\t\t| terminal-technology. And a lid, overkilled   |\n") +
            std::string(" | Your score will also be calculated based on  |\t\t| GUI is not even required. So if you're bored |\n") +
            std::string(" | this criterium.                              |\t\t| at work, use your office's Linux-server to   |\n") +
            std::string(" | The navigation within the game is done with  |\t\t| make a nostalgic trip down <memory> lane ;-).|\n") +
            std::string(" | the array keys. The little hand will show    |\t\t| It is even more fun if there are crytical    |\n") +
            std::string(" | you which card you are currently selecting.  |\t\t| applications running on your device *chuckle.|\n") +
            std::string(" | You can confirm your choice with the enter-  |\t\t| Good luck and enjoy!                         |\n") +
            std::string(" | key. You can exit the game with ctrl + c.    |\t\t|               ° copyright 1992 - Arno Baecke |\n") +
            std::string(" +----------------------------------------------+\t\t+----------------------------------------------+\n") +
            std::string("\n\n\n\n\t\t\t\tPRESS ANY KEY TO CONTINUE...\n");

            printw(instructions.c_str());

            getch();
            clear();
    }

    int Intro::AskDifficultyLevel(void) {
        printw("\n\n\n\tJust one last thing before we can start the game.\n\t\tWhat difficylty level do you prefer?");

        std::string options[3] = { "easy", "medium", "hard" };
        int optionsSize = (sizeof(options)/sizeof(*options));

        WINDOW * difficultyMenu = newwin((2 * optionsSize + 1), 60, 8, 5);
        box(difficultyMenu, 0, 0);
        refresh();
        wrefresh(difficultyMenu);

        keypad(difficultyMenu, true);

        int userInput = 0;
        int highlightedOption = 0;

        while(true) {
            for(int i = 0; i < optionsSize; i ++) {               
                if(i == highlightedOption) {
                    wattron(difficultyMenu, A_REVERSE);
                    mvwprintw(difficultyMenu, (1 + i * 2), 1, options[i].c_str());
                    wattroff(difficultyMenu, A_REVERSE);
                }
                else {
                    mvwprintw(difficultyMenu, (1 + i * 2), 1, options[i].c_str());
                }
            }

                userInput = wgetch(difficultyMenu);

                if(userInput == KEY_UP && (highlightedOption - 1) >= 0) {
                    highlightedOption--;
                }
                else if(userInput == KEY_DOWN && (highlightedOption + 1) < optionsSize) {
                    highlightedOption++;
                }

                if(userInput == 10) {
                    break;
                }
        }

        clear();

        return highlightedOption;
    }
}