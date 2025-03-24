#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "timer.h"
#include "RedBlackTree.h"  // Include the RedBlackTree header

using namespace std;

// Constants for maximum word length and alphabet size
const int MAX_WORD_LENGTH = 25;
const int ALPHABET_SIZE = 26;

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

// Function to get the index for the first character
int getCharIndex(char c) {
    return tolower(c) - 'a';
}

// Function to get the total size of the dictionary
int getTotalSize(const vector<vector<RedBlackTree<string>>> &dictionary) {
    int totalSize = 0;
    for (const auto &treesByLength : dictionary) {
        for (const auto &tree : treesByLength) {
            totalSize += tree.getSize();
        }
    }
    return totalSize;
}

int main() {
    // 2D array of Red-Black Trees
    vector<vector<RedBlackTree<string>>> dictionary(ALPHABET_SIZE, vector<RedBlackTree<string>>(MAX_WORD_LENGTH + 1));
    
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
        if (!word.empty() && word.length() <= MAX_WORD_LENGTH && isalpha(word[0])) {
            int charIndex = getCharIndex(word[0]);
            int lengthIndex = word.length();
            dictionary[charIndex][lengthIndex].insert(word);
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
        
        if (word.length() > MAX_WORD_LENGTH) {
            incorrectWords++;
            incorrectCompares += compare;
            misspelledFile << word << endl;
            continue;
        }

        int charIndex = getCharIndex(word[0]);
        int lengthIndex = word.length();

        if (dictionary[charIndex][lengthIndex].find(word, compare) != nullptr) {
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
    cout << "dictionary size: " << getTotalSize(dictionary) << endl;
    cout << "Done checking and these are the results" << endl;
    cout << "finished in time: " << elapsedTime << " seconds" << endl;
    cout << "There are " << correctWords << " words found in the dictionary" << endl;
    cout << correctCompares << " compares. Average: " << (correctWords > 0 ? correctCompares / correctWords : 0) << endl;
    cout << "There are " << incorrectWords << " words NOT found in the dictionary" << endl;
    cout << incorrectCompares << " compares. Average: " << (incorrectWords > 0 ? incorrectCompares / incorrectWords : 0) << endl;
    cout << "There are " << skippedWords << " words not checked." << endl;

    return 0;
}