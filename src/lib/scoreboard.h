#pragma once

#include "filestream.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

namespace AsciiGame {
    class Scoreboard {
        public:
            Scoreboard(std::string filePath, int currentScore, std::string currentNickname);
        
        public:
            void Summary(std::vector<std::string> scoreboardLines, int currentScore, std::string username);

        private:
            std::vector<std::string> SortEntries(std::vector<std::string>);
            int ExtractScore(std::string entry);

        private:
            std::string filePath = "";
            int currentScore = 0;
            std::string currentNickname = "";
    };
}