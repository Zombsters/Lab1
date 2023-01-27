#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void findFirstLetter(char** newspaper[],string wordToFind, int& row, int& col); //nested loop

int main() {
	int numRows, numCols;
	
	ifstream fin("input1.txt");
	fin >> numRows; fin >> numCols;

	//create array to hold characters
	char** newspaper = new char*[numRows]; 
	
	
	//read in values and load array
	for (int i = 0;i < numRows * numCols; i++) {
		newspaper[i] = new char[numCols]; // a row of new columns
		//cout << newspaper[i] << " " << endl; // addresses
	}

	for (int row = 0; row < numRows;row++) {
		for (int col = 0; col < numCols; col++) {
			fin >> newspaper[row][col]; // because both are pointers --> we allow [][]
		}
	}

	for (int row = 0; row < numRows;row++) {
		for (int col = 0; col < numCols; col++) {
			cout << newspaper[row][col] << " "; //display
		}
		cout << endl;
	}
	
	//read in apple
	string wordToFind; fin.ignore(); getline(fin, wordToFind); cout << wordToFind;

	//now... solve problem! //create funciton to find first letter->array auto passed by reference -- boolean to determine if found
	findFirstLetter(newspaper,wordToFind, numRows,numCols);


	fin.close();
	return 0;
}

void findFirstLetter(char** newspaper, string wordToFind, int& row, int& col){
	for (int i = 0; i < row; i++) {
		cout << newspaper[row][col] << " "; //display
	}
	return;
}

