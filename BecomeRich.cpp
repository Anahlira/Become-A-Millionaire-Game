#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // rand
#include <unistd.h> // sleep
#include <ctime>    //srand
#include <conio.h>

using namespace std;

struct Question {
    string question;
	string trueAns;
	string ans1;
	string ans2;
	string ans3;
};

void LetterByLetter(string text, int time = 0);
void Border(int characterBorder = 32);
void NewScreen(int border = 220);
void AlineCenter (string text, int characterBorder1 = 32, int characterBorder2 = 32,int time = 0, int character = 32);

//string IDToString(string line, int& i = 2);
int DifrentDifficulties (ifstream& category, int currentHardnesL);
string getAnswers (string line, int& i);
void ShowAnswer (string ans1, string ans2, int characterBorder1 = 32, int characterBorder2 = 32, int choice1 = 1, int choice2 = 2);
void ShowQuestion (int& i, string line, int& trueAnswer, Question &q);
void UserInput (int& userAnswer, int minValue = 1, int maxValue = 4, int center = 35);
void NextQuestion (ifstream& categoryFile, int chosedCategoryN, string& chosedCategory, int row);
void NextDifficulty (int question, int& difficulty);
void Win (int& reward, int question);

void NewQuestion (Question &q);
void ChangeQuestion();



int main() {
    Question q;

    //...................................Main menu........................................//
    int choice = 0;
    bool newGame = false;

    while (!newGame) {
    NewScreen(220);
    Border(220);

    cout << endl;
    AlineCenter("GET SOME MONEY", 32, 32);//, 90000);
    cout << endl << endl;

    AlineCenter("New game");
    //sleep(1);
    AlineCenter("New question");
    //sleep(1);
    AlineCenter("Change question");
    //sleep(1);
    AlineCenter("Exit");
    //sleep(1);

    cout<<endl<<endl;
    Border(223);
    Border(223);

    UserInput(choice);

    switch (choice) {
        case 1:
            newGame = true;
            break;
        case 2:
            NewQuestion(q);
            break;
        case 3:
            ChangeQuestion();
            break;
        case 4:
            return 0;
            break;
    }
    }
    //....................................................................................//

    NewScreen();
    string line;

    //...................................Category.........................................//

    //Show categories ...........

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

    //Select the category ...........
    int currentRow = 1;
    string chosedCategory;
    int chosedCateggoryN = 1;

    UserInput(chosedCateggoryN, 1, row);

    if(chosedCateggoryN != row) {
        while (getline(categoryAll, line)) {
            if(currentRow == chosedCateggoryN) {
                chosedCategory = line + ".txt";
                break;
            }
            currentRow++;
        }
    }

    categoryAll.close();
    //.....................................................................................//

    system("CLS");

    //....................................New Game.........................................//

    int difficultyLevel = 47;
    int numberDifficulties = 2;
    int showedQuestions[15][1] = {0};

    int trueAnswer = 0;
    int userAnswer = 0;

    int ownMoney = 0;
    int reward = 0;

    srand((unsigned int)time(NULL));// for more precise random number

    ifstream categoryFile;
    for (int currentQ = 1; currentQ < 16; currentQ++) {

        NextQuestion(categoryFile, chosedCateggoryN, chosedCategory, row);
        NextDifficulty(currentQ, difficultyLevel);
        Win(reward, currentQ);

        numberDifficulties = DifrentDifficulties(categoryFile, difficultyLevel);
        //unfinished category
        if(numberDifficulties < 1) {
            categoryFile.close();
            return 0;
        }

        //............chose the question.............//
        bool foundQuestion = false;

        while(!foundQuestion) {

            int randomQuest = rand() % numberDifficulties; //choses one question
            int currentLine = 0; // track current question

            if(!categoryFile.is_open()) {
                cout << "An error has ocurre during the opening of the file!" << endl;
                return 0;
            }

            while (getline(categoryFile, line)) {
                int quetionHardness = line[0];

                if (quetionHardness == difficultyLevel) {
                    if(currentLine == randomQuest) {
                        int i = 2;
                        for(i; line[i] != '/'; i++) {
                            //currentID[i-2] = line[i];
                        }
                        i++;

                        if(showedQuestions[difficultyLevel-47][0] == randomQuest + 1) {
                            foundQuestion = false;
                            break;
                        }
                        else foundQuestion = true;

                        //.........Question display.........//
                        Border(220);

                        AlineCenter("Reward for the round: " + to_string(reward));

                        //Border(223);

                        ShowQuestion(i, line, trueAnswer, q);
                        AlineCenter("Please enter your answer.(Use only numbers!!)");
                        UserInput(userAnswer);

                        //............won round............//
                        if(userAnswer == trueAnswer) {
                            showedQuestions[difficultyLevel-47][0] = randomQuest + 1;
                            ownMoney = reward;
                            currentLine = 0;

                            NewScreen();

                            AlineCenter("Congrats, you won: " + to_string(ownMoney));
                            cout<<endl;
                            AlineCenter("Press any key to continue...");

                            Border(223);
                            getch();
                            system("CLS");

                            break;
                        }

                        //............lost game.............//
                        else {
                            NewScreen();
                            for(int i = 0; i < 5 ; i++) {
                                AlineCenter(".", 221, 222);
                            }

                            AlineCenter("The true answer was: " + to_string(trueAnswer) + q.trueAns, 221, 222);
                            AlineCenter("You won: " + to_string(ownMoney), 221, 222);

                            for(int i = 0; i < 5 ; i++) {
                                AlineCenter(".", 221, 222);
                            }

                            Border(223);

                            cout<<endl;
                            AlineCenter("Press any key to exit...");
                            getch();

                            if(categoryFile.is_open())
                                categoryFile.close();
                            return 0;
                        }
                    }
                    else currentLine++;
                }
            }
        categoryFile.clear();
        categoryFile.seekg(0);
        }
    }

    //................congrats screen..............//
    NewScreen();
    for(int i = 0; i < 5 ; i++) {
        AlineCenter(".", 221, 222);
    }

    AlineCenter("You won the game!!!", 221, 222);
    string rewardSt;
    rewardSt = "Reward: " + to_string(ownMoney);
    AlineCenter(rewardSt, 221, 222);

    for(int i = 0; i < 5 ; i++) {
        AlineCenter(".", 221, 222);
    }

    Border(223);

    cout<<endl;
    AlineCenter("Press any key to exit...");
    getch();

    if(categoryFile.is_open())
        categoryFile.close();

    return 0;
}




