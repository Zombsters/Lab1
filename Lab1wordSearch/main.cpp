#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void findFirstLetter(char** newspaper, string wordToFind, int numRows, int numCols); //nested loop

void findNextLetter(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt,int& colFoundAt, int& index);

bool checkRight(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index);
bool checkLeft(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index);
bool checkUp(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index);
bool checkDown(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index);

int main() {
	int numRows, numCols;

	ifstream fin("input1.txt");
	fin >> numRows; fin >> numCols;

	//create array to hold characters
	char** newspaper = new char* [numRows];

	//create 2d dynamic array
	for (int i = 0;i < numRows; i++) {
		newspaper[i] = new char[numCols]; // every row points to a new char of columns
	}
	//load in values
	for (int row = 0; row < numRows;row++) {
		for (int col = 0; col < numCols; col++) {
			fin >> newspaper[row][col]; // because both are pointers --> we allow [][]
		}
	}

	//display values
	for (int row = 0; row < numRows;row++) {
		for (int col = 0; col < numCols; col++) {
			cout << newspaper[row][col] << " "; 
		}
		cout << endl;
	}
	//read in word
	string wordToFind; fin.ignore(); getline(fin, wordToFind); cout << wordToFind << endl;

	//now... solve problem! //create funciton to find first letter->array auto passed by reference -- boolean to determine if found...

	//findFirstLetter
	findFirstLetter(newspaper, wordToFind, numRows, numCols);
	

	fin.close();


	return 0;
}

void findFirstLetter(char** newspaper, string wordToFind, int numRows, int numCols) {
	int index = 0;
	char letterToFind = wordToFind.at(index);
	int rowFoundAt = 0; int colFoundAt = 0;

	for (int row = 0; row < numRows;row++) {
		for (int col = 0; col < numCols; col++) {

			if (letterToFind == newspaper[row][col]) {
				cout << "Found First Letter " << letterToFind << " at row " << row << " and column " << col << endl;
				letterToFind = wordToFind.at(++index);
				rowFoundAt = row; colFoundAt = col;
				break;
			}

		}
	}
	cout << "Next Letter to find is " << letterToFind << endl;

	findNextLetter(newspaper, wordToFind, numRows, numCols, letterToFind,rowFoundAt,colFoundAt, index);
}

void findNextLetter(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index)
{

	cout << "In findNextLetter Function... " << endl; 
	bool found = false; // letter not found yet...

	//handle left column
	if (colFoundAt == 0) {
		if (rowFoundAt != 0) { //left but not top
			found = checkUp(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (rowFoundAt != (numRows - 1) && found == false) { //left but not bottom
			found = checkDown(newspaper, wordToFind,numRows, numCols, letterToFind, rowFoundAt, colFoundAt,index);
		}
		if (found == false) {
			found = checkRight(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index); //left side can always check right
		}
	}
	
	//handle right column
	if (colFoundAt == (numCols - 1) && found == false) {
		if (rowFoundAt != 0 && found == false) { //right but not top
			found = checkUp(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (rowFoundAt != (numRows - 1) && found == false) { //right but not bottom
			found = checkDown(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (found == false) {
			found = checkLeft(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index); //right side can always check left
		}
	}
	
	//handle top row
	if (rowFoundAt == 0 && found == false) {
		if (colFoundAt != 0 && found == false) { //top but not left
			found = checkLeft(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (colFoundAt != (numCols - 1) && found == false) { //top but not right
			found = checkRight(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (found == false) {
			found = checkDown(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index); //top side can always check down
		}
	}

	//handle bottom row
	if (rowFoundAt == (numRows - 1) && found == false) {
		if (colFoundAt != 0 && found == false) { //bottom but not left
			found = checkLeft(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (colFoundAt != (numCols - 1) && found == false) { //bottom but not right
			found = checkRight(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (found == false) {
			found = checkUp(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index); //bottom side can always check up
		}
	}

	else {
		found == checkLeft(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		if (found == false) {
			found == checkRight(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (found == false) {
			found == checkUp(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		}
		if (found == false){
			found == checkDown(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
			}
	}

	if (letterToFind == wordToFind.at(wordToFind.size() - 1)) {
		cout << "Found " << wordToFind << "! Last Letter was " << letterToFind << " at row " << rowFoundAt << " and column " << colFoundAt << endl;
		return;
	}

	cout << "Unable to find word... " << " last letter found from " << wordToFind << " was " << letterToFind << " at row " << rowFoundAt << " and column " << colFoundAt << endl;
 }



bool checkRight(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index) {
	cout << "Checking right...  " << endl;
	

	if (letterToFind == newspaper[rowFoundAt][colFoundAt + 1])
	{
		colFoundAt++; 
		cout << "Found " << letterToFind << " at row " << rowFoundAt << " and col " << colFoundAt << endl;
		if (letterToFind != wordToFind.at(wordToFind.size() - 1) ) {
			letterToFind = wordToFind.at(++index);
		}
		findNextLetter(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		return true;
	}

	return false;
}

bool checkLeft(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index) {
	cout << "Checking left... " << endl;
	
	if (letterToFind == newspaper[rowFoundAt][colFoundAt - 1])
	{
		colFoundAt--; 
		cout << "Found " << letterToFind << " at row " << rowFoundAt << " and col " << colFoundAt << endl;

		if (letterToFind != wordToFind.at(wordToFind.size() - 1) ) {
			letterToFind = wordToFind.at(++index);
		}
		findNextLetter(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		return true;
	}

	return false;
}

bool checkUp(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index) {
	cout << "Checking up... " << endl;
	if (letterToFind == newspaper[rowFoundAt + 1][colFoundAt])
	{
		rowFoundAt++;
		cout << "Found " << letterToFind << " at row " << rowFoundAt << " and col " << colFoundAt << endl;

		if (letterToFind != wordToFind.at(wordToFind.size()) - 1) {
			letterToFind = wordToFind.at(++index);
		}
		findNextLetter(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		return true;
	}

	return false;
}

bool checkDown(char** newspaper, string wordToFind, int numRows, int numCols, char& letterToFind, int& rowFoundAt, int& colFoundAt, int& index) {
	cout << "Checking down... " << endl;
	if (letterToFind == newspaper[rowFoundAt - 1][colFoundAt])
	{
		rowFoundAt--;
		cout << "Found " << letterToFind << " at row " << rowFoundAt << " and col " << colFoundAt << endl;
		
		if (letterToFind != wordToFind.at(wordToFind.size() - 1)) {
			letterToFind = wordToFind.at(++index);
		}
		findNextLetter(newspaper, wordToFind, numRows, numCols, letterToFind, rowFoundAt, colFoundAt, index);
		return true;
	}

	return false;
}
