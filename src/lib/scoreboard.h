#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace WordBlaster {
    class Scoreboard {
        public:
            Scoreboard(std::string filePath);
        
        public:
            void Summary(std::vector<std::string> scoreboardLines, int currentScore, std::string username);

        private:
            std::vector<std::string> SortEntries(std::vector<std::string>);
            int ExtractScore(std::string entry);

        private:
            std::string filePath;
    };
}