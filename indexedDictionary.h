#ifndef INDEXEDDICTIONARY_
#define INDEXEDDICTIONARY_

#include "myList.h"
#include <vector>
#include <string>

// IndexedDictionary class to store and manage a dictionary of words
// The dictionary is indexed by the first letter of the word and the word length
class IndexedDictionary {
 private:
    // 2D vector of myList objects
    // Outer vector size is 26 (for each letter of the alphabet)
    // Inner vector size is 100 (assuming max word length is less than 100)
    vector<vector<myList<string>>> index;

    // Variable to keep track of the total number of words in the dictionary
    int size;

 public:
    // Constructor to initialize the index with 26x100 myList objects and set size to 0
    IndexedDictionary();

    // Method to insert a word into the dictionary
    // Words are indexed based on their first letter and length
    void insert(const string &word);

    // Method to find a word in the dictionary
    // Performs a search based on the word's first letter and length
    // Returns true if the word is found, false otherwise
    // The number of comparisons made is stored in the 'compare' variable
    bool find(const string &word, long long int &compare);

    // Method to get the total number of words in the dictionary
    int getSize() const;

    // Method to print the contents of the indexed dictionary for debugging
    void print();
};

// Constructor implementation
IndexedDictionary::IndexedDictionary() : index(26, vector<myList<string>>(100)), size(0) {}

// Insert method implementation
void IndexedDictionary::insert(const string &word) {
    if (word.empty()) return; // Do nothing if the word is empty

    // Convert the first character to lowercase and get the word length
    char firstChar = tolower(word[0]);
    int length = word.length();

    // Insert the word into the appropriate myList based on the first letter and length
    index[firstChar - 'a'][length].insert(word);

    // Increment the total size of the dictionary
    size++;
}
// Find method implementation
bool IndexedDictionary::find(const string &word, long long int &compare) {
    if (word.empty()) return false; // Return false if the word is empty

    // Convert the first character to lowercase and get the word length
    char firstChar = tolower(word[0]);
    int length = word.length();

    // Perform a search in the appropriate myList based on the first letter and length
    return index[firstChar - 'a'][length].find(word, compare);
}

// GetSize method implementation
int IndexedDictionary::getSize() const {
    return size; // Return the total number of words in the dictionary
}

// Print method implementation
void IndexedDictionary::print() {
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 100; ++j) {
            if (index[i][j].getSize() > 0) {
                cout << "Index [" << char('a' + i) << "][" << j << "]: ";
                index[i][j].print();
                cout << endl;
            }
        }
    }
}

#endif //