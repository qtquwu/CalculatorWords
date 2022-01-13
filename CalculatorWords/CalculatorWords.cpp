
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

// A set of letters that can be typed on a calculator
// This set is not necessarily comprehensive
const char letters[] = {'h', 'e', 'l', 'o', 'b', 's', 'i', 'g'};

using namespace std;

int main()
{
	// Read a dictionary of words and store it as a vector of strings
	ifstream dict;
	dict.open("words.txt", ios::in);
	vector<string> words;
	string currentWord;
	bool dictcomplete = false;
	while (getline(dict, currentWord)) {
		words.push_back(currentWord);
	}
	dict.close();
	// Sift through the list and pick words that can be only consist of valid characters

	vector<string> validWords;
	bool word_valid, letter_valid;
	for (auto i = words.begin(); i != words.end(); i++) { // i points to a word in words
		word_valid = true;
		for (int j = 0; j < i->size(); j++) { // j is a location in the word pointed to by i
			letter_valid = false;
			for (int k = 0; k < sizeof(letters) / sizeof(char); k++) { // k is a valid letter
				if (i->c_str()[j] == letters[k]) {
					letter_valid = true;
				}
			}
			if (!letter_valid) {
				word_valid = false;
			}
		}
		if (word_valid) {
			validWords.push_back(*i);
		}
	}

	// Display valid words and write them to a file - calculatorwords.txt
	ofstream calculatorwords;
	bool canWrite = true;
	calculatorwords.open("calculatorwords.txt", ios::out);

	if (!calculatorwords.is_open()) {
		cerr << "An error occurred writing the file. Words will be outputted but not saved to a file.\n";
		canWrite = false;
	}
	for (auto i = validWords.begin(); i != validWords.end(); i++) {
		cout << *i << '\n';
		if (canWrite)
			calculatorwords << *i << '\n';
	}

	return 0;
}
