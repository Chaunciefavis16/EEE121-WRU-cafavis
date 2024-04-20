#include <iostream>
#include <unordered_map> // Include the unordered_map library for storing Morse codes
#include <string>

using namespace std;

struct MorseTrieNode // Define a structure for the Morse code trie node
{
    MorseTrieNode *nextNodes[2]; // array of pointers that stores Pointers to the next nodes in the trie
    bool isEndOfWord;            // Flag to indicate if the node represents the end of a word
    char symbol;                 // The symbol associated with the node (if any)

    MorseTrieNode() : isEndOfWord(false), symbol('\0') // Constructor initializes the node with default values
    {
        nextNodes[0] = nullptr; // Initialize the next nodes to null
        nextNodes[1] = nullptr;
    }
};

class MorseCodeTranslator // Define a class for the Morse code translator
{
public:
    MorseCodeTranslator() // Constructor initializes the root node and builds the trie
    {
        root = new MorseTrieNode();
        buildTrie(); // creates the morse code trie, calls the insert node function
    }

    void encodeMessage(string message, MorseTrieNode *currentNode = nullptr, string currentCode = "")
{
    // If the currentNode is nullptr, set it to the root node
    if (currentNode == nullptr)
    {
        currentNode = root;
    }

    // Base case: if the message is empty, print the encoded Morse code
    if (message.empty())
    {
        cout << currentCode << endl;
        return;
    }

    // Get the first character of the message
    char currentChar = message[0];

    // If the character is a space, append a slash to the Morse code and continue with the rest of the message
    if (currentChar == ' ')
    {
        encodeMessage(message.substr(1), root, currentCode + "/ ");
    }
    else
    {
        // Convert the character to uppercase
        currentChar = toupper(currentChar);

        // Determine the index for dot or dash (0 for dot, 1 for dash)
        int index = (currentChar == '.') ? 0 : 1;

        // If the next node does not exist
        if (!currentNode->nextNodes[index])
        {
            // Print error message for invalid character for encoding and return
            cout << "Error: Invalid character for encoding: " << currentChar << endl;
            return;
        }

        // Recursively encode the rest of the message using the next node in the trie
        encodeMessage(message.substr(1), currentNode->nextNodes[index], currentCode + currentChar);
    }
}


    void decodeMessage(string code) // uses the trie
    {
        string decoded;                    // creates a string to store the decoded message
        MorseTrieNode *currentNode = root; // creates a pointer to the root of the morse trie
        string morseChar;                  // accumulate the Morse code sequence for each character in the input code

        for (char c : code)
        {
            // Check if the current character is a space or a slash
            if (c == '/' || c == ' ')
            {
                // If Morse character sequence is not empty / or ' ' means that dat wala ng idedecode kasi kumpleto na siya
                if (!morseChar.empty())
                {
                    // If the current node is not the end of a valid Morse code sequence
                    if (!currentNode->isEndOfWord)
                    {
                        // Print error message for invalid Morse code and return
                        cout << "Error: Invalid Morse code: " << code << endl;
                        return;
                    }
                    // Append the decoded character to the decoded message
                    decoded += currentNode->symbol;
                    // Reset the current node to the root
                    currentNode = root;
                    // Clear the Morse character sequence
                    morseChar.clear();
                }
                // If the current character is a slash, append a space to the decoded message
                if (c == '/')
                    decoded += ' ';
            }
            // If the current character is a dot or a dash
            else if (c == '.' || c == '-')
            {
                // Accumulate the Morse character sequence
                morseChar += c;
                // Determine the index for dot or dash (0 for dot, 1 for dash)
                int index = (c == '.') ? 0 : 1;
                // If the next node does not exist
                if (!currentNode->nextNodes[index])
                {
                    // Print error message for invalid Morse code and return
                    cout << "Error: Invalid Morse code: " << code << endl;
                    return;
                }
                // Move to the next node in the Morse trie
                currentNode = currentNode->nextNodes[index];
            }
            // If the current character is neither dot, dash, space, nor slash
            else
            {
                // Print error message for invalid character for decoding and return
                cout << "Error: Invalid character for decoding: " << c << endl;
                return;
            }
        }
        // After processing all characters, if Morse character sequence is not empty and the current node is the end of a valid Morse code sequence
        if (!morseChar.empty() && currentNode->isEndOfWord)
        {

            decoded += currentNode->symbol; // Append the decoded character to the decoded message
        }

        cout << decoded << endl; // Print the decoded message
    }

    void decode_encode(string input) // Function to decode or encode a message based on the input
    {
        for (char &c : input) // Iterate through each character in the input
        {
            if (c == '\n') // Skip newline characters
            {
                continue;
            }
            c = toupper(c); // Convert the character to uppercase
        }

        if (input.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ") == string::npos) // If the input only contains alphanumeric characters and spaces
        {
            encodeMessage(input); // Encode the message
        }
        else if (input.find_first_not_of(".-/ ") == string::npos) // If the input only contains Morse code characters, slashes, and spaces
        {
            decodeMessage(input); // Decode the message
        }
        else
        {
            cout << "Error: Invalid input" << endl; // Print an error message and return
            return;
        }
    }

private:
    MorseTrieNode *root;                       // Pointer to the root node of the Morse code trie
    unordered_map<char, string> morseCodes = { // Map of Morse code symbols and their corresponding codes
        {'A', ".-"},
        {'B', "-..."},
        {'C', "-.-."},
        {'D', "-.."},
        {'E', "."},
        {'F', "..-."},
        {'G', "--."},
        {'H', "...."},
        {'I', ".."},
        {'J', ".---"},
        {'K', "-.-"},
        {'L', ".-.."},
        {'M', "--"},
        {'N', "-."},
        {'O', "---"},
        {'P', ".--."},
        {'Q', "--.-"},
        {'R', ".-."},
        {'S', "..."},
        {'T', "-"},
        {'U', "..-"},
        {'V', "...-"},
        {'W', ".--"},
        {'X', "-..-"},
        {'Y', "-.--"},
        {'Z', "--.."},
        {'0', "-----"},
        {'1', ".----"},
        {'2', "..---"},
        {'3', "...--"},
        {'4', "....-"},
        {'5', "....."},
        {'6', "-...."},
        {'7', "--..."},
        {'8', "---.."},
        {'9', "----."},
        {' ', "/"}

    };
    void buildTrie() // Function to build the Morse code trie and stores the value
    {
        for (const auto &pair : morseCodes) // Iterate through each pair in the Morse code map
        {
            insertNode(root, pair.second, pair.first); // Insert the node into the trie
        }
    }

    void insertNode(MorseTrieNode *node, const string &morseCode, char data) // Function to insert a node into the Morse code trie
    {
        for (char c : morseCode) // Iterate through each dot and dash in the Morse code
        {
            int index = (c == '.') ? 0 : 1;        // check if its a dot or a dash/ this is a ternary operator
            if (node->nextNodes[index] == nullptr) // If the next node is null
            {
                node->nextNodes[index] = new MorseTrieNode(); // Create a new node
            }
            node = node->nextNodes[index]; // Move to the next node
        }
        node->isEndOfWord = true; // Set the end of word flag for the node
        node->symbol = data;      // Set the correspondimg character to that node
    }
};

int main() //
{
    MorseCodeTranslator morse_code;  // Create a MorseCodeTranslator object
    string input;                    // Initialize an empty string to store the input
    getline(cin, input);             // Get the input from the user
    morse_code.decode_encode(input); // Call the decode_encode function to decode or encode the input
    return 0;
}
