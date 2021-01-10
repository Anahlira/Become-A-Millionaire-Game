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
* <change question function>
*
*/

#include "main_functions.h"
#include "visual_functions.h"
#include "fuctions.h"
#include "user_input.h"


void ChangeQuestion(Question &q, const int topBorder, const int bottomBorder, const int leftBorder, const int rightBorder, const int middleBorder) {
    string changeID;
    string line;
    string textCategory;
    string question;
    int gotoS = 0; //row to remove
    bool findCategory = false;

    //......chose category......//
    NewScreen(topBorder);

    int row = 1;
    int delimiterPos = 0;
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
            textCategory = line.substr(delimiterPos + 1) + ".txt";
            break;
        }
        currentRow++;
    }

    if(allCategories.is_open())
        allCategories.close();
    cin.clear();
    cin.ignore();

    //...............open the category...............//

    fstream changeCategory;
    changeCategory.open(textCategory, ios::in);
    if (!changeCategory.is_open()) {
        AlignCenter("Error with the opening of the category...");
        pause(1, "Press any key to return to the main menu");
        return;
    }

    //.................show ID....................//

    NewScreen(topBorder);
    AlignCenter("Available ID:");
    Border();

    while (getline(changeCategory, line)){
        if(line[0] != '*' && line[0] != ' ') {
            delimiterPos = line.find("?");
            AlignLeft(line.substr(2, delimiterPos - 2));
            cout << endl;
        }
    }

    changeCategory.clear();
    changeCategory.seekg(0);

    Border();
    Border(bottomBorder);

    //...............enter Valid ID.............//

    while (!findCategory) {
        AlignLeft("Enter ID: ");
        getline(cin, changeID);

        while (getline(changeCategory, line)){
            delimiterPos = line.find("/");

            if(line.substr(2, delimiterPos - 2) == changeID) {
                question = line;
                findCategory = true;
                break;
            }
            gotoS = gotoS + line.length() + 2;
        }
        if(findCategory) break;

        changeCategory.clear();
        changeCategory.seekg(0);
        cin.clear();
        gotoS = 0;
        AlignLeft("Enter valid ID.\n");
    }

    if(changeCategory.is_open())
        changeCategory.close();

    //........change the question.........//

    NewScreen(32);
    int trueAnswer = 1; //just to show the question
    CollectQuestion(changeID.length() + 3, line, q);
    ShowQuestion(trueAnswer, q);

    string text;
    int chose = 0;
    int i = 2;
    while(line[i] != '/') i++;
    i++;

    //CollectQuestion(i, question, q);

    AlignLeft("What do you want to change?\n");
    AlignLeft("[1]Question\n");
    AlignLeft("[2]True answer\n");
    AlignLeft("[3]Wrong answers\n");
    Border();
    Border(bottomBorder);

    UserInput(chose, 1, 3, 0);
    cin.clear();
    cin.ignore();

    NewScreen(topBorder);
    switch (chose) {
        case 1:
            AlignLeft ("Please finish your question with -> ?\n");
            while(true) {
                AlignLeft ("Enter your new question: ");
                getline(cin, text);

                q.question = text;
                for(int i = 0; i <= text.length(); i++){
                    if (text[i] != '?')
                        q.question[i] = text[i];
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

    //...delete the old question...//

    changeCategory.open(textCategory);
    if(!changeCategory.is_open()) {
        AlignCenter("Error with the opening of the category...");
        pause(1, "Press any key to return to the main menu");
        return;
    }

    //changeCategory.clear();
    changeCategory.seekp(gotoS);

    for(int i = 0; i < question.length(); i++)
                changeCategory << "*";
    changeCategory << endl;

    if(changeCategory.is_open())
        changeCategory.close();

    //........write the new question.........//

    changeCategory.open(textCategory, ios::out | ios::app);
    if(!changeCategory.is_open()) {
        AlignCenter("Error with the opening of the category...");
        pause(1, "Press any key to return to the main menu");
        return;
    }

    /* uncomment if you want to see how the question will look like in file
    cout << question.substr(0, delimiterPos + 1) << q.question << q.trueAns << "|"
                 << q.ans1 << "|" << q.ans2 << "|" << q.ans3 << "|" << endl;
    pause();
    */

    changeCategory << question.substr(0, delimiterPos + 1) << q.question << q.trueAns << "|"
                 << q.ans1 << "|" << q.ans2 << "|" << q.ans3 << "|" << "\n";

    changeCategory.close();
    return ;
}
