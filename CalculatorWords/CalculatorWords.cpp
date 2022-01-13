
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <iomanip>

using namespace std;

// A set of letters that can be typed on a calculator
// This set is not necessarily comprehensive
// While I have all the letters as key in the map, this is a more convenient method
const char letters[] = {'h', 'e', 'l', 'o', 'b', 's', 'i', 'g'};

map<char, int> number_associated{ {'h', 4}, {'e', 3}, {'l', 1}, {'o', 0}, {'b', 8}, { 's', 5 }, { 'i', 1 }, {'g', 6} } ;

// Input: a string to turn into a series of calculator-compatible numbers represented as a string
// Output: a calculator-compatible number representing the input string
string word_to_number(string word) {
	string output;
	// 
	for (int i = 0; i < word.size(); i++) {
		auto found = number_associated.find(word[i]);
		if (found == number_associated.end()) {
			return "An invalid character was found; could not turn into calculator code\n";
		}
		// This is maybe a stupid way of turning an integer into a string as opposed to just storing strings in the mapping but whatever
		output.insert(0,string(1,"0123456789"[found->second]));
	}
	return output;
}

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
		cout << *i << setw(20) << word_to_number(*i) << '\n';
		if (canWrite)
			calculatorwords << *i << setw(20) << word_to_number(*i) << '\n';
	}

	return 0;
}