void LetterByLetter(const string text, int time) {
    for(int i = 0; i < text.length(); i++) {
        cout<<text[i];
        usleep(time);
    }
    return;
}

void AlineCenter (string text, int characterBorder1, int characterBorder2, int time, int character) {
    int length = text.length();
    char st[3];
    st[0] = character;
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    cout<<st[1];

    for(int i = 0; i < (68 - length)/2; i++) {
        cout<< st[0];
    }
    LetterByLetter(text, time);

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

void NewScreen(int border) {
    system("CLS");
    Border(220);
    return;
}


//calculates how many of 1 hardness level is there
int DifrentDifficulties (ifstream& category, int currentHardnesL) {
    category.clear();
    category.seekg(0);

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

    if(numHardnesses < 1) {
            cout << "Upss... It seems that you did't finish a category" << endl;
            cout << "Please finish your category, it should have at least 2 questions from every difficulty level." << endl;
            cout << "This message will continue to show, until you complete your category!" << endl;
            cout << "Hope you make a lot of money next time!" << endl;
            system ("pause");
        }

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
    q.question = sentance + "?";
    AlineCenter(q.question, 221, 222, 50000);

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

void UserInput (int& userAnswer, int minValue, int maxValue, int center) {
    string invalid;
    invalid = "Enter only numbers between " + to_string(minValue) + " and " + to_string(maxValue) + "!";
    while(true) {
        //cout << endl;
        for(int i = 0; i < center; i++) cout<< " ";
        cin>>userAnswer;

        if(userAnswer >= minValue && userAnswer <= maxValue) break;

        AlineCenter(invalid);
        cin.clear();
        cin.ignore();
    }
    return ;
}

void NextQuestion (ifstream& categoryFile, int chosedCategoryN, string& chosedCategory, int row) {
    system("CLS");

    //chose random category
    if(chosedCategoryN == row) {
        if(categoryFile.is_open())
            categoryFile.close();

        row--;
        fstream categoryAll;
        categoryAll.open("AllCategories.txt", ios::in);

        int chosedCateggoryN = 0;
        chosedCateggoryN = rand() % row + 1;
        int currentRow = 1;

        string line;
        while (getline(categoryAll, line)) {
            if(currentRow == chosedCateggoryN) {
                chosedCategory = line + ".txt";
                break;
            }
            currentRow++;
        }

        categoryAll.close();
    }

    //open file
    if(!categoryFile.is_open()) {
            categoryFile.open(chosedCategory, ios::in);
        }
}

void NextDifficulty (int question, int& difficulty) {
    if(question == 2 || question == 4 || question == 11 || question == 13 || question == 15) {
        return ;
    }
    else difficulty++;
    return;
}

void Win (int& reward, int question) {
    if(question == 5) {
        reward = 1000;
        return ;
    }

    if(question == 12){
        reward = 125000;
        return ;
    }

    if(question > 5){
        reward = reward*2;
        return ;
    }

    reward = reward + 100;
    return;
}

void NewQuestion (Question &q) {

    return;
}

void ChangeQuestion() {
    cout << "one day you will have the chance...";
    system("pause");
    return ;
}
