#include <iostream>
#include <fstream> 
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


int main() {

	ifstream suspectsInput("dataBase.in");
    int suspectQuantity = 0;
    suspectsInput >> suspectQuantity;
    person suspects[suspectQuantity];
    string name, lastname, magic;

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
