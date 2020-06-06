#include "scoreboard.h"

namespace WordBlaster {

    Scoreboard::Scoreboard(std::string filePath)
    {
        this->filePath = filePath;
    }

    void Scoreboard::Summary(std::vector<std::string> scoreboardLines, int currentScore, std::string nickname)
    {
        std::vector<std::string> sortedEntries = SortEntries(scoreboardLines);

        std::cout << "Your score is " << currentScore << "%.\n" << std::endl;
        std::cout << "SCOREBOARD:" << std::endl;
        std::cout << "-----------" << std::endl;

        for(unsigned int i = 0; i < sortedEntries.size(); i++) {
            std::replace(sortedEntries[i].begin(), sortedEntries[i].end(), ';', '-');

            std::cout << "[" << i + 1 << "] " << sortedEntries[i];

            if(sortedEntries[i] == std::to_string(currentScore) + "-" + nickname) {
                std::cout << " <";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> Scoreboard::SortEntries(std::vector<std::string> scoreboardLines)
    {
        std::vector<std::string> entries = scoreboardLines;

        // this sorting algorythm is based on this example: https://bit.ly/3bGCzFK
        for (unsigned int i = 0; i < entries.size() -1; i++)  
        {
            // Checking the condition for two simultaneous elements of the array
            if (ExtractScore(entries[i]) < ExtractScore(entries[i + 1]))  
            {
                // Swapping the elements. 
                std::string temp = entries[i]; 
                entries[i] = entries[i + 1]; 
                entries[i + 1] = temp; 
                
                // Don't skip the next entry
                i = -1; 
            } 
        }
        return entries; 
    }

    int Scoreboard::ExtractScore(std::string entry)
    {
        return std::stoi(entry.substr(0, entry.find(";")));
    }
}