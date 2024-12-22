#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

struct person {
    string name;
    string species;
    float height;
    bool hasMagic;
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

	ifstream suspectsInput = checkFile("dataBase.in");
    int suspectQuantity = getSuspectQuantity(suspectsInput);

    person suspects[suspectQuantity];
    string name, lastname, magic;

	printf("\e[0;33mDEBUG: Suspect quantity: %d\n\e[0m", suspectQuantity);

	string line;
	while (getline(suspectsInput, line)) {
		printf("\e[0;33mDEBUG: %s\n\e[0m", line.c_str());
	}

    for (int i = 0; i < suspectQuantity; i++) {
        suspectsInput >> name;
        suspectsInput >> lastname;
        suspects[i].name = name + " " + lastname;
        suspectsInput >> suspects[i].species;
        suspectsInput >> suspects[i].height;
        suspectsInput >> magic;
        if(magic=="No")suspects[i].hasMagic = false;
        else suspects[i].hasMagic = true;
        suspectsInput >> suspects[i].eyeDepth;
        suspectsInput >> suspects[i].eyeDistance;
        suspectsInput >> suspects[i].NFDistance;
        suspectsInput >> suspects[i].NLDistance;
    }

    suspectsInput.close();

	return 0;
}
