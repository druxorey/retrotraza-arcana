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
    float NFDistance; // Nose-Forehead distance
    float NLDistance; // Nose-Upperlip (lip) distance
	
	bool isShapeShifter = false;
	int shapeShifterIndex = -1;
};


// START OF DEBUG FUNCTIONS

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


void printShapeShiftersData(person suspects[], int size) {
	for (int i = 0; i < size; i++) {
		cout << suspects[i].fullName << ","
			 << (suspects[i].isShapeShifter ? "Yes" : "No") << ","
			 << suspects[i].shapeShifterIndex << endl;
	}
}

// END OF DEBUG FUNCTIONS


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
	// It has to be the first function to be called to get the quantity correctly
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

	// Iterate from the second line of the file onwards
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


void searchShapeShifter(person suspects[], int size, int index = 0) {
    // Base case: if all suspects have been checked
    if (index >= size) return;

	// Check if the current suspect is innocent
	bool isInnocent = (!suspects[index].isMagic && suspects[index].species != "Kripsan")? false : true;

    // Check if the current suspect can be an original shapeshifter
    if (!isInnocent) {
		double heightDiff, eyeDepthDiff, eyeDistanceDiff, NFDistanceDiff, NLDistanceDiff;

		printf("\e[0;33mDEBUG: Checking suspect %d: %s\n\e[0m", index, suspects[index].fullName.c_str());

        TOTAL_SHAPESHIFTERS++;
        suspects[index].isShapeShifter = true;
        suspects[index].shapeShifterIndex = TOTAL_SHAPESHIFTERS;

        // Try to find other forms of the shapeshifter
        for (int i = 0; i < size; i++) {
            if (i != index && !suspects[i].isShapeShifter && !isInnocent) {

				heightDiff = abs(suspects[i].height - suspects[index].height);
				eyeDepthDiff = abs(suspects[i].eyeDepth - suspects[index].eyeDepth);
				eyeDistanceDiff = abs(suspects[i].eyeDistance - suspects[index].eyeDistance);
				NFDistanceDiff = abs(suspects[i].NFDistance - suspects[index].NFDistance);
				NLDistanceDiff = abs(suspects[i].NLDistance - suspects[index].NLDistance);

                if (heightDiff <= 1 &&
					eyeDistanceDiff > 0.05 &&
					eyeDepthDiff <= 0.05 &&
					NFDistanceDiff <= 0.05 &&
					NFDistanceDiff <= 0.05) {

                    suspects[i].isShapeShifter = true;
                    TOTAL_SHAPESHIFTERS++;

                }
            }
        }
    }
	
    // Move to the next suspect
    searchShapeShifter(suspects, size, index + 1);
}


int main() {
	ifstream inputFile = checkFile("dataBase.in");

	// File reading and data storage
    int suspectQuantity = getSuspectQuantity(inputFile);
    person suspects[suspectQuantity];

	getPersonData(suspects, inputFile, suspectQuantity);

	// Search for shapeshifters
	searchShapeShifter(suspects, suspectQuantity);

	// Data display
	printf("\n\e[0;32mSuspect data:\n\e[0m");
    printPersonData(suspects, suspectQuantity);

	printf("\n\e[0;32mShapeshifter data:\n\e[0m");
	printShapeShiftersData(suspects, suspectQuantity);

	printf("\n\e[0;32mTotal shapeshifters: %d\n\e[0m", TOTAL_SHAPESHIFTERS);

    inputFile.close();

	return 0;
}
