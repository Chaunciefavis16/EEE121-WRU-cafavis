#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

class CarParking {
private:
    struct CarEntry {
        string plate;
        string brand;
        string model;
        string year;
        time_t entryTime;
        time_t exitTime;
        double totalHours;
        int totalCost;
    };

    vector<CarEntry> parkingDatabase;
    vector<CarEntry> parkingLogDatabase;

public:
    void parkCar(const string& plate, const string& brand, const string& model, const string& year) {
        for (size_t i = 0; i < parkingDatabase.size(); ++i) {
            if (parkingDatabase[i].plate == plate) {
                cout << "UNSUPPORTED COMMAND" << endl;
                return;
            }
        }

        CarEntry entry;
        entry.plate = plate;
        entry.brand = brand;
        entry.model = model;
        entry.year = year;
        entry.entryTime = time(NULL);
        entry.exitTime = 0;
        entry.totalHours = 0;
        entry.totalCost = 0;
        parkingDatabase.push_back(entry);
    }

    void carExit(const string& plate) {
        for (int i = 0; i < parkingDatabase.size(); i++) {
            if (parkingDatabase[i].plate == plate) {
                CarEntry carOut = parkingDatabase[i];

                carOut.exitTime = time(NULL);
                carOut.totalHours = static_cast<int>(ceil(difftime(carOut.exitTime, carOut.entryTime) / 3600));
                if (carOut.totalHours > 3) {
                    carOut.totalCost = 50 + ceil((carOut.totalHours - 3) * 20);
                } else {
                    carOut.totalCost = 50;
                }

                parkingLogDatabase.push_back(carOut);
                parkingDatabase.erase(parkingDatabase.begin() + i);

                cout << carOut.plate << "," << put_time(localtime(&carOut.entryTime), "%T") << ","
                    << put_time(localtime(&carOut.exitTime), "%T") << ","
                    << carOut.totalHours << "," << "P" << carOut.totalCost << "," << put_time(localtime(&carOut.entryTime), "%F") << ","
                    << carOut.brand << "," << carOut.model << "," << carOut.year << "\n" << endl;
                return;
            }
        }
        cout << "CAR NOT FOUND" << "\n" << endl;
    }

    void findCar(const string& plate) {
        for (size_t i = 0; i < parkingDatabase.size(); i++) {
            if (parkingDatabase[i].plate == plate) {
                cout << parkingDatabase[i].plate << ", " << put_time(localtime(&parkingDatabase[i].entryTime), "%T") << ", "
                    << put_time(localtime(&parkingDatabase[i].exitTime), "%T") << ", " << parkingDatabase[i].totalHours << ", "
                    << "P" << parkingDatabase[i].totalCost << ", " << put_time(localtime(&parkingDatabase[i].entryTime), "%F") << ", "
                    << parkingDatabase[i].brand << ", " << parkingDatabase[i].model << ", " << parkingDatabase[i].year << endl;
                return;
            }
        }
        cout << "CAR NOT FOUND" << endl;
    }

    void listCarEntries() {
        for (size_t i = 0; i < parkingDatabase.size(); i++) {
            cout << parkingDatabase[i].plate << ", " << put_time(localtime(&parkingDatabase[i].entryTime), "%T") << ", " << "NONE, "
                << parkingDatabase[i].totalHours << ", " << "P" << parkingDatabase[i].totalCost << ", " << put_time(localtime(&parkingDatabase[i].entryTime), "%F") << ", "
                << parkingDatabase[i].brand << ", " << parkingDatabase[i].model << ", " << parkingDatabase[i].year << endl;
        }
    }

    void logCarEntries() {
        for (size_t i = 0; i < parkingLogDatabase.size(); i++) {
            cout << parkingLogDatabase[i].plate << ", " << put_time(localtime(&parkingLogDatabase[i].entryTime), "%T") << ", "
                << put_time(localtime(&parkingLogDatabase[i].exitTime), "%T") << ", " << parkingLogDatabase[i].totalHours << ", "
                << "P" << parkingLogDatabase[i].totalCost << ", " << put_time(localtime(&parkingLogDatabase[i].entryTime), "%F") << ", "
                << parkingLogDatabase[i].brand << ", " << parkingLogDatabase[i].model << ", " << parkingLogDatabase[i].year << endl;
        }
    }

