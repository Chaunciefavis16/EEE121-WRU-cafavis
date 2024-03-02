#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;

struct ParkingEntry {
    string plateNumber;
    string brand;
    string model;
    int year;
    time_t entryTime;
    time_t exitTime;
    double totalHours;
    double totalCost;

    ParkingEntry() : exitTime(0), totalHours(0), totalCost(0) {}
};

class ParkingSystem {
private:
    vector<ParkingEntry> currentDatabase;
    vector<ParkingEntry> historyDatabase;
    const int maxCurrentEntries = 500;
    const int maxHistoryEntries = 1000;

public:
    void parseCommand(const string& command) {
        cout << command << endl;

        stringstream ss(command);
        string op;
        ss >> op;

        if (op == "PARK") {
            parkCar(ss);
        } else if (op == "EXIT") {
            exitCar(ss);
        } else if (op == "FIND") {
            findEntry(ss);
        } else if (op == "LIST") {
            listEntries(currentDatabase, maxCurrentEntries);
        } else if (op == "LOG") {
            listEntries(historyDatabase, maxHistoryEntries);
        } else if (op == "QUIT") {
            exit(0);
        } else {
            cout << "Unsupported command: " << op << endl;
        }
    }

    void parkCar(stringstream& ss) {
        ParkingEntry entry;
        ss >> entry.plateNumber >> entry.brand >> entry.model >> entry.year;

        entry.entryTime = time(nullptr);

        currentDatabase.push_back(entry);

        // Check and remove the oldest entry if currentDatabase exceeds the limit
        if (currentDatabase.size() > maxCurrentEntries) {
            currentDatabase.erase(currentDatabase.begin());
        }
    }

    void exitCar(stringstream& ss) {
        string plateNumber;
        ss >> plateNumber;

        auto it = find_if(currentDatabase.begin(), currentDatabase.end(),
                          [plateNumber](const ParkingEntry& entry) {
                              return entry.plateNumber == plateNumber;
                          });

        if (it != currentDatabase.end()) {
            it->exitTime = time(nullptr);
            it->totalHours = calculateDuration(it->entryTime, it->exitTime);
            it->totalCost = calculateCost(it->totalHours);

            // Move the entry to historyDatabase
            historyDatabase.push_back(*it);
            currentDatabase.erase(it);

            // Check and remove the oldest entry if historyDatabase exceeds the limit
            if (historyDatabase.size() > maxHistoryEntries) {
                historyDatabase.erase(historyDatabase.begin());
            }

            // Print details in CSV format
            cout << it->plateNumber << ", " << ctime(&it->entryTime) << ", " << ctime(&it->exitTime) << ", ";
            cout << fixed << setprecision(2) << it->totalHours << ", " << fixed << setprecision(2) << it->totalCost << ", ";
            cout << ctime(&it->entryTime) << ", " << it->brand << ", " << it->model << ", " << it->year << endl;
            
        } else {
            cout << "CAR NOT FOUND" << endl;
        }
    }

    void findEntry(stringstream& ss) {
        string plateNumber;
        ss >> plateNumber;

        auto it = find_if(currentDatabase.begin(), currentDatabase.end(),
                          [plateNumber](const ParkingEntry& entry) {
                              return entry.plateNumber == plateNumber;
                          });

        if (it != currentDatabase.end()) {
            cout << it->plateNumber << ", " << ctime(&it->entryTime) << ", ";
            if (it->exitTime != 0) {
                cout << ctime(&it->exitTime) << ", " << fixed << setprecision(2) << it->totalHours << ", ";
                cout << fixed << setprecision(2) << it->totalCost << ", ";
            } else {
                cout << "NONE, 0.00, P0, ";
            }
            cout << ctime(&it->entryTime) << ", " << it->brand << ", " << it->model << ", " << it->year << endl;
        } else {
            cout << "CAR NOT FOUND" << endl;
        }
    }

    void listEntries(const vector<ParkingEntry>& database, int maxEntries) {
        int count = 0;
        for (const auto& entry : database) {
            if (entry.exitTime != 0) {
                cout << entry.plateNumber << ", " << ctime(&entry.entryTime) << ", " << ctime(&entry.exitTime) << ", " << fixed << setprecision(2) << entry.totalHours << ", " << fixed << setprecision(2) << entry.totalCost << ", ";
                cout << ctime(&entry.entryTime) << ", " << entry.brand << ", " << entry.model << ", " << entry.year;
            } else {
                cout << entry.plateNumber << ", " << ctime(&entry.entryTime) << ", " << "NONE, 0.00, P0, " << ctime(&entry.entryTime) << ", " << entry.brand << ", " << entry.model << ", " << entry.year;
            }

            count++;
            if (count < maxEntries) {
                cout << ", " << endl;
            } else {
                cout << endl;
                break;
            }
        }
    }

    double calculateDuration(time_t entryTime, time_t exitTime) {
        return difftime(exitTime, entryTime) / 3600.0;
    }

    double calculateCost(double totalHours) {
        const double firstThreeHoursCost = 50.0;
        const double hourlyRate = 20.0;

        if (totalHours <= 3) {
            return firstThreeHoursCost;
        } else {
            return firstThreeHoursCost + hourlyRate * (totalHours - 3);
        }
    }
};

int main() {
    ParkingSystem parkingSystem;

    while (true) {
        string command;
        cout << "> ";
        getline(cin, command);

        parkingSystem.parseCommand(command);
    }

    return 0;
}
