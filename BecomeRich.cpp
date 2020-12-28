#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // rand
#include <unistd.h> // sleep
#include <ctime>    //srand

using namespace std;

int DifrentHardnesses (ifstream& category, int currentHardnesL);
string getAnswers (string line, int& i);

struct Question {
    string question;
	string trueAns;
	string ans1;
	string ans2;
	string ans3;
};

int main() {
    Question q;
    int hardnesLevel = 49;
    int numberHardnesses = 2;

    srand((unsigned int)time(NULL));// for more precise random number

    ifstream categoryFile;
    categoryFile.open("Painting.txt", ios::in);
    if (categoryFile.is_open()) {
        numberHardnesses = DifrentHardnesses(categoryFile, hardnesLevel);

        string line;
        int randomQuest = rand() % numberHardnesses; //choses one question
        int currentQuest = 0; // track current question

        cout<<"randomQuest: "<< randomQuest<<endl;

        while (getline(categoryFile, line)) {
            int quetionHardness = line[0];

            if (quetionHardness == hardnesLevel) {
                if(currentQuest == randomQuest) {
                    int i = 2;
                    string sentance;
                    while(line[i] != '?') {
                       sentance = sentance + line[i];
                       i++;
                    }
                    q.question = sentance + '?';
                    cout<<q.question<<endl;

                    q.trueAns = getAnswers(line, ++i);
                    q.ans1 = getAnswers(line, ++i);
                    q.ans2 = getAnswers(line, ++i);
                    q.ans3 = getAnswers(line, ++i);

                    sentance.clear();
                    sentance = 'a' + q.ans1;
                    cout<<sentance<<endl;

                    currentQuest++;
                }
                else currentQuest++;
            }
        }
    }
    else {
        cout << "An error has ocure during the opening of the file!" << endl;
    }

    categoryFile.close();

    return 0;
}

//calculates how many of 1 hardness level is there
int DifrentHardnesses (ifstream& category, int currentHardnesL) {
    string line;
    int numHardnesses = 0;
    while (getline(category, line)) {
        int questHardness = line[0];

        if (questHardness == currentHardnesL)
            numHardnesses++;
    }

    //return to first line
    category.clear();
    category.seekg(0);

    return numHardnesses;
}

string getAnswers (string line, int& i) {
    string sentance = ")";
    while(line[i] != '/') {
        sentance = sentance + line[i];
        i++;
    }
    cout<<sentance<<endl;
    return sentance;
}