    void bubbleSort() {
        for (int i = 0; i < parkingDatabase.size() - 1; i++) {
            for (size_t k = 0; k < parkingDatabase.size(); k++) {
                cout << "ITER-" << i << " : " << parkingDatabase[k].plate << ", " << put_time(localtime(&parkingDatabase[k].entryTime), "%T") << ", " << "NONE, "
                    << parkingDatabase[k].totalHours << ", " << "P" << parkingDatabase[k].totalCost << ", " << put_time(localtime(&parkingDatabase[k].entryTime), "%F") << ", "
                    << parkingDatabase[k].brand << ", " << parkingDatabase[k].model << ", " << parkingDatabase[k].year << endl;
            }
            for (int j = 0; j < parkingDatabase.size() - i - 1; j++) {
                if (parkingDatabase[j].year > parkingDatabase[j + 1].year) {
                    swap(parkingDatabase[j], parkingDatabase[j + 1]);
                }
            }
        }
    }

    void binarySearch(const string& plate) {
        int left = 0;
        int right = parkingDatabase.size();
        for (int i = 0; i < parkingDatabase.size() - 1; i++) {
            for (int j = 0; j < parkingDatabase.size() - i - 1; j++) {
                if (parkingDatabase[j].plate > parkingDatabase[j + 1].plate) {
                    swap(parkingDatabase[j], parkingDatabase[j + 1]);
                }
            }
        }
        while (left <= right) {
            int middle = (left + right) / 2;
            cout << "MID-" << middle << " : " << parkingDatabase[middle].plate << ", " << put_time(localtime(&parkingDatabase[middle].entryTime), "%T") << ", " << "NONE, "
                << parkingDatabase[middle].totalHours << ", " << "P" << parkingDatabase[middle].totalCost << ", " << put_time(localtime(&parkingDatabase[middle].entryTime), "%F") << ", "
                << parkingDatabase[middle].brand << ", " << parkingDatabase[middle].model << ", " << parkingDatabase[middle].year << endl;

            if (parkingDatabase[middle].plate == plate) {
                cout << endl << parkingDatabase[middle].plate << ", " << put_time(localtime(&parkingDatabase[middle].entryTime), "%T") << ", "
                    << put_time(localtime(&parkingDatabase[middle].exitTime), "%T") << ", " << parkingDatabase[middle].totalHours << ", "
                    << "P" << parkingDatabase[middle].totalCost << ", " << put_time(localtime(&parkingDatabase[middle].entryTime), "%F") << ", "
                    << parkingDatabase[middle].brand << ", " << parkingDatabase[middle].model << ", " << parkingDatabase[middle].year << endl;
                break;
            }
            if (parkingDatabase[middle].plate < plate) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
    }
};

int main() {
    CarParking carParking;
    string userCommand;
    while (true) {
        cout << "> ";
        getline(cin, userCommand);
        stringstream commandStream(userCommand);
        string action;
        commandStream >> action;

        if (action == "PARK") {
            string plate, brand, model, year;
            if (commandStream >> plate >> brand >> model >> year) {
                cout << userCommand << endl;
                carParking.parkCar(plate, brand, model, year);
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (action == "EXIT") {
            string plate;
            if (commandStream >> plate) {
                cout << userCommand << endl;
                carParking.carExit(plate);
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (action == "FIND") {
            string plate;
            if (commandStream >> plate) {
                cout << userCommand << endl;
                carParking.findCar(plate);
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (action == "LIST") {
            if (!(commandStream)) {
                cout << "UNSUPPORTED COMMAND\n";
            } else {
                cout << userCommand << endl;
                carParking.listCarEntries();
            }
        } else if (action == "LOG") {
            if (!(commandStream)) {
                cout << "UNSUPPORTED COMMAND\n";
            } else {
                cout << userCommand << endl;
                carParking.logCarEntries();
            }
        } else if (action == "BSORT") {
            if (!(commandStream)) {
                cout << "UNSUPPORTED COMMAND\n";
            } else {
                cout << userCommand << endl;
                carParking.bubbleSort();
            }
        } else if (action == "BFIND") {
            string plate;
            if (commandStream >> plate) {
                cout << userCommand << endl;
                carParking.binarySearch(plate);
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (action == "QUIT") {
            cout << userCommand << endl;
            break;
        } else {
            cout << "UNSUPPORTED COMMAND\n";
        }
    }
    return 0;
}
