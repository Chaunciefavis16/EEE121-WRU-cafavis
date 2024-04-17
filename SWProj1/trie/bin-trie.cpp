#include <iostream>
#include <vector>
#include <string>
#include <list>          // Include the list library for storing prefixes
#include <unordered_map> // Include the unordered_map library for storing element counts

using namespace std;

const int BINARY_ALPHABET_SIZE = 2; // Define the binary alphabet size as 2 (0 and 1)

struct TrieNode // Define a structure for the Trie node
{
    TrieNode *children[BINARY_ALPHABET_SIZE]; // Pointers to the children nodes
    bool isEndOfWord;                         // Flag to indicate if the node is the end of a word
    int count;                                // Count of how many times this node is visited during insertion
};

struct Trie // Define a structure for the Trie
{
    TrieNode *root;                          // Pointer to the root node
    unordered_map<string, int> elementCount; // Map to store the count of each prefix
    list<string> prefixes;                   // List to store the prefixes
    int maxPrefixScore;                      // Maximum prefix score
    string maxPrefix;                        // Maximum prefix string
    int maxPrefixLength;                     // Length of the maximum prefix string
    int totalSubstrings;                     // Total number of substrings
    int numberOfNodes;                       // Number of nodes in the Trie

    Trie() // Constructor initializes the Trie object
    {
        root = getNode();    // Initialize the root node
        maxPrefixScore = 0;  // Initialize the maximum prefix score
        maxPrefixLength = 0; // Initialize the maximum prefix length
        totalSubstrings = 0; // Initialize the total number of substrings
        numberOfNodes = 1;   // Initialize the number of nodes
    }

    TrieNode *getNode() // Function to get a new node
    {
        TrieNode *newNode = new TrieNode(); // Create a new node
        if (newNode)
        {
            newNode->isEndOfWord = false;                  // Initialize the end of word flag to false
            newNode->count = 0;                            // Initialize the count to 0
            for (int i = 0; i < BINARY_ALPHABET_SIZE; i++) // creates two children for each node
                newNode->children[i] = nullptr;            // Initialize the children pointers to null
        }
        return newNode;
    }

    void insert(string key) // Function to insert a string into the Trie
    {
        int length = key.length(); // Get the length of the string
        if (length > 200)
        {
            cerr << "Error: Length of the string exceeds maximum allowed length of 200 characters." << endl;
            exit(EXIT_FAILURE); // Exit the function if length exceeds maximum
        }
        for (char c : key)
        {
            if (c != '0' && c != '1')
            {
                cerr << "Error: String contains characters other than '0' and '1'." << endl;
                exit(EXIT_FAILURE); // Exit the function if string contains invalid characters
            }                       // these are just checking paramaters bago magstart
        }
        TrieNode *crawl = root;                      // Initialize a pointer to the root node
        string prefix;                               // Initialize a string to store the current prefix
        for (int level = 0; level < length; level++) // iterate through the binary string
        {
            int index = key[level] - '0'; // 48 ung 0. use to convert to integer because because characters in C++ are represented using their ASCII values.
            prefix += key[level];         // Add the current symbol to the prefix
            if (!crawl->children[index])  // If the current node doesn't have a child at the current index
            {
                crawl->children[index] = getNode(); // Create a new node
                numberOfNodes++;                    // Increment the number of nodes
            }
            crawl = crawl->children[index]; // Move to the next node
            crawl->count++;                 // This count effectively tracks how many times this particular prefix has been encountered during the insertion process.
            prefixes.push_back(prefix);     // Add the current prefix to the list of prefixes
            elementCount[prefix]++;         // Increment the count of the current prefix

            int prefixScore = prefix.length() * elementCount[prefix]; // length * no. of occurences
            if (prefixScore > maxPrefixScore)                         // If the prefix score is greater than the maximum prefix score
            {
                maxPrefixScore = prefixScore;           // Update the maximum prefix goodness
                maxPrefix = prefix;                     // Update the maximum prefix string
                maxPrefixLength = prefix.length();      // Update the maximum prefix length
                totalSubstrings = elementCount[prefix]; // Update the total number of substrings that appeared
            }
        }
        crawl->isEndOfWord = true; // finally reached the end of the binary string
    }
};

int main()
{
    int testCases;
    cin >> testCases;
    if (testCases > 20)
    {
        cerr << "Error: Number of test cases exceeds the maximum limit of 20." << endl;
        return 1; // Exit the program with an error code
    }
    for (int testCase = 1; testCase <= testCases; testCase++)
    {
        int numberOfStrings;
        cin >> numberOfStrings;
        if (numberOfStrings > 50000)
        {
            cerr << "excceeded the number of strings" << endl;
            return 1;
        }
        vector<string> strings(numberOfStrings);
        for (int i = 0; i < numberOfStrings; i++)
        {
            cin >> strings[i];
            if (strings[i].length() > 200)
            {
                cerr << "Exceeds the length of the binary string" << endl;
                return 1;
            }
        }

        Trie trie;
        for (int i = 0; i < numberOfStrings; i++)
            trie.insert(strings[i]);

        int totalDigits = 0;
        for (string s : strings)
            totalDigits += s.length();

        cout << "Test Case #" << testCase << ":" << endl;
        cout << "Number of digits in all binary strings: " << totalDigits << endl;
        cout << "Number of nodes in Trie: " << trie.numberOfNodes << endl;
        cout << "Max Prefix Length: " << trie.maxPrefixLength << endl;
        cout << "Total Substrings: " << trie.totalSubstrings << endl;
        cout << "Prefix Goodness: " << trie.maxPrefixScore << endl;
    }
    return 0;
}
