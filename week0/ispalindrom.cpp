#include <algorithm>
#include <iostream>
#include <algorithm>

using namespace std;

bool isPalindrome(std::string string_1);

int main()
{
    char choice;

    do
    {
        string string_1;
        cout<< "INPUT A STRING: ";
        cin >> string_1;

        if (isPalindrome(string_1))
        {
            cout << string_1 << " is a palindrome. " << endl;
        }
        else
        {
            cout << string_1 << " is not  a palindrome. " << endl;
        }
        cout << "Do you want to run the program again? (Y to continue otherwise stop): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    return 0;
}

bool isPalindrome(std::string string_1){
    string reversed_string = string_1;

    reverse(string_1.begin(), string_1.end());
    
    if (string_1== reversed_string){
        return true;
    }
    else {
        return false;
    }
}





