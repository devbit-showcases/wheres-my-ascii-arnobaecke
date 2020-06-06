#pragma once

#include <string>
#include <vector>

namespace WordBlaster {
    class FileStream {
        
        public:
            std::vector<std::string> ReadLines(std::string filePath);
            void WriteToScoreBoard(std::string filePath, int score, std::string nickname);
    };
}