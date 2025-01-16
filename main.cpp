#include <iostream>
#include "videoGameManagementSystem.h"

int main() {
    VideoGameManagementSystem system;
    string filePath = "videogames.txt";
    system.loadDataFromTextFile(filePath);
    
    char choice;
    do {
        cout << "Menu:\n1. Display All Games\n2. Add Game\n3. Delete Game\n4. Change Game isPlayed State\n5. Games Played vs Not Played\n6. Save and Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            system.displayAllGames();
            break;
        case '2': {
            int newYear;
            string newTitle;
            string newSystem;
            string newSeries;
            string newPlayed;
            bool playedStatus;
            cout << "Enter Title: ";
            cin.ignore();
            getline(cin, newTitle);
            cout << "Enter Year: ";
            cin>>newYear;
            cout << "Enter System: ";
            cin.ignore();
            getline(cin, newSystem);
            cout << "Enter Series: ";
            cin.ignore();
            getline(cin, newSeries);
            cout << "Has the game been played? Answer y or n: ";
            getline(cin, newPlayed);
            
            if (newPlayed == "y" || newPlayed == "Y") {
                playedStatus = true;
            } else if (newPlayed == "n" || newPlayed == "N") {
                playedStatus = false;
            }
            system.addGame(newTitle, newYear, newSystem, newSeries, playedStatus);
            break;
        }
        case '3': {
            int deleteNumber;
            cout << "Please give me the number of the game you would like to delete: ";
            cin >> deleteNumber;
            system.deleteGame(deleteNumber);
            break;
        }
        case '4': {
            int updateNumber;
            string updateString;
            cout << "Please give me the number of the game you would like to update: ";
            cin >> updateNumber;
            cout << "Was the game played? Answer y or n: ";
            cin >> updateString;
            system.updatePlayedStatus(updateNumber, updateString);
            break;
        }
        case '5':
            system.gamesPlayed();
            break;
        case '6':
            cout << "Saving and exiting. Thank you.\n";
            system.saveDataToTextFile(filePath);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '6');

    return 0;
}