/*
	I pledge my honor that I have abided by the Stevens Honor System.
	Author: Ryan Perretta
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> dict;
int letter_vals[] = { 2, 3, 5, 7, 11 , 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 71, 73, 79, 83, 89, 97, 101, 103 };

//Calculates the unique product for a string
int get_product(string s) {
	int x = 1;

	for (char c : s) {
		//Skips word if non-ascii character is read
		if (!isascii(c)) {
			x = 1;
			break;
		}
		//Computes unique product of word (13 is the ascii of a 'return' character)
		if (c != 13) {
			x *= letter_vals[tolower(c) - 97];
		}
	}

	return x;
}

vector<vector<string>> find_anagrams() {
	//vector to keep track of groups of vectors (vector to be returned)
	vector<vector<string>> groups;
	//keeps track of unique products so that we don't repeat the process for a
	//word already in an anagram group
	vector<int> seen_anagrams;
	//is the first iteration of a loop?
	bool isFirst = true;

	for (int i = 0; i < (int) dict.size(); ++i) {
		int product;
		vector<string> curr_group;
		//adds the first word to a new group of anagrams
		curr_group.push_back(dict[i]);
		product = get_product(dict[i]);
		if (product == 1) {
			continue;
		}
		//does not test for seen anagram on first run
		if (!isFirst) {
			int temp = 0;
			for (auto& x : seen_anagrams) {
				if (x == product) {
					temp++;
					break;
				}
			}
			if (temp > 0) {
				continue;
			}
		}
		seen_anagrams.push_back(product);
		//finds the rest of the anagrams in the dictionary
		for (int j = i + 1; j < (int)dict.size(); j++) {
			if (get_product(dict[j]) == product) {
				curr_group.push_back(dict[j]);
			}
		}
		//pushes the current group onto the final vector unconditionally on the first iteration
		if (isFirst) {
			groups.push_back(curr_group);
		}
		else {
			//clears final vector and adds current group of vectors if current group
			//has more anagrams
			if ((int) groups.front().size() < (int) curr_group.size()) {
				groups.clear();
				groups.push_back(curr_group);
			}
			//Adds current group to final vector if its size matchs the first in final vector
			else if ((int) groups.front().size() == (int) curr_group.size()) {
				groups.push_back(curr_group);
			}
		}
		isFirst = false;
	}

	return groups;
}

/*
	Takes in variable file name.
	Reads file into the global vector dict.
	Returns TRUE if file does not exist.
*/
bool readFileToVector(string fileName) {
	ifstream source;
	source.open(fileName);
	string line;
	if (source.is_open()) {
		while (getline(source, line)) {
			dict.push_back(line);
		}
	}
	else {
		return true;
	}
	return false;
}

//sorts the vector of vectors by reordering the groups of anagrams (Essentially a selection sort)
vector<vector<string>> sort_vector_of_vectors(vector<vector<string>> unsorted) {
	for (int i = 0; i < (int)unsorted.size(); ++i) {
		//index of the minimum vector
		int min_vector = i;
		for (int j = i + 1; j < (int)unsorted.size(); ++j) {
			int result = unsorted[min_vector].front().compare(unsorted[j].front());
			if (result > 0) {
				min_vector = j;
			}
		}
		//swap
		vector<string> temp = unsorted[min_vector];
		unsorted[min_vector] = unsorted[i];
		unsorted[i] = temp;
	}

	return unsorted;
}

//sorts each group of anagrams in the answer	(Essentially a selection sort)
vector<string> sort_vector(vector<string> unsorted) {
	for (int i = 0; i < (int)unsorted.size(); ++i) {
		int min_string = i;
		for (int j = i + 1; j < (int)unsorted.size(); ++j) {
			if (unsorted[min_string].compare(unsorted[j]) > 0) {
				min_string = j;
			}
		}
		//swap
		string temp = unsorted[min_string];
		unsorted[min_string] = unsorted[i];
		unsorted[i] = temp;
	}

	return unsorted;
}

int main(int argc, char** argv) {
	string fileName;
	//Makes sure the user entered EXACTLY ONE dictionary file
	if (argc != 2) {
		cerr << "Usage: ./anagramfinder <dictionary file>" << endl;
		return 1;
	}
	else {
		fileName = argv[1];
	}

	//Reads file to vector and outputs error if file can't be opened
	if (readFileToVector(fileName)) {
		cerr << "Error: File '"<< fileName <<"' not found." << endl;
		return 1;
	}

	int max_anagrams = 0;
	vector<vector<string>> answers;
	//will run find_anagrams() as long as the file is not empty
	if (!dict.empty()) {
		answers = find_anagrams();
		if (!answers.empty()) {
			max_anagrams = (int)answers.front().size();
		}
	}
	//If file is empty or no anagrams exist
	if (max_anagrams <= 1 or answers.empty()) {
		cout << "No anagrams found." << endl;
	}
	//Outputs final answer
	else {
		cout << "Max anagrams: " << max_anagrams << endl;
		int v_size = (int)answers.size()-1;
		for (int i = 0; i < (int)answers.size(); ++i) {
			answers[i] = sort_vector(answers[i]);
		}
		answers = sort_vector_of_vectors(answers);
		for (vector<string> vect : answers) {
			for (auto& x : vect) {
				cout << x << endl;
			}
			if (v_size != 0) {
				cout << endl;
			}
			--v_size;
		}
	}

	return 0;
}