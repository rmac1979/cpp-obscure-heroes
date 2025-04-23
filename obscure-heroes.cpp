/*
Author: Ryan McCamy
Assignment: Obscure Superheroes
Description: Database that stores and manipulates information about lesser-known superheroes.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_HEROES = 100;
int heroCount = 3; // Starting with 3 predefined heroes

// Parallel Arrays
string names[MAX_HEROES] = {"Squirrel Girl", "Arm-Fall-Off-Boy", "The Tick"};
string superpowers[MAX_HEROES] = {"Control Squirrels", "Detachable Limbs", "Super Strength"};
string weaknesses[MAX_HEROES] = {"Time Limits", "Heavy Objects", "Poor Judgment"};

// Multidimensional Array
int yearsAndUniverses[MAX_HEROES][2] = { {1992, 0}, {1989, 1}, {1986, 2} }; // 0 = Marvel, 1 = DC, 2 = Other

// Additional Arrays
int popularity[MAX_HEROES] = {80, 60, 75}; // Optional: Popularity score out of 100

string universeToString(int code) {
    switch (code) {
        case 0: return "Marvel";
        case 1: return "DC";
        case 2: return "Other";
        default: return "Unknown";
    }
}

void displayHero(int index, bool toUpper = false, bool toLower = false) {
    string name = names[index], power = superpowers[index], weak = weaknesses[index];
    if (toUpper) {
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        transform(power.begin(), power.end(), power.begin(), ::toupper);
        transform(weak.begin(), weak.end(), weak.begin(), ::toupper);
    } else if (toLower) {
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(power.begin(), power.end(), power.begin(), ::tolower);
        transform(weak.begin(), weak.end(), weak.begin(), ::tolower);
    }

    cout << name << " | " << power << " | " << weak << " | "
         << yearsAndUniverses[index][0] << " | "
         << universeToString(yearsAndUniverses[index][1]) << " | "
         << "Popularity: " << popularity[index] << endl;
}

void displayAll(bool upper = false, bool lower = false) {
    for (int i = 0; i < heroCount; ++i)
        displayHero(i, upper, lower);
}

void searchByName(string query) {
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    for (int i = 0; i < heroCount; ++i) {
        string name = names[i];
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name.find(query) != string::npos)
            displayHero(i);
    }
}

void searchByPower(string query) {
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    for (int i = 0; i < heroCount; ++i) {
        string power = superpowers[i];
        transform(power.begin(), power.end(), power.begin(), ::tolower);
        if (power.find(query) != string::npos)
            displayHero(i);
    }
}

void sortAlphabetically() {
    for (int i = 0; i < heroCount - 1; ++i) {
        for (int j = i + 1; j < heroCount; ++j) {
            if (names[i] > names[j]) {
                swap(names[i], names[j]);
                swap(superpowers[i], superpowers[j]);
                swap(weaknesses[i], weaknesses[j]);
                swap(yearsAndUniverses[i], yearsAndUniverses[j]);
                swap(popularity[i], popularity[j]);
            }
        }
    }
}

void addHero() {
    if (heroCount >= MAX_HEROES) {
        cout << "Database full!" << endl;
        return;
    }
    cout << "Enter name: ";
    getline(cin, names[heroCount]);
    cout << "Enter superpower: ";
    getline(cin, superpowers[heroCount]);
    cout << "Enter weakness: ";
    getline(cin, weaknesses[heroCount]);
    cout << "Enter year introduced: ";
    cin >> yearsAndUniverses[heroCount][0];
    cout << "Universe (0: Marvel, 1: DC, 2: Other): ";
    cin >> yearsAndUniverses[heroCount][1];
    cout << "Popularity (0-100): ";
    cin >> popularity[heroCount];
    cin.ignore(); // clear input buffer
    heroCount++;
}

void showTopRanked() {
    int maxIndex = 0;
    for (int i = 1; i < heroCount; ++i) {
        if (popularity[i] > popularity[maxIndex])
            maxIndex = i;
    }
    cout << "Top Ranked Hero:\n";
    displayHero(maxIndex);
}

void randomHero() {
    srand(time(0));
    int index = rand() % heroCount;
    cout << "Random Hero:\n";
    displayHero(index);
}

int main() {
    int choice;
    string input;
    do {
        cout << "\n=== Superhero Database ===\n";
        cout << "1. Display All\n2. Search by Name\n3. Search by Power\n4. Sort Alphabetically\n";
        cout << "5. Display UPPERCASE\n6. Display lowercase\n7. Add New Hero\n8. Show Top Ranked\n9. Random Hero\n0. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore(); // Flush newline

        switch (choice) {
            case 1: displayAll(); break;
            case 2: cout << "Name to search: "; getline(cin, input); searchByName(input); break;
            case 3: cout << "Power to search: "; getline(cin, input); searchByPower(input); break;
            case 4: sortAlphabetically(); cout << "Sorted!\n"; break;
            case 5: displayAll(true, false); break;
            case 6: displayAll(false, true); break;
            case 7: addHero(); break;
            case 8: showTopRanked(); break;
            case 9: randomHero(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
