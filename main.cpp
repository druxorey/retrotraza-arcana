#include <iostream>
#include <fstream> 

using namespace std;

int TOTAL_SHAPESHIFTERS = 0;

struct person {
    string fullName;
    string species;
    float height;
    bool isMagic;
    float eyeDepth;
    float eyeDistance;
    float NFDistance; //nose-forehead distance
    float NLDistance; //nose-upperlip (lip) distance
	
	bool isShapeShifter = false;
	bool isOriginal = false;
};


// START DEBUG FUNCTIONS

void printPersonData(person suspects[], int size) {
    for (int i = 0; i < size; i++) {
        cout << suspects[i].fullName << ","
             << suspects[i].species << ","
             << suspects[i].height << ","
             << (suspects[i].isMagic ? "Yes" : "No") << ","
             << suspects[i].eyeDepth << ","
             << suspects[i].eyeDistance << ","
             << suspects[i].NFDistance << ","
             << suspects[i].NLDistance << endl;
    }
}

// END DEBUG FUNCTIONS


ifstream checkFile(string fileName) {
	ifstream file(fileName);

	if (!file) {
		cerr << "\e[0;31mError: The file could not be opened\e[0m" << '\n';
		exit(1);
	}

	return file;
}


int getSuspectQuantity(ifstream &file) {
	string suspectLine = "";
	getline(file, suspectLine);
	int suspectQuantity = stoi(suspectLine);
	if (suspectQuantity < 1 || suspectQuantity > 1000) {
		cerr << "\e[0;31mError: The number of suspects is out of range\e[0m" << '\n';
		exit(1);
	}
	return suspectQuantity;
}


void getPersonData(person suspects[], ifstream &file, int size) {
	string firstName, lastName, magic;
	printf("\e[0;33mDEBUG: Suspect quantity: %d\n\e[0m", size);

    for (int i = 0; i < size; i++) {
		file >> firstName;
		file >> lastName;
		suspects[i].fullName = firstName + " " + lastName;
		file >> suspects[i].species;
		file >> suspects[i].height;
		file >> magic;
		suspects[i].isMagic = (magic == "No") ? false : true;
		file >> suspects[i].eyeDepth;
		file >> suspects[i].eyeDistance;
		file >> suspects[i].NFDistance;
		file >> suspects[i].NLDistance;
	}
}


int main() {
	ifstream inputFile = checkFile("dataBase.in");

    int suspectQuantity = getSuspectQuantity(inputFile);
    person suspects[suspectQuantity];
	getPersonData(suspects, inputFile, suspectQuantity);

    printPersonData(suspects, suspectQuantity);
	printf("\e[0;32mTotal shapeshifters: %d\n\e[0m", TOTAL_SHAPESHIFTERS);

    inputFile.close();

	return 0;
}
