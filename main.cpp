#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

struct person {
    string fullName;
    string species;
    float height;
    bool isMagic;
    float eyeDepth;
    float eyeDistance;
    float NFDistance; //nose-forehead distance
    float NLDistance; //nose-upperlip (lip) distance
};


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


int main() {

	ifstream inputFile = checkFile("dataBase.in");
    int suspectQuantity = getSuspectQuantity(inputFile);

    person suspects[suspectQuantity];
    string firstName, lastName, magic;

	printf("\e[0;33mDEBUG: Suspect quantity: %d\n\e[0m", suspectQuantity);

	string line;
	while (getline(inputFile, line)) {
		printf("\e[0;33mDEBUG: %s\n\e[0m", line.c_str());
	}

    for (int i = 0; i < suspectQuantity; i++) {
        inputFile >> firstName;
        inputFile >> lastName;
        suspects[i].fullName = firstName + " " + lastName;
        inputFile >> suspects[i].species;
        inputFile >> suspects[i].height;
        inputFile >> magic;
        if (magic == "No") suspects[i].isMagic = false;
        else suspects[i].isMagic = true;
        inputFile >> suspects[i].eyeDepth;
        inputFile >> suspects[i].eyeDistance;
        inputFile >> suspects[i].NFDistance;
        inputFile >> suspects[i].NLDistance;
    }

    inputFile.close();

	return 0;
}
