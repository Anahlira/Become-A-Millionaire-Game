#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // rand
#include <unistd.h> // sleep
#include <ctime>    //srand

using namespace std;

struct Question {
    string question;
	string trueAns;
	string ans1;
	string ans2;
	string ans3;
};

void Border(int characterBorder = 32);
void AlineCenter (string text, int characterBorder1 = 32, int characterBorder2 = 32, int character = 32);

int DifrentHardnesses (ifstream& category, int currentHardnesL);
string getAnswers (string line, int& i);
void ShowAnswer (string ans1, string ans2, int characterBorder1 = 32, int characterBorder2 = 32, int choice1 = 1, int choice2 = 2);
void ShowQuestion (int& i, string line, int& trueAnswer, Question &q);
void UserInput (int& userAnswer, int minValue = 1, int maxValue = 4);

int main() {

    //....................Main menu.....................//
    int choice = 0;

    Border(220);
    Border(220);
    cout<<endl;
    AlineCenter("GET SOME MONEY");
    cout<<endl<<endl;

    AlineCenter("New game");
    AlineCenter("New question");
    AlineCenter("Change question");
    AlineCenter("Exit");
    cout<<endl<<endl;
    Border(223);
    Border(223);

    UserInput(choice);

    switch (choice) {
        case 2:

            break;
        case 3:

            break;
        case 4:
            return 0;
            break;
    }

    //..................................................//

    system("CLS");
    string line;

    //....................Category......................//
    int chosedCateggoryN = 0;
    Border(220);

    fstream categoryAll;
    categoryAll.open("AllCategories.txt", ios::in);

    int row = 1;
    string rowLine;
    while (getline(categoryAll, line)) {
        rowLine = to_string(row) + "." + line;
        AlineCenter(rowLine, 221, 222);
        row++;
    }
    rowLine = to_string(row) + ".All Categories";
    AlineCenter(rowLine, 221, 222);

    categoryAll.clear();
    categoryAll.seekg(0);

    Border(223);

    UserInput(chosedCateggoryN, 1, row);

    int rowC = 1;
    string chosedCategory;
    while (getline(categoryAll, line)) {
        if(rowC == chosedCateggoryN) {
            chosedCategory = line + ".txt";
            break;
        }
    }

    categoryAll.close();
    //..................................................//

    system("CLS");

    //....................New Game......................//

    Question q;
    int hardnesLevel = 49;
    int numberHardnesses = 2;
    int trueAnswer = 0;
    int userAnswer = 0;
    int reward = 100;


    srand((unsigned int)time(NULL));// for more precise random number

    ifstream categoryFile;
    categoryFile.open(chosedCategory, ios::in);

    if (categoryFile.is_open()) {
        numberHardnesses = DifrentHardnesses(categoryFile, hardnesLevel);

        int randomQuest = rand() % numberHardnesses; //choses one question
        int currentLine = 0; // track current question

        while (getline(categoryFile, line)) {
            int quetionHardness = line[0];

            if (quetionHardness == hardnesLevel) {
                if(currentLine == randomQuest) {
                    int i = 2;

                    ShowQuestion(i, line, trueAnswer, q);                           //Question display
                    AlineCenter("Please enter your answer.(Use only numbers!!)");
                    UserInput(userAnswer);

                    if(userAnswer == trueAnswer && hardnesLevel<57) {
                        system("CLS");
                        hardnesLevel++;
                        currentLine = 0;
                        categoryFile.clear();
                        categoryFile.seekg(0);
                    }
                    else {
                        system("CLS");
                        Border(220);
                        for(int i = 0; i < 5 ; i++) {
                            AlineCenter(".", 221, 222);
                        }

                        AlineCenter("The game ends here.", 221, 222);
                        string rewardSt;
                        rewardSt = "You won: " + to_string(reward);
                        AlineCenter(rewardSt, 221, 222);

                        for(int i = 0; i < 5 ; i++) {
                            AlineCenter(".", 221, 222);
                        }

                        Border(223);
                        break;
                    }
                }
                else currentLine++;
            }
        }
    }
    else {
        cout << "An error has ocure during the opening of the file!" << endl;
    }

    categoryFile.close();

    return 0;
}





void AlineCenter (string text, int characterBorder1, int characterBorder2, int character) {
    int length = text.length();
    char st[3];
    st[0] = character;
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    cout<<st[1];

    for(int i = 0; i < (68 - length)/2; i++) {
        cout<< st[0];
    }
    cout<<text;

    for(int i = 0; i < (69 - length)/2; i++) {
        cout<< st[0];
    }

    cout<<st[2];

    cout<<endl;
    return;
}

void Border(int characterBorder) {
    char st[1];
    st[0] = characterBorder;
    for(int i = 0; i < 70; i++) {
        cout<< st[0];
    }
    cout<<endl;
    return;
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
    return sentance;
}

void ShowAnswer (string ans1, string ans2, int characterBorder1, int characterBorder2, int choice1, int choice2) {
    char st[3];
    st[0] = 32; //space
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    cout << st[1] << st[0] << choice1 << ans1;
    for(int i = ans1.length() + 3; i < 34; i++) {
        cout<<st[0];
    }
    cout << choice2 << ans2;
    for(int i = 35 + ans2.length(); i < 69; i++) {
        cout<<st[0];
    }

    cout << st[2] << endl;
    return ;
}

void ShowQuestion (int& i, string line, int& trueAnswer, Question &q) {
    Border(220);

    string sentance;
    while(line[i] != '?') {
        sentance = sentance + line[i];
        i++;
    }
    q.question = sentance + '?';
    AlineCenter(sentance, 221, 222);

    Border(223);

    q.trueAns = getAnswers(line, ++i);
    q.ans1 = getAnswers(line, ++i);
    q.ans2 = getAnswers(line, ++i);
    q.ans3 = getAnswers(line, ++i);

    trueAnswer = rand() % 4 + 1;

    switch (trueAnswer) {
        case 1:
            ShowAnswer(q.trueAns, q.ans1, 221, 222);
            ShowAnswer(q.ans2, q.ans3, 221, 222, 3, 4);
            break;
        case 2:
            ShowAnswer(q.ans1, q.trueAns, 221, 222);
            ShowAnswer(q.ans2, q.ans3, 221, 222, 3, 4);
            break;                                                       //Random right answer place
        case 3:
            ShowAnswer(q.ans2, q.ans1, 221, 222);
            ShowAnswer(q.trueAns, q.ans3, 221, 222, 3, 4);
            break;
        case 4:
            ShowAnswer(q.ans3, q.ans1, 221, 222);
            ShowAnswer(q.ans2, q.trueAns, 221, 222, 3, 4);
            break;
    }

    Border(220);
}

void UserInput (int& userAnswer, int minValue, int maxValue) {
    string invalid;
    invalid = "Enter only numbers between " + to_string(minValue) + " and " + to_string(maxValue) + "!";
    while(true) {
        cout << endl;
        for(int i = 0; i < 35; i++) cout<< " ";
        cin>>userAnswer;

        if(userAnswer >= minValue && userAnswer <= maxValue) break;

        AlineCenter(invalid);
        cin.clear();
        cin.ignore();
    }
    return ;
}
