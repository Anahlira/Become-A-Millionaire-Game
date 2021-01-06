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
void Border(int characterBorder = 32, int length = 70);
void BorderC(int characterBorder = 32, int characterBorderB = 32, int characterBorderE = 32);
void NewScreen(int border = 220);
void AlignCenter (string text, int characterBorder1 = 32, int characterBorder2 = 32,int time = 0, int character = 32);
void AlignLeft (string text, int characterBorder1 = 32, int characterBorder2 = 32,int time = 0, int character = 32);
void WaitUser (string text, bool center = 1, int border = 32);

int DifrentDifficulties (ifstream& category, int currentHardnesL);
string getAnswers (string line, int& i);
void CollectQuestion(int i, string line, Question &q);
void ShowAnswer (string ans1, string ans2, int characterBorder1 = 32, int characterBorder2 = 32, int choice1 = 1, int choice2 = 2);
void ShowQuestion (int& trueAnswer, Question &q);
void UserInput (int& userAnswer, int minValue = 1, int maxValue = 4, int center = 35);
void NextQuestion (ifstream& categoryFile, int chosedCategoryN, string& chosedCategory, int row);
void NextDifficulty (int question, int& difficulty);
void Win (int& reward, int question);
void ShowReward(int reward);
void ShowLifelines (bool lifelines[]);
int GuessTheAnsewer(int difficulty);
void ActivateLifeline(int userAnswer, int difficulty, Question &q);
bool ChooseLifeline (bool lifelines[], int& userAnswer);

string WriteAnswer (string text = "Enter true answer: ", string errorText = "You didn't write the answer within the limitation!\n",int limitation = 38);
void NewQuestion (Question &q);
void ChangeQuestion(Question &q);



