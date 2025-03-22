#include <iostream>
#include <fstream>
#include <string>
#include "indexedDictionary.h"
#include "timer.h"

using namespace std;

// Function to clean and sanitize words
// This function removes any non-alphabetic, non-numeric characters except for apostrophes
// It also converts all characters to lowercase
string cleanWord(string word) {
    string cleaned = "";
    for (char c : word) {
        // Check if character is alphabetic, numeric, or an apostrophe
        if (isalpha(c) || isdigit(c) || c == '\'') {
            // Convert character to lowercase and add to cleaned string
            cleaned += tolower(c);
        }
    }
    return cleaned; // Return the cleaned word
}

int main() {
    IndexedDictionary dictionary;  // Create an instance of IndexedDictionary to store dictionary words
    // Debugging: Print the initial state of the dictionary
    ifstream dictFile("dict.txt"); // Open the dictionary file for reading
    ifstream bookFile("book.txt"); // Open the book file for reading

    // Check if dictionary file opened successfully
    if (!dictFile.is_open()) {
        cerr << "Error: Unable to open dictionary file." << endl;
        return 1; // Return error code 1 if dictionary file cannot be opened
    }

    // Check if book file opened successfully
    if (!bookFile.is_open()) {
        cerr << "Error: Unable to open book file." << endl;
        return 1; // Return error code 1 if book file cannot be opened
    }

    string word;
    long long int compare = 0; // Variable to store number of comparisons

    // Read and insert dictionary words
    while (dictFile >> word) {
        word = cleanWord(word); // Clean the word
        if (!word.empty()) { // Check if cleaned word is not empty
            dictionary.insert(word); // Insert word into dictionary
        }
    }
    dictFile.close(); // Close the dictionary file

    Timer Watch; // Create an instance of Timer to measure elapsed time
    Watch.Start(); // Start the timer

    int correctWords = 0; // Counter for correctly spelled words
    int incorrectWords = 0; // Counter for incorrectly spelled words
    int skippedWords = 0; // Counter for skipped words
    long long int correctCompares = 0; // Total comparisons for correct words
    long long int incorrectCompares = 0; // Total comparisons for incorrect words
    ofstream misspelledFile("misspelled.txt"); // Open file to write misspelled words
 //   ofstream notCheckedFile("notchecked.txt"); // Debugging output for not checked words

    // Read and check book words
    while (bookFile >> word) {
        word = cleanWord(word); // Clean the word
        if (word.empty() || !isalpha(word[0])) {
            if (!word.empty()) { // Only count non-empty words as not checked
                skippedWords++;
                //notCheckedFile << word << endl; // Debugging output for not checked words
            }
            continue;
        }
        // Check if word is in dictionary
        if (dictionary.find(word, compare)) {
            correctWords++; // Increment correct word counter
            correctCompares += compare; // Add comparisons to correct compares
        } else {
            incorrectWords++; // Increment incorrect word counter
            incorrectCompares += compare; // Add comparisons to incorrect compares
            misspelledFile << word << endl; // Write misspelled word to file
        }
        compare = 0; // Reset comparison counter for next word
    }
        // Debugging: Print the initial state of the dictionary


    bookFile.close(); // Close the book file
    misspelledFile.close(); // Close the misspelled words file

    cout << "Initial state of the dictionary:" << endl;
    dictionary.print();
    cout << endl;

    Watch.Stop(); // Stop the timer

    double elapsedTime = Watch.Time(); // Get the elapsed time
    int totalWords = correctWords + incorrectWords; // Calculate total words checked

    // Print the results
    cout << "dictionary size: " << dictionary.getSize() << endl;
    cout << "Done checking and these are the results" << endl;
    cout << "finished in time: " << elapsedTime << endl;
    cout << "There are " << correctWords << " words found in the dictionary" << endl;
    cout << correctCompares << " compares. Average: " << (correctWords > 0 ? correctCompares / correctWords : 0) << endl;
    cout << "There are " << incorrectWords << " words NOT found in the dictionary" << endl;
    cout << incorrectCompares << " compares. Average: " << (incorrectWords > 0 ? incorrectCompares / incorrectWords : 0) << endl;
    cout << "There are " << skippedWords << " words not checked." << endl;

    return 0; // Return success code
}
