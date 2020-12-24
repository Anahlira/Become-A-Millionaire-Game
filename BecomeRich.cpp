#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // rand
#include <unistd.h> // sleep
#include <ctime>

using namespace std;

//calculates how many of 1 hardness level is there
int DifrentHardnesses (ifstream& category, int currentHardnesL) {
    string line;
    int numHardnesses = 0;
    while (getline(category, line)) {
        int questHardness = line[0];

        if (questHardness == currentHardnesL)
            numHardnesses++;
    }

    category.clear();
    category.seekg(0);

    return numHardnesses;
}

struct Question {
    string question;
	string trueAns;
	string ans1;
	string ans2;
	string ans3;
};

int main() {
    int hardnesLevel = 49;
    int numberHardnesses = 2;

    srand((unsigned int)time(NULL));// for more precise random number

    ifstream category;
    category.open("Painting.txt", ios::in);
    if (category.is_open()) {
        numberHardnesses = DifrentHardnesses(category, hardnesLevel);

        string line;
        int randomQuest = rand() % numberHardnesses; //choses one question
        int i = 0; // track current question

        cout<<"randomQuest: "<< randomQuest<<endl;

        while (getline(category, line)) {
            int quetionHardness = line[0];

            if (quetionHardness == hardnesLevel) {
                if(i == randomQuest) {
                    cout<<line<<endl;
                    i++;
                }
                else i++;
            }
            else cout<< "Sorry" <<endl;
        }
    }
    else {
        cout << "An error has ocure during the opening of the file!" << endl;
    }

    category.close();

    return 0;
}
