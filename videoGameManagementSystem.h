#ifndef VIDEOGAMEMANAGEMENTSYSTEM_H
#define VIDEOGAMEMANAGEMENTSYSTEM_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype> 
#include "videoGame.h"
using namespace std;

class VideoGameManagementSystem {
private:
    vector<videoGame> games;

public:
void loadDataFromTextFile(const std::string& filePath) {
    ifstream file(filePath);
    if (!file) {
        cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    std::string line;
    int number = 1;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, system, series, playedStr;
        std::string yearStr;

        if (std::getline(iss, title, ',') &&
            std::getline(iss, yearStr, ',') && 
            std::getline(iss, system, ',') &&
            std::getline(iss, series, ',') &&
            std::getline(iss, playedStr, ',')) {

            int year = std::stoi(yearStr);

            bool played = (playedStr == "Y");
            games.emplace_back(number, title, year, system, series, played);
            number++;
        } else {
            std::cerr << "Warning: Malformed line skipped: " << line << std::endl;
        }
    }

    file.close();
}
void displayAllGames() const {
    if (games.empty()) {
        std::cout << "No games available to display." << std::endl;
        return;
    }

    std::cout << "Displaying all games:" << std::endl;
    for (const auto& game : games) {
        game.print();
    }
}
void sortGames() {
    sort(games.begin(), games.end(),
        [](const videoGame& a, const videoGame& b) {
            if (a.getYear() != b.getYear()) {
                return a.getYear() < b.getYear();
            }
            return a.getTitle() < b.getTitle(); 
        });

    for (size_t i = 0; i < games.size(); ++i) {
        games[i] = videoGame(
            i + 1, 
            games[i].getTitle(),
            games[i].getYear(),
            games[i].getSystem(),
            games[i].getSeries(),
            games[i].isPlayed()
        );
    }
}
void addGame(const std::string& title, int year, const std::string& system,
             const std::string& series, bool played) {
    int number = games.empty() ? 1 : games.back().getNumber() + 1;
    games.emplace_back(number, title, year, system, series, played);
    sortGames();
    std::cout << "Game added successfully!" << std::endl;
}
void saveDataToTextFile(const std::string& filePath) const {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "Error: Could not open file for writing: " << filePath << std::endl;
        return;
    }

    for (const auto& game : games) {
        file << game.getTitle() << ","
             << game.getYear() << "," 
             << game.getSystem() << ","
             << game.getSeries() << ","
             << (game.isPlayed() ? "Y" : "N") << std::endl;
    }

    file.close();
    std::cout << "Data saved successfully to " << filePath << std::endl;
}
void updatePlayedStatus(int searchNumber, std::string& isPlayedStatus) {
    bool newPlayedStatus;
    if (isPlayedStatus == "Y" || isPlayedStatus == "y" || isPlayedStatus == "yes" || isPlayedStatus == "Yes" || isPlayedStatus == "YES") {
        newPlayedStatus = true;
    }
    if (isPlayedStatus == "N" || isPlayedStatus == "n" || isPlayedStatus == "no" || isPlayedStatus == "No" || isPlayedStatus == "NO") {
        newPlayedStatus = false;
    }
    else {
        std::cout << "Invalid input for played status.";
        return;
    }
    for (auto& game : games) {
        if (game.getNumber() == searchNumber) {
            game = videoGame(
                game.getNumber(),
                game.getTitle(),
                game.getYear(),
                game.getSystem(),
                game.getSeries(),
                newPlayedStatus
            );
            std::cout << "Played status for game number " << searchNumber
                      << " updated to " << (newPlayedStatus ? "Played" : "Not Played") << ".\n";
            return;
        }
    }
    std::cout << "Game with number " << searchNumber << " not found!\n";
}
void deleteGame(int gameNumber) {
    for (auto it = games.begin(); it != games.end(); ++it) {
        if (it->getNumber() == gameNumber) { 
            games.erase(it);
            std::cout << "Game with number " << gameNumber << " has been deleted.\n";
            sortGames();
            return;
        }
    }
    std::cout << "Game with number " << gameNumber << " not found!\n";
}
void gamesPlayed () {
    int isPlayed = 0;
    int isNotPlayed = 0;
    int totalGames = 0;
    for (auto& game : games) {
        if (game.isPlayed()) {
            isPlayed++;
        }
        else {
            isNotPlayed++;
        }
        totalGames++;
    }
    std::cout << "Out of " << totalGames << " games, " << isPlayed << " games have been played and " << isNotPlayed << " games have not been played.\n";
    return;
}
};

#endif
