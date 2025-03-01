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


void searchSecondaryIdentities(person suspects[], int size, int index, int &TOTAL_SHAPESHIFTERS) {
	for (int i = 0; i < size; i++) {
		// Check if current comparison subject is initially innocent
		bool isInnocent = (!suspects[i].isMagic && suspects[i].species != "Kripsan")? false : true;

		// If it isn't we proceed to do a more exhaustive comparison
		if (i != index && !suspects[i].isShapeShifter && !isInnocent) {
			double heightDiff, eyeDepthDiff, eyeDistanceDiff, NFDistanceDiff, NLDistanceDiff;
			int sameCharacteristics = 0;

			heightDiff = abs(suspects[i].height - suspects[index].height);
			eyeDepthDiff = suspects[i].eyeDepth - suspects[index].eyeDepth; // Eye depth difference needs to be a signed value for comparison
			eyeDistanceDiff = abs(suspects[i].eyeDistance - suspects[index].eyeDistance);
			NFDistanceDiff = abs(suspects[i].NFDistance - suspects[index].NFDistance);
			NLDistanceDiff = abs(suspects[i].NLDistance - suspects[index].NLDistance);

			// Original subject and comparison subject must have at least one identical facial feature
			if (eyeDistanceDiff <= 0.05) sameCharacteristics++;
			if (NFDistanceDiff <= 0.05) sameCharacteristics++;
			if (NLDistanceDiff <= 0.05) sameCharacteristics++;
			// If OgSubject and ComSubject have no identical facial features or their height/eye depth gets out of parameters ComSubject is not a secondary identity
			if (heightDiff > 1 || eyeDepthDiff < -0.05 || sameCharacteristics < 1) continue;

			// Marks first OgSubject as shapeshifter, adds to the total shapeshifters and assingns it an index number
			if (!suspects[index].isShapeShifter){
				TOTAL_SHAPESHIFTERS++;
				suspects[index].isShapeShifter = true;
				suspects[index].shapeShifterIndex = TOTAL_SHAPESHIFTERS;
			}
			// Marks ComSubject as secondary identity to prevent the function from adding to the total shapeshifters in next iteration
			suspects[i].isShapeShifter = true;
			suspects[i].shapeShifterIndex = TOTAL_SHAPESHIFTERS;
			
			// Makes secondary identity the new OgSubject for next iterations
			index = i;
		}
	}
}


void searchShapeShifter(person suspects[], int size, int index = 0) {
	// Base case: if all suspects have been checked
	if (index >= size) return;

	// Check if the current suspect is innocent
	bool isInnocent = (!suspects[index].isMagic && suspects[index].species != "Kripsan")? false : true;

	//If the suspect isn't innocent and isn't yet marked as a shapeshifter we proceed to find possible second identities
	if (!isInnocent && !suspects[index].isShapeShifter){
		searchSecondaryIdentities(suspects, size, index, TOTAL_SHAPESHIFTERS);
	}

	// Move to the next suspect
	searchShapeShifter(suspects, size, index + 1);
}


void sortSuspects(person suspects[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (suspects[i].eyeDepth > suspects[j].eyeDepth && suspects[j].shapeShifterIndex != -1) {
				person temp = suspects[i];
				suspects[i] = suspects[j];
				suspects[j] = temp;
			}
		}
	}
}


void printResults(person suspects[], int size, int index = 1){
	if (TOTAL_SHAPESHIFTERS==0){
		cout << "0" << endl;
		return;
	}
	if (index > TOTAL_SHAPESHIFTERS) return;
	if (index == 1) cout << TOTAL_SHAPESHIFTERS << endl;

	int identityCounter = 0;

	for (int i = 0; i < size; i++) {
		if (suspects[i].shapeShifterIndex == index) {
			cout << index << " - " << suspects[i].fullName;
			if (identityCounter == 0) cout << " (O)";
			cout << endl;

			identityCounter++;
		}
	}
	printResults(suspects, size, index + 1);
}


int main() {
	ifstream inputFile = checkFile("../build/dataBase.in");

	// File reading and data storage
	int suspectQuantity = getSuspectQuantity(inputFile);
	person suspects[suspectQuantity];

	getPersonData(suspects, inputFile, suspectQuantity);

	// Search for shapeshifters
	searchShapeShifter(suspects, suspectQuantity);

	//Results display according to document specifications
	sortSuspects(suspects, suspectQuantity);
	printResults(suspects, suspectQuantity);

	inputFile.close();

	return 0;
}