int main() {
    Question q;
    int topBorder = 220;
    int bottomBorder = 223;
    int leftBorder = 221;
    int rightBorder = 222;
    int middleBorder = 219;

    //...................................Main menu........................................//
    int choice = 0;
    bool newGame = false;

    while (!newGame) {
        NewScreen(topBorder);
        BorderC(32, leftBorder, rightBorder);

        BorderC(32, leftBorder, rightBorder);
        AlignCenter("GET SOME MONEY", leftBorder, rightBorder, 90000);
        BorderC(32, leftBorder, rightBorder);
        BorderC(32, leftBorder, rightBorder);

        AlignCenter("New game", leftBorder, rightBorder);
        AlignCenter("New question", leftBorder, rightBorder);
        AlignCenter("Change question", leftBorder, rightBorder);
        AlignCenter("Exit", leftBorder, rightBorder);

        BorderC(32, leftBorder, rightBorder);
        BorderC(32, leftBorder, rightBorder);
        Border(bottomBorder);

        UserInput(choice);

        switch (choice) {
            case 1:
                newGame = true;
                break;
            case 2:
                NewQuestion(q);
                break;
            case 3:
                ChangeQuestion(q);
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
    BorderC(32, 221, 222);

    fstream categoryAll;
    categoryAll.open("AllCategories.txt", ios::in);

    int row = 1;
    int delimiterPos;
    string rowLine;
    while (getline(categoryAll, line)) {
        delimiterPos = line.find("/");
        rowLine = to_string(row) + "." + line.substr(delimiterPos + 1);
        AlignCenter(rowLine, 221, 222);
        row++;
    }
    rowLine = to_string(row) + ".All Categories";
    AlignCenter(rowLine, 221, 222);

    categoryAll.clear();
    categoryAll.seekg(0);

    BorderC(32, 221, 222);
    Border(223);

    //Select the category ...........
    int currentRow = 1;
    string chosedCategory;
    int chosedCateggoryN = 1;

    UserInput(chosedCateggoryN, 1, row);

    if(chosedCateggoryN != row) {
        while (getline(categoryAll, line)) {
            if(currentRow == chosedCateggoryN) {
                chosedCategory = line.substr(delimiterPos + 1) + ".txt";
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

    bool lifelines[3] = {1, 1, 1};
    //string llInput; //yes or no

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
                        while(line[i] != '/') i++;
                        i++;

                        if(showedQuestions[difficultyLevel-47][0] == randomQuest + 1) {
                            foundQuestion = false;
                            break;
                        }
                        else foundQuestion = true;

//.......................Question display......................//


                        CollectQuestion(i, line, q);
                        ShowReward(reward);
                        ShowQuestion(trueAnswer, q);
                        if (lifelines[0] == 1 || lifelines[1] == 1 || lifelines[2] == 1) { //check if the player have lifelines
                            ShowLifelines(lifelines);
                            AlignLeft("Would you like to use a lifeline ([y] yes : [n] no): ");
                            if(ChooseLifeline(lifelines, userAnswer)) {
                                ActivateLifeline(userAnswer, difficultyLevel, q);
                                ShowReward(reward);
                                ShowQuestion(trueAnswer, q);
                            }
                        }

                        Border();
                        AlignCenter ("Please enter your answer.(Use only numbers!!)");
                        UserInput(userAnswer);

//............................WON ROUND..............................//
                        if(userAnswer == trueAnswer) {
                            showedQuestions[difficultyLevel-47][0] = randomQuest + 1;
                            ownMoney = reward;
                            currentLine = 0;

                            NewScreen();

                            AlignCenter("Congrats, you won: " + to_string(ownMoney));
                            Border();
                            AlignCenter("Press any key to continue...");

                            Border(223);
                            getch();
                            system("CLS");

                            break;
                        }

//...........................LOST GAME........................,.....//
                        else {
                            NewScreen();
                            for(int i = 0; i < 5 ; i++) {
                                AlignCenter(".", 221, 222);
                            }

                            AlignCenter("The true answer was: " + to_string(trueAnswer) + ")" + q.trueAns, 221, 222);
                            AlignCenter("You won: " + to_string(ownMoney), 221, 222);

                            for(int i = 0; i < 5 ; i++) {
                                AlignCenter(".", 221, 222);
                            }

                            Border(223);

                            cout<<endl;
                            AlignCenter("Press any key to exit...");
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

    //............................congrats screen.................................//

    NewScreen();
    for(int i = 0; i < 5 ; i++) {
        AlignCenter(".", 221, 222);
    }

    AlignCenter("You won the game!!!", 221, 222);
    string rewardSt;
    rewardSt = "Reward: " + to_string(ownMoney);
    AlignCenter(rewardSt, 221, 222);

    for(int i = 0; i < 5 ; i++) {
        AlignCenter(".", 221, 222);
    }

    Border(223);

    cout<<endl;
    AlignCenter("Press any key to exit...");
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

void AlignCenter (string text, int characterBorder1, int characterBorder2, int time, int character) {
    string text2 = text;
    int length = text.length();
    char st[3];
    st[0] = character;
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    //int spaceCounter = 0;
    int lastSpace = 0;
    int startPos = 0;
    int rotations = 1;
    bool stop = false;

    text2.clear();
    do {
        if(text.length() / rotations > 66) {
            for (int i = 0; i < 67; i++) {
                if(text[startPos + i] == 32) {
                    lastSpace = i + startPos;
                    //spaceCounter++;
                }
            }
            text2 = text.substr (startPos, lastSpace - startPos);
        }
        else {
            text2 = text.substr (lastSpace);
            stop = true;
        }
        length = text2.length();

        //.....display line.....//
        cout << " " <<st[1];

        for(int i = 0; i < (68 - length)/2; i++) {
            cout << st[0];
        }
        LetterByLetter(text2, time);
        for(int i = 0; i < (69 - length)/2; i++) {
            cout << st[0];
        }

        cout << st[2] << endl;
        //......................//

        startPos = lastSpace + 1;
        text2 = text;
        rotations++;

    } while (!stop);
    return;
}
void AlignLeft (string text, int characterBorder1, int characterBorder2, int time, int character) {
    int length = text.length();
    char st[3];
    st[0] = character;
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    cout << " " << st[1] << " ";

    LetterByLetter(text, time);
    return;
}

void Border(int characterBorder, int length) {
    char st[1];
    st[0] = characterBorder;
    cout << " ";
    for(int i = 0; i < length; i++) {
        cout<< st[0];
    }
    cout<<endl;
    return;
}
void BorderC(int characterBorder, int characterBorderB, int characterBorderE) {
    char st[3];
    st[0] = characterBorder;
    st[1] = characterBorderB;
    st[2] = characterBorderE;
    cout << " " << st[1];
    for(int i = 0; i < 68; i++) {
        cout<< st[0];
    }
    cout<< st[2] << endl;
    return;
}

void NewScreen(int border) {
    system("CLS");
    Border(220);
    return;
}

void WaitUser (string text, bool center, int border) {
    if(center) {
        AlignCenter(text, border, border);
        Border(border);
    }
    else {
        Border(border);
        AlignLeft(text, border, border);
        Border(border);
    }
    getch();
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
    string sentance;
    while(line[i] != '/') {
        sentance = sentance + line[i];
        i++;
    }
    return sentance;
}

void CollectQuestion(int i, string line, Question &q) {
    string sentance;
    while(line[i] != '?') {
        sentance = sentance + line[i];
        i++;
    }
    q.question = sentance + "?";

    q.trueAns = getAnswers(line, ++i);
    q.ans1 = getAnswers(line, ++i);
    q.ans2 = getAnswers(line, ++i);
    q.ans3 = getAnswers(line, ++i);
    return;
}

void ShowAnswer (string ans1, string ans2, int characterBorder1, int characterBorder2, int choice1, int choice2) {
    char st[3];
    st[0] = 32; //space
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    if(ans1 == " ") cout << st[1] << st[0] << " " << ans1;
    else cout << st[1] << st[0] << choice1<< ")" << ans1;

    for(int i = ans1.length() + 3; i < 34; i++) {
        cout<<st[0];
    }
    if(ans2 == " ") cout << " " << ans2;
    else cout << choice2 << ")" << ans2;
    for(int i = 35 + ans2.length(); i < 69; i++) {
        cout<<st[0];
    }

    cout << st[2] << endl;
    return ;
}

void ShowQuestion (int& trueAnswer, Question &q) {
    BorderC(254, 219, 219);

    AlignCenter(" ", 221, 222);
    AlignCenter(q.question, 221, 222, 50000);
    AlignCenter(" ", 221, 222);

    BorderC(223, 223, 223);
    Border();

    trueAnswer = rand() % 4 + 1;

    switch (trueAnswer) {
        case 1:
            ShowAnswer(q.trueAns, q.ans1);
            ShowAnswer(q.ans2, q.ans3, 32, 32, 3, 4);
            break;
        case 2:
            ShowAnswer(q.ans1, q.trueAns);
            ShowAnswer(q.ans2, q.ans3, 32, 32, 3, 4);
            break;                                                       //Random right answer place
        case 3:
            ShowAnswer(q.ans2, q.ans1);
            ShowAnswer(q.trueAns, q.ans3, 32, 32, 3, 4);
            break;
        case 4:
            ShowAnswer(q.ans3, q.ans1);
            ShowAnswer(q.ans2, q.trueAns, 32, 32, 3, 4);
            break;
    }
    Border();
    Border(31);
    Border();
    return;
}

void UserInput (int& userAnswer, int minValue, int maxValue, int center) {
    string invalid;
    invalid = "Enter only numbers between " + to_string(minValue) + " and " + to_string(maxValue) + "!";
    while(true) {
        for(int i = 0; i < center; i++) cout<< " ";
        cin>>userAnswer;

        if(userAnswer >= minValue && userAnswer <= maxValue) break;

        if(center != 0)
            AlignCenter (invalid);
        else AlignLeft (invalid);
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
        int demitterPos = 0;
        while (getline(categoryAll, line)) {
            if(currentRow == chosedCateggoryN) {
                demitterPos = line.find("/");
                chosedCategory = line.substr(demitterPos + 1) + ".txt";
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

void ShowReward(int reward) {
    Border(220);
    AlignCenter(" ", 221, 222);
    AlignCenter("Reward for the round: " + to_string(reward), 221, 222);
    AlignCenter(" ", 221, 222);
    return;
}

void ShowLifelines (bool lifelines[]){
    AlignLeft ("Available lifeline: ");
    Border();
    if(lifelines[0]) {
        AlignLeft ("[1] 50/50");
        cout << endl;
    }
    if(lifelines[1]) {
        AlignLeft ("[2] Call your friend");
        cout << endl;
    }
    if(lifelines[2]) {
        AlignLeft ("[3] Help from the audience");
        cout << endl;
    }
    Border();
    return;
}

bool ChooseLifeline (bool lifelines[], int& userAnswer) {
    string llInput;
    while(true) {
        cin >> llInput;
        if(llInput == "y" || llInput == "Y") {
            NewScreen(31);

            ShowLifelines(lifelines);
            while(true) {
                AlignLeft("What would you like to use:");
                cin >> userAnswer;
                if(userAnswer == 1 && lifelines[0] == 1) {
                    lifelines[0] = 0;
                    break;
                }
                else if(userAnswer == 2 && lifelines[1] == 1) {
                    lifelines[1] = 0;
                    break;
                }
                else if(userAnswer == 3 && lifelines[2] == 1) {
                    lifelines[2] = 0;
                    break;
                }
                cin.clear();
                cin.ignore();
            }
            break;
        }
        if(llInput == "n" || llInput == "N")
            return 0;
    }
    return 1;
}

int GuessTheAnsewer(int difficulty) {
    int random = rand() % 100 + 1;
    difficulty = difficulty - 47;
    if (difficulty >=0 && difficulty < 3) {
        if(random > 0 && random < 81)
            return 4;
        else return rand() % 3 + 1;
    }
    else  if (difficulty >=4 && difficulty < 6) {
        if(random > 0 && random < 61)
            return 4;
        else return rand() % 3 + 1;
    }
    else {
        if(random > 0 && random < 31)
            return 4;
        else return rand() % 3 + 1;
    }
}

void ActivateLifeline(int userAnswer, int difficulty, Question &q){

    string friendName = "My friend";
    int random = rand() % 3 + 1;
    int randomP = 0; //to save the first eliminated answer

    int helpAnswer = GuessTheAnsewer(difficulty);
    string answer;
    if(helpAnswer == 1) answer = q.ans1;
    else if(helpAnswer == 2) answer = q.ans2;
    else if(helpAnswer == 3) answer = q.ans3;
    else answer = q.trueAns;

    switch(userAnswer) {
        case 1:
            for(int i = 0; i < 2; i++) {
                if (random == 1)
                    q.ans1 = " ";
                if (random == 2)
                    q.ans2 = " ";
                if (random == 3)
                    q.ans3 = " ";
                randomP = random;
                random = rand() % 3 + 1;
                while(random == randomP) {
                    random = rand() % 3 + 1;
                }
            }
            system("CLS");
            break;

        case 2:
            NewScreen(220);
            AlignLeft("Who do you wanna call: ", 32);
            cin.ignore();
            getline(cin, friendName);
            NewScreen();
            AlignCenter("Calling " + friendName);
            AlignCenter(". . . . .", 32, 32, 300000);

            NewScreen(220);
            BorderC(32, 221, 222);
            AlignCenter("Pres any key to continue the conversation.", 221, 222);
            BorderC(32, 221, 222);
            Border(223);

            WaitUser(friendName + ": Hello? What's up? Need help?", 0);
            WaitUser("Yes. " + q.question, 0);
            WaitUser(friendName + ": Just... Let me think for a second.", 0);
            Border();
            AlignLeft("Waiting...", 32, 32, 80000);
            Border();
            WaitUser(friendName + ": Ok, I think it is " + answer, 0);
            system("CLS");
            Border();
            AlignCenter(friendName + " thinks the true answer is " + answer);
            break;

        case 3:
            char st[1];
            st[0] = 220;

            //....percentage of the vote....//
            string a,b,c,d;
            a = q.trueAns;
            b = q.ans1;
            c = q.ans2;
            d = q.ans3;
            switch (rand() % 4 + 1) {
            case 1:
                a = q.ans1;
                b = q.trueAns;
                break;
            case 2:
                a = q.ans2;
                c = q.trueAns;
                break;
            case 3:
                a = q.ans3;
                d = q.trueAns;
                break;
            case 4://to keep the first values
                break;
            }
            string answerS[4] = {a, b, c, d};

            int percentage = 0;
            int usePr[3];
            int longestAns = 0;
            int randMax = 0;

            for (int j = 0; j < 4; j++) {
                if(answerS[j].length() > longestAns)
                    longestAns = answerS[j].length();
            }

            //....percentage of the vote....//
            if(difficulty < 4) {
                percentage = rand() % 12 + 15;
            }
            else percentage = rand() % 3 + 15;
            randMax = 31 - percentage;

            usePr[0] = rand() % randMax/2 + 1;
            randMax = randMax - usePr[0];

            if(randMax > 0) {
                usePr[1] = rand() % randMax + 1;
                randMax = randMax - usePr[1];
                if (randMax > 0) {
                    usePr[2] = rand() % randMax + 1;
                }
                else usePr[2] = 0;
            }
            else  usePr[1] = 0;

            //-------- show pow lines----------//
            system("CLS");
            AlignLeft("         Audience poll"); //spaces are for visuals
            Border();
            Border();
            int z = 0;

            for(int j = 0; j < 4; j++) {
                if(answerS[j] == answer) {
                    cout << answer << ": ";
                    for(int i = answer.length(); i < longestAns; i++)
                        cout << " ";

                    Border(220, percentage);
                }
                else {
                    cout << answerS[j] << ": ";
                    for(int i = answerS[j].length(); i < longestAns; i++)
                        cout << " ";

                    Border(220, usePr[z]);
                    z++;
                }
            }
            //----------------------------------//
            Border();
            break;
        }

    return;
}

string WriteAnswer (string text, string textError, int limitation) {
    string answer;
    while(true) {
        AlignLeft (text);
        getline(cin, answer);

        if (answer.length() < limitation && answer.length() > 2)
            break;

        AlignLeft (textError);

        cin.clear();
    }
    return answer;
}

void NewQuestion (Question &q) {
    NewScreen();

    fstream categoryFile;
    string line;
    string category;
    bool foundCategory = false;

    fstream allCategories;
    allCategories.open ("AllCategories.txt");

    //..............Choses the category...............//

    AlignLeft("Please chose a category: ");
    while(!foundCategory) {
        cin >> category;

        while(getline(allCategories, line)) {
            int delimiterPos = line.find("/");
            if(line.substr(delimiterPos + 1) == category || line.substr(0, delimiterPos) == category) {
                category = line.substr(delimiterPos + 1);
                foundCategory = true;
                break;
            }
        }
        allCategories.clear();
        allCategories.seekg(0);
        AlignLeft ("Please enter existing category: ");
        cin.clear();
        cin.ignore();
    }
    allCategories.close();

    //.............Writing the new question...........//

    string question;
    int difficulty = 0;

    NewScreen();
    AlignLeft ("Please finish your question with -> ?");
    Border();

    while(true) {
        AlignLeft ("Enter your question: ");
        getline(cin, q.question);

        int i = q.question.length();
        if(q.question[i-1] == '?')
            break;

        AlignLeft ("Why you did'n finish with -> ?\n");
        cin.clear();
    }

    AlignLeft ("Choose difficulty (1 to 10): ");
    UserInput(difficulty, 1, 10, 0);
    difficulty--;
    cin.ignore();

    NewScreen();
    AlignLeft("Your answers should be no longer than 38 characters!\n");

    q.trueAns = WriteAnswer();
    q.ans1 = WriteAnswer("Enter wrong answer: ");
    q.ans2 = WriteAnswer("Enter wrong answer: ");
    q.ans3 = WriteAnswer("Enter wrong answer: ");

    //..........Start writing.........//

    int IDNumber = 0;
    int newID = 0;
    string categoryID;
    int i = 0;

    categoryFile.open (category + ".txt", ios::in);
    if(!categoryFile.is_open())
        return;

    while(getline(categoryFile, line)){
        if(line[4] != 42 && line[4] != 32) { //Skips lines with "*" or space
            categoryID = line.substr (2,2);
            IDNumber = int(line[4]) - 48;
            i = 5;

            while(line[i] != '/') {
                IDNumber = IDNumber*10 + int(line[i]) - 48;
                i++;
            }
            if (newID < IDNumber) {
                    newID = IDNumber;
            }
        }
    }

    newID++;
    categoryFile.close();
    categoryFile.open (category + ".txt", ios::out | ios::app);
    if(!categoryFile.is_open())
        return;

    categoryFile << difficulty << "." << categoryID << newID << "/" << q.question << q.trueAns << "/"
                 << q.ans1 << "/" << q.ans2 << "/" << q.ans3 << "/" <<"\n";

    categoryFile.close();
    return;
}

void ChangeQuestion(Question &q) {
    string changeID;
    string line;
    string textCategory;
    string question;
    char symbol[1];
    symbol[0] = 42;
    int delimiterPos = 0;
    int row = 0;
    bool findCategory = false;
    ifstream allCategories;

    allCategories.open("AllCategories.txt");
    if(!allCategories.is_open()) {
        AlignCenter("Error with the opening of the file...");
        AlignCenter("Press any key to return to the main menu");
        getch();
        return;
    }

    cin.clear();
    cin.ignore();
    NewScreen();
    while(!findCategory){
        AlignLeft("Enter ID:");
        getline(cin, changeID);

        while(getline(allCategories, line)) {
            delimiterPos = line.find("/");
            if (changeID[0] == line[0] && changeID[1] == line[1]) {
                textCategory = line.substr(delimiterPos + 1);
                findCategory = true;
                break;
            }
        }
        if(findCategory) break;

        allCategories.clear();
        allCategories.seekg(0);
        AlignLeft("Enter valid ID.\n");
    }
    allCategories.close();

    fstream changeCategory;
    changeCategory.open(textCategory + ".txt");
    if(!changeCategory.is_open()) {
        AlignCenter("Error with the opening of the category...");
        AlignCenter("Press any key to return to the main menu");
        getch();
        return;
    }

    int gotoS = 0;
    while(getline(changeCategory, line)){
        delimiterPos = line.find("/");
        //cout<<line<<endl;
        if(line.substr(4, delimiterPos - 4) == changeID.substr(2)) {
            question = line;
            break;
        }
        gotoS = gotoS + line.length() + 2;
    }

    changeCategory.clear();
    changeCategory.seekp(gotoS);

    for(int i = 0; i < question.length(); i++)
                changeCategory << "*";
    changeCategory <<endl;

    changeCategory.close();

    string text;
    int chose = 0;
    int i = 2;
    while(line[i] != '/') i++;
    i++;

    CollectQuestion(i, question, q);

    AlignLeft("What do you want to change?\n");
    AlignLeft("[1]Question\n");
    AlignLeft("[2]True answer\n");
    AlignLeft("[3]Wrong answers\n");
    Border();
    Border(223);

    UserInput(chose, 1, 3, 0);
    cin.clear();
    cin.ignore();

    NewScreen(220);
    switch (chose) {
        case 1:
            AlignLeft ("Please finish your question with -> ?\n");
            while(true) {
                AlignLeft ("Enter your new question: ");
                getline(cin, text);

                int i = text.length();
                if(text[i-1] == '?')
                    break;

                AlignLeft ("Why you did'n finish with -> ?\n");
                cin.clear();
            }
            q.question = text;
            break;
        case 2:
            AlignLeft("New true answer: ");
            q.trueAns = WriteAnswer(text);
            break;
        case 3:
            AlignLeft("New wrong answer: ");
            q.ans1 = WriteAnswer(text);
            AlignLeft("New wrong answer: ");
            q.ans2 = WriteAnswer(text);
            AlignLeft("New wrong answer: ");
            q.ans3 = WriteAnswer(text);
            break;
    }

    changeCategory.open(textCategory + ".txt", ios::app);
    if(!changeCategory.is_open()) {
        AlignCenter("Error with the opening of the category...");
        AlignCenter("Press any key to return to the main menu");
        getch();
        return;
    }

    changeCategory << question.substr(0, delimiterPos + 1) << q.question << q.trueAns << "/"
                 << q.ans1 << "/" << q.ans2 << "/" << q.ans3 << "/" <<"\n";

    changeCategory.close();

    system("pause");
    return ;
}
