#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cmath>

using namespace std;

class Parking
{
private:
    struct Car_Entry
    {
        string plate;
        string brand;
        string model;
        string year;
        time_t entT;
        time_t exT;
        double tHours;
        int tCost;
    };

    vector<Car_Entry> parkingDb;
    vector<Car_Entry> parkingLogDb;

public:
    void park(const string &plate, const string &brand, const string &model, const string &year)
    {
        for (size_t i = 0; i < parkingDb.size(); ++i)
        {
            if (parkingDb[i].plate == plate)
            {
                cout << "UNSUPPORTED COMMAND" << endl;
                return;
            }
        }

        Car_Entry entry;
        entry.plate = plate;
        entry.brand = brand;
        entry.model = model;
        entry.year = year;
        entry.entT = time(NULL);
        entry.exT = 0;
        entry.tHours = 0;
        entry.tCost = 0;
        parkingDb.push_back(entry);
    }

    void exit(const string &plate)
    {
        for (int i = 0; i < parkingDb.size(); i++)
        {
            if (parkingDb[i].plate == plate)
            {
                Car_Entry car_out = parkingDb[i];

                car_out.exT = time(NULL);
                car_out.tHours = static_cast<int>(ceil(difftime(car_out.exT, car_out.entT) / 3600));
                if (car_out.tHours > 3)
                {
                    car_out.tCost = 50 + ceil((car_out.tHours - 3) * 20);
                }
                else
                {
                    car_out.tCost = 50;
                }

                parkingLogDb.push_back(car_out);
                parkingDb.erase(parkingDb.begin() + i);

                cout << car_out.plate << "," << put_time(localtime(&car_out.entT), "%T") << "," << put_time(localtime(&car_out.exT), "%T") << ","
                     << car_out.tHours << ","
                     << "P" << car_out.tCost << "," << put_time(localtime(&car_out.entT), "%F") << ","
                     << car_out.brand << "," << car_out.model << "," << car_out.year << "\n"
                     << endl;
                return;
            }
        }
        cout << "CAR NOT FOUND"
             << "\n"
             << endl;
    }

    void findCar(const string &plate)
    {
        for (size_t i = 0; i < parkingDb.size(); i++)
        {
            if (parkingDb[i].plate == plate)
            {
                cout << parkingDb[i].plate << ", " << put_time(localtime(&parkingDb[i].entT), "%T") << ", "
                     << put_time(localtime(&parkingDb[i].exT), "%T") << ", " << parkingDb[i].tHours << ", "
                     << "P" << parkingDb[i].tCost << ", " << put_time(localtime(&parkingDb[i].entT), "%F") << ", "
                     << parkingDb[i].brand << ", " << parkingDb[i].model << ", " << parkingDb[i].year << endl;
                return;
            }
        }
        cout << "CAR NOT FOUND" << endl;
    }

    void listEntries()
    {
        for (size_t i = 0; i < parkingDb.size(); i++)
        {
            cout << parkingDb[i].plate << ", " << put_time(localtime(&parkingDb[i].entT), "%T") << ", "
                 << "NONE, "
                 << parkingDb[i].tHours << ", "
                 << "P" << parkingDb[i].tCost << ", " << put_time(localtime(&parkingDb[i].entT), "%F") << ", "
                 << parkingDb[i].brand << ", " << parkingDb[i].model << ", " << parkingDb[i].year << endl;
        }
    }

    void logEntries()
    {
        for (size_t i = 0; i < parkingLogDb.size(); i++)
        {
            cout << parkingLogDb[i].plate << ", " << put_time(localtime(&parkingLogDb[i].entT), "%T") << ", "
                 << put_time(localtime(&parkingLogDb[i].exT), "%T") << ", " << parkingLogDb[i].tHours << ", "
                 << "P" << parkingLogDb[i].tCost << ", " << put_time(localtime(&parkingLogDb[i].entT), "%F") << ", "
                 << parkingLogDb[i].brand << ", " << parkingLogDb[i].model << ", " << parkingLogDb[i].year << endl;
        }
    }

    void bSort()
    {
        for (int i = 0; i < parkingDb.size() - 1; i++)
        {
            for (size_t k = 0; k < parkingDb.size(); k++)
            {
                cout << "ITER-" << i << " : " << parkingDb[k].plate << ", " << put_time(localtime(&parkingDb[k].entT), "%T") << ", "
                     << "NONE, "
                     << parkingDb[k].tHours << ", "
                     << "P" << parkingDb[k].tCost << ", " << put_time(localtime(&parkingDb[k].entT), "%F") << ", "
                     << parkingDb[k].brand << ", " << parkingDb[k].model << ", " << parkingDb[k].year << endl;
            }
            for (int j = 0; j < parkingDb.size() - i - 1; j++)
            {
                if (parkingDb[j].year > parkingDb[j + 1].year)
                {
                    swap(parkingDb[j], parkingDb[j + 1]);
                }
            }
        }
    }
};

int main()
{
    Parking parking;
    string statement;
    while (true)
    {
        cout << "> ";
        getline(cin, statement);
        stringstream ss(statement);
        string command;
        ss >> command;

        if (command == "PARK")
        {
            string plate, brand, model, year;
            if (ss >> plate >> brand >> model >> year)
            {
                cout << statement << endl;
                parking.park(plate, brand, model, year);
            }
            else
            {
                cout << "UNSUPPORTED COMMAND\n";
            }
        }
        else if (command == "EXIT")
        {
            string plate;
            if (ss >> plate)
            {
                cout << statement << endl;
                parking.exit(plate);
            }
            else
            {
                cout << "UNSUPPORTED COMMAND\n";
            }
        }
        else if (command == "FIND")
        {
            string plate;
            if (ss >> plate)
            {
                cout << statement << endl;
                parking.findCar(plate);
            }
            else
            {
                cout << "UNSUPPORTED COMMAND\n";
            }
        }
        else if (command == "LIST")
        {
            if (!(ss))
            {
                cout << "UNSUPPORTED COMMAND\n";
            }
            else
            {
                cout << statement << endl;
                parking.listEntries();
            }
        }
        else if (command == "LOG")
        {
            if (!(ss))
            {
                cout << "UNSUPPORTED COMMAND\n";
            }
            else
            {
                cout << statement << endl;
                parking.logEntries();
            }
        }
        else if (command == "BSORT")
        {
            if (!(ss))
            {
                cout << "UNSUPPORTED COMMAND\n";
            }
            else
            {
                cout << statement << endl;
                parking.bSort();
            }
        }
        // this is for part 2 else if (command == "BFIND")
        // {  
        // }
        else if (command == "QUIT")
        {
            cout << statement << endl;
            break;
        }
        else
        {
            cout << "UNSUPPORTED COMMAND\n";
        }
    }
    return 0;
}
