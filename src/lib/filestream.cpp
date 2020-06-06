#include <iostream>
#include <fstream>
#include "filestream.h"

namespace WordBlaster
{

    std::vector<std::string> FileStream::ReadLines(std::string filePath)
    {
        std::vector<std::string> lines = {};
        std::ifstream txtfile(filePath);

        std::string line;
        // Read the next line from File untill it reaches the end.
        while (std::getline(txtfile, line))
        {
            // If line contains string of length > 0 then save it in vector
            if (line.size() > 0) {
                lines.push_back(line);
            }
        }

        txtfile.close();

        return lines;
    }

    void FileStream::WriteToScoreBoard(std::string filePath, int score, std::string nickname)
    {
        std::ofstream scoreboardFile(filePath, std::ios_base::app); //append

        scoreboardFile << score << ";" << nickname << std::endl;

        scoreboardFile.close();
    }
}