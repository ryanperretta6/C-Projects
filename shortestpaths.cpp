/*
	Best darn header on this side of the Mississippi

	Authors:	 Ryan Perretta & Zachary Costanzo
	Pledge:	 	 I pledge my honor that I have abided by the Stevens Honor System.
	Date:		 December 5, 2019
	Description: Implementation of Floyd's All-Pairs Shortest-Paths Algorithm
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<char> alphabet = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
vector<vector<long>> distanceMatrix;

//Returns the  number of digits in a number
int len(long num) {
	int count = 0;
	if (num <= 0) {
		return 1;
	}
	while (num != 0) {
		num /= 10;
		count++;
	}
	return count;
}

void displayMatrix(vector<vector<long>> v, const string label, const bool use_letters) {
	int numVertices = (int)v.size();
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			long cell = v[i][j];
			if (cell > max_val) {
				max_val = v[i][j];
			}
		}
	}//MAX VALUE FOUND
	long max_cell_width = use_letters ? len(max_val) :
		len(max(static_cast<long>(numVertices), max_val));
	cout << ' ';
	for (int j = 0; j < numVertices; j++) {
		cout << setw(max_cell_width + 1) << alphabet[j];
	}
	cout << endl;
	for (int i = 0; i < numVertices; i++) {
		cout << alphabet[i];
		for (int j = 0; j < numVertices; j++) {
			cout << " " << setw(max_cell_width);
			if (v[i][j] == -1 || v[i][j] == -2) {
				cout << "-";
			}
			else if (use_letters) {
				cout << static_cast<char>(v[i][j] + 'A');
			}
			else {
				cout << v[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

//Initializes the distance matrix with 0's along the major diagonal and -1's everywhere else
void buildDistanceMatrix(int numVertices) {
	for (int i = 0; i < numVertices; i++) {
		vector<long> tempVect;
		for (int j = 0; j < numVertices; j++) {
			if (i == j) {
				tempVect.push_back(0);
			}
			else {
				tempVect.push_back(-1);
			}
		}
		distanceMatrix.push_back(tempVect);
	}
}

int readFile(string fileName) {
	ifstream source;
	source.open(fileName);
	string line;
	//return character in the text file
	char enter = 13;
	int numVertices, lineNum = 1;
	if (source.is_open()) {
		while (getline(source, line)) {
			stringstream ss(line);
			//Gets the number of vertices from the first line of the file
			if (lineNum == 1) {
				//Checks that the number of vertices provided is valid
				if (!(ss >> numVertices) || numVertices < 1 || numVertices > 26) {
					line = line.substr(0, line.find(enter));
					cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
					return 2;
				}
				buildDistanceMatrix(numVertices);
			}
			else {
				//Removes the return character from the end of the string
				line = line.substr(0, line.find(enter));
				string untouched = line;
				char from, to;
				long dist;
				string temp = line.substr(0, line.find(' '));
				//tempCount is used to check size of each vertex given
				int componentCount = 0, tempCount = 0;
				for (char c : temp) {
					//Checks if vertex is in the valid range
					if ((c - 65) > numVertices - 1) {
						tempCount = -1;
						break;
					}
					from = c;
					tempCount++;
				}
				//Will output error if the vertex is not in the valid range or if there are too many characters
				if (tempCount != 1) {
					cerr << "Error: Starting vertex '" << temp << "' on line " << lineNum
						 << " is not among valid values " << alphabet[0] << "-" << alphabet[numVertices - 1] << "." << endl;
					return 2;
				}
				//Starting Vertex acquired
				componentCount++;

				//Erases the Starting Vertex from the line
				line = line.erase(0, line.find(' ') + 1);
				//Gets the next string up to the next space
				temp = line.substr(0, line.find(' '));

				tempCount = 0;
				for (char c : temp) {
					//Checks if vertex is in the valid range
					if ((c - 65) > numVertices - 1 || c < 65) {
						tempCount = -1;
						break;
					}
					to = c;
					tempCount++;
				}
				//Will output error if the vertex is not in the valid range or if there are too many characters
				if (tempCount != 1) {
					cerr << "Error: Ending vertex '" << temp << "' on line " << lineNum
						 << " is not among valid values " << alphabet[0] << "-" << alphabet[numVertices - 1] << "." << endl;
					return 2;
				}
				//Ending Vertex acquired
				componentCount++;

				//Erases the Ending Vertex from the line
				line = line.erase(0, temp.length() + 1);
				temp = line.substr(0, line.find(' '));

				if (line.length() != 0) {
					istringstream iss(line);
					if (!(iss >> dist) || dist < 1) {
						cerr << "Error: Invalid edge weight '" << temp << "' on line " << lineNum << "." << endl;
						return 2;
					}
				}
				else {
					cerr << "Error: Invalid edge data '" << untouched << "' on line " << lineNum << "." << endl;
					return 2;
				}
				//Distance acquired
				componentCount++;

				line = line.erase(0, line.find(temp) + temp.length());
				
				if (componentCount != 3 || line.length() != 0) {
					cerr << "Error: Invalid edge data '" << untouched << "' on line " << lineNum << "." << endl;
					return 2;
				}
				//Adds to the distance matrix
				distanceMatrix[from - 65][to - 65] = dist;

			}
			lineNum++;
		}
	}
	else {
		//returns 1 for a file not open error
		return 1;
	}
	source.close();
	return 0;
}

//Returns the initializes intermediate matrix with '-' in every spot
vector<vector<long>> buildIntermediate() {
	vector<vector<long>> vOfV;
	int numVertices = (int)distanceMatrix.size();
	for (int i = 0; i < numVertices; i++) {
		vector<long> v;
		for (int j = 0; j < numVertices; j++) {
			if (i == j) {
				v.push_back(-2);
			}
			else {
				v.push_back(-1);
			}
		}
		vOfV.push_back(v);
	}

	return vOfV;
}

//Implements Floyd's Algorithm for the all-pairs shortest-paths
vector<vector<long>> floyds() {
	vector<vector<long>> intermediate = buildIntermediate(), copy = distanceMatrix;
	int numVertices = (int)distanceMatrix.size();
	for (int k = 0; k < numVertices; k++) {
		for (int i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
				long x = distanceMatrix[i][j], y = distanceMatrix[i][k],
					z = distanceMatrix[k][j];
				//For when current spot is infinite and both others are not
				if (x == -1 && (y != -1 && z != -1)) {
					distanceMatrix[i][j] = y + z;
					intermediate[i][j] = k;
				}
				//For when both will be infinite
				else if (y == -1 || z == -1) {
					continue;
				}
				else {
					distanceMatrix[i][j] = min(x, y + z);
					//Adds the intermediate vertex if the edge is changed
					if (distanceMatrix[i][j] != x) {
						intermediate[i][j] = k;
					}
				}
				if (distanceMatrix[i][j] == copy[i][j]) {
					intermediate[i][j] = -2;
				}
			}
		}
	}
	return intermediate;
}

void displayIntermediates(vector<vector<long>> intermediate, int i, int j) {
	if (intermediate[i][j] != -2) {
		displayIntermediates(intermediate, i, intermediate[i][j]);
		cout << static_cast<char>(intermediate[i][j] + 'A') << " -> ";
		displayIntermediates(intermediate, intermediate[i][j], j);
	}
}

//Displays all of the shortest paths from one vertex to another
void displayPaths(vector<vector<long>> intermediate, int i, int j) {

	if (intermediate[i][j] == -2) {
		cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A');
		return;
	}
	else {
		cout << static_cast<char>(i + 'A') << " -> ";
		displayIntermediates(intermediate, i, j);
		cout << static_cast<char>(j + 'A');
	}

}

void displayPathsBegin(vector<vector<long>> intermediate, int i, int j) {

	cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A')
		<< ", distance: ";
	if (intermediate[i][j] == -1) {
		cout << "infinity, path: none";
	}
	else {
		cout << distanceMatrix[i][j] << ", path: ";
		if (i == j) {
			cout << static_cast<char>(i + 'A');
		}
		else {
			displayPaths(intermediate, i, j);
		}
	}

	cout << endl;
}

int main(int argc, char* argv[]) {
	//Throws Error if too few or too many arguments are given
	if (argc != 2) {
		cerr << "Usage: ./shortestpaths <filename>" << endl;
		return 1;
	}
	string fileName = argv[1];
	int test = readFile(fileName);
	//Error due to the file not opening
	if (test == 1) {
		cerr << "Error: Cannot open file '" << fileName << "'." << endl;
		return 1;
	}
	//Error due to anything else encountered in the readFile
	else if (test == 2) {
		return 1;
	}

	displayMatrix(distanceMatrix, "Distance matrix:", false);

	vector<vector<long>> intermediate = floyds();

	displayMatrix(distanceMatrix, "Path lengths:", false);
	displayMatrix(intermediate, "Intermediate vertices:", true);

	for (int i = 0; i < (int)intermediate.size(); i++) {
		for(int j = 0; j < (int)intermediate.size(); j++){
			displayPathsBegin(intermediate, i, j);
		}
	}

	return 0;
}