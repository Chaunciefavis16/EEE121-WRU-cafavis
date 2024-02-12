#include <iostream>

using namespace std;

bool isPrime(int number);

int main()
{
    char choice;

    do
    {
        int number;
        cout << "Enter an integer: ";
        cin >> number;

        if (isPrime(number))
        {
            cout << number << " is a prime number." << endl;
        }
        else
        {
            cout << number << " is not a prime number." << endl;
        }

        cout << "Do you want to run the program again? (Y to continue otherwise stop): ";
        cin >> choice;

        

    } while (choice == 'Y' || choice == 'y');

    return 0;
}

bool isPrime(int number)
{
    if (number <= 1)
    {
        return false; // 1 is not a prime number
    }

    for (int i = 2; i <= number / 2; ++i)
    {
        if (number % i == 0)
        {
            return false; // Found a factor, so not prime
        }
    }

    return true; // No factors found, so prime
}
