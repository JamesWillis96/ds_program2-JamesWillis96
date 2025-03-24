#include <iostream>
#include <fstream>
#include <string>
#include "timer.h"
#include "BinaryTree.h"  // Include the updated BinarySearchTree header

using namespace std;

// Function to clean and sanitize words
string cleanWord(string word) {
    string cleaned = "";
    for (char c : word) {
        if (isalpha(c) || isdigit(c) || c == '\'') {
            cleaned += tolower(c);
        }
    }
    return cleaned; // Return the cleaned word
}

int main() {
    BinarySearchTree<string> dictionary; // Use BST instead of IndexedDictionary
    ifstream dictFile("dict.txt");       // Open dictionary file
    ifstream bookFile("book.txt");       // Open book file

    // Check if dictionary file opened successfully
    if (!dictFile.is_open()) {
        cerr << "Error: Unable to open dictionary file." << endl;
        return 1;
    }

    // Check if book file opened successfully
    if (!bookFile.is_open()) {
        cerr << "Error: Unable to open book file." << endl;
        return 1;
    }

    string word;
    long long int compare = 0;

    // Read and insert dictionary words
    while (dictFile >> word) {
        word = cleanWord(word);
        if (!word.empty()) {
            dictionary.insert(word);
        }
    }
    dictFile.close();

    Timer Watch;
    Watch.Start(); // Start timing spell checking

    int correctWords = 0;
    int incorrectWords = 0;
    int skippedWords = 0;
    long long int correctCompares = 0;
    long long int incorrectCompares = 0;
    ofstream misspelledFile("misspelled.txt");

    // Read and check book words
    while (bookFile >> word) {
        word = cleanWord(word);
        if (word.empty()) {
            continue; // Skip blank words, not counted as skipped
        }
        if (!isalpha(word[0])) {
            skippedWords++;
            continue; // Skip words not starting with a letter
        }

        compare = 0; // Reset comparison counter

        if (dictionary.find(word, compare) != nullptr) {
            correctWords++;
            correctCompares += compare;
        } else {
            incorrectWords++;
            incorrectCompares += compare;
            misspelledFile << word << endl;
        }
    }
    bookFile.close();
    misspelledFile.close();

    Watch.Stop();
    double elapsedTime = Watch.Time();

    // Print results
    cout << "dictionary size: " << dictionary.getSize() << endl;
    cout << "Done checking and these are the results" << endl;
    cout << "finished in time: " << elapsedTime << " seconds" << endl;
    cout << "There are " << correctWords << " words found in the dictionary" << endl;
    cout << correctCompares << " compares. Average: " << (correctWords > 0 ? correctCompares / correctWords : 0) << endl;
    cout << "There are " << incorrectWords << " words NOT found in the dictionary" << endl;
    cout << incorrectCompares << " compares. Average: " << (incorrectWords > 0 ? incorrectCompares / incorrectWords : 0) << endl;
    cout << "There are " << skippedWords << " words not checked." << endl;

    return 0;
}