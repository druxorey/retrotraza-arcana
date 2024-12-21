#include <iostream>
#include <fstream> 
using namespace std;

struct person
{
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

	ifstream suspectsIN("dataBase.in");
    int suspectQuantity=0;
    suspectsIN>>suspectQuantity;
    person suspects[suspectQuantity];
    string name, lastname, magic;
    for (int i = 0; i < suspectQuantity; i++)
    {
        suspectsIN>>name;
        suspectsIN>>lastname;
        suspects[i].name=name+" "+lastname;
        suspectsIN>>suspects[i].species;
        suspectsIN>>suspects[i].height;
        suspectsIN>>magic;
        if(magic=="No")suspects[i].hasMagic=false;
        else suspects[i].hasMagic=true;
        suspectsIN>>suspects[i].eyeDepth;
        suspectsIN>>suspects[i].eyeDistance;
        suspectsIN>>suspects[i].NFDistance;
        suspectsIN>>suspects[i].NLDistance;
    }
    suspectsIN.close();

	return 0;
}
