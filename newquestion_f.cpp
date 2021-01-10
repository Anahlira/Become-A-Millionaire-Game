/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Teodora Slavova
* @idnumber 62548
* @compiler GCC
*
* <new question fuction>
*
*/

#include "main_functions.h"

void NewQuestion (Question &q, const int topBorder , const int bottomBorder, const int leftBorder , const int rightBorder , const int middleBorder) {
    NewScreen(topBorder);

    fstream categoryFile;
    string line;
    string category;


    //..............Choses the category...............//

    int delimiterPos = 0;
    int row = 1;
    int chosedCateggoryN = 0;

    fstream allCategories;
    ShowCategories(row, allCategories, delimiterPos, false);

    Border(bottomBorder);
    Border();
    AlignCenter("Please chose a category: ");

    UserInput(chosedCateggoryN, 1, row);

    int currentRow = 1;
    while (getline(allCategories, line)) {
        if(currentRow == chosedCateggoryN) {
            category = line.substr(delimiterPos + 1) + ".txt";
            break;
        }
        currentRow++;
    }

    if(allCategories.is_open())
        allCategories.close();

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    //.............Writing the new question...........//

    string question;
    int difficulty = 0;

    NewScreen(topBorder);
    AlignLeft ("Please finish your question with -> ?");
    Border();

    while(true) {
        AlignLeft ("Enter your question: ");
        getline(cin, question);

        q.question = question;
        for(size_t i = 0; i <= question.length(); i++){
            if (question[i] != '?')
                q.question[i] = question[i];
            else {
                q.question[i] = '?';
                q.question = q.question.substr(0, i + 1);
                break;
            }
        }
        int len = q.question.length() - 1;
        if(q.question[len] == '?')
            break;

        AlignLeft ("Why you did'n finish with -> ?\n");
        cin.clear();
    }

    AlignLeft ("Choose difficulty (1 to 10): ");
    UserInput(difficulty, 1, 10, 0);
    difficulty--;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    NewScreen(topBorder);
    BorderC(32, leftBorder, rightBorder);
    AlignCenter(q.question, leftBorder, rightBorder);
    BorderC(32, leftBorder, rightBorder);
    Border(bottomBorder);
    Border();

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

    categoryFile.open (category, ios::in);
    if (!categoryFile.is_open()) {
        AlignCenter("Unexpected error, the question was not written!");
        pause("Press any key to return to main menu...");
        return;
    }

    while (getline(categoryFile, line)){
        if (line[4] != 42 && line[4] != 32) { //Skips lines with "*" or space
            categoryID = line.substr (2,2);
            IDNumber = int(line[4]) - 48;
            i = 5;

            while(line[i] != '/') {
                IDNumber = IDNumber * 10 + int(line[i]) - 48;
                i++;
            }
            if (newID < IDNumber) {
                    newID = IDNumber;
            }
        }
    }

    newID++;
    if(categoryFile.is_open())
        categoryFile.close();

    categoryFile.open (category, ios::out | ios::app);
    if(!categoryFile.is_open())
        return;
    /* uncomment if you want to see how the question will look like in file
    cout << difficulty << "." << categoryID << newID << "/" << q.question << q.trueAns << "|"
                 << q.ans1 << "|" << q.ans2 << "|" << q.ans3 << "|" << endl;
    pause();
    */
    categoryFile << difficulty << "." << categoryID << newID << "/" << q.question << q.trueAns << "|"
                 << q.ans1 << "|" << q.ans2 << "|" << q.ans3 << "|" << "\n";

    categoryFile.close();
    return;
}
