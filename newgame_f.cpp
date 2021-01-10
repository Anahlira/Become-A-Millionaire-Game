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
* <new game function>
*
*/

#include "main_functions.h"

void NewGame (Question &q, const int topBorder, const int bottomBorder, const int leftBorder, const int rightBorder, const int middleBorder){

    string line;  //get lines from file
    NewScreen(topBorder);

//.....................................Category...........................................//

    //....Show categories.....//
    BorderC(32, leftBorder, rightBorder);

    int delimiterPos = 0;
    int row = 1;
    fstream categoryAll;
    ShowCategories (row, categoryAll, delimiterPos, false, leftBorder, rightBorder, true);

    BorderC(32, leftBorder, rightBorder);
    Border(bottomBorder);

    //....Select the category....//
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
    if(categoryAll.is_open())
        categoryAll.close();
    //.....................................................................................//

    system("CLS");
    srand((unsigned int)time(NULL)); // for more precise random number

    //....................................New Game.........................................//

    int difficultyLevel = 47;           //47 is "0" in ASCII
    int numberDifficulties = 2;         //how many of one difficulty are in the file
    int showedQuestions[15][1] = {0};   //collects ID's of showed questions
    bool lifelines[3] = {1, 1, 1};      //how many lifelines you have

    int trueAnswer = 0; //the answer witch have to be chosen
    int userAnswer = 0; //user answer

    int ownMoney = 0;   //money you won
    int reward = 0;     //reward for won round

    ifstream categoryFile;
    for (int currentQ = 1; currentQ < 16; currentQ++) {

        NextQuestion (categoryFile, chosedCateggoryN, chosedCategory, row);
        NextDifficulty (currentQ, difficultyLevel);
        Win (reward, currentQ);

        numberDifficulties = DifrentDifficulties(categoryFile, difficultyLevel);


        if (numberDifficulties < 1) { //in case of unfinished category
            categoryFile.close();
            return;
        }

        //............chose the question.............//

        bool foundQuestion = false;                    //tracks if question is chosed
        int randomQuest = rand() % numberDifficulties; //choses one question
        int currentLine = 0;                           //tracks current question

        while (!foundQuestion) {
            randomQuest = rand() % numberDifficulties;
            currentLine = 0;

            if (!categoryFile.is_open()) {
                cout << "An error has occur during the opening of the file!" << endl;
                return;
            }

            while (getline(categoryFile, line)) {
                int quetionDifficulty = line[0];  //gets difficulty of the question

                if (quetionDifficulty == difficultyLevel) {
                    if (currentLine == randomQuest) {
                        int i = 2;
                        while(line[i] != '/') i++;  //reaches the question
                        i++;

                        if (showedQuestions[difficultyLevel-47][0] == randomQuest + 1) { //checks if the question has been showned
                            foundQuestion = false;
                            break;
                        }
                        else foundQuestion = true;  // question is chosed

                        //.......................Question display......................//

                        CollectQuestion(i, line, q);
                        ShowReward(reward, topBorder, leftBorder, rightBorder);
                        ShowQuestion(trueAnswer, q);

                        if (lifelines[0] == 1 || lifelines[1] == 1 || lifelines[2] == 1) { //check if the player have lifelines
                            ShowLifelines (lifelines);
                            AlignLeft ("Would you like to use a lifeline ([y] yes : [n] no): ");

                            if (ChooseLifeline(lifelines, userAnswer)) {
                                ActivateLifeline (userAnswer, difficultyLevel, q);
                                ShowReward (reward);
                                ShowQuestion (trueAnswer, q);
                            }
                        }

                        Border();
                        AlignCenter ("Please enter your answer.(Use only numbers!!)");
                        UserInput (userAnswer);

                        //............................won round..............................//

                        if (userAnswer == trueAnswer) {
                            showedQuestions[difficultyLevel-47][0] = randomQuest + 1;
                            ownMoney = reward;
                            currentLine = 0;

                            NewScreen(topBorder);

                            AlignCenter("Congrats, you won: " + to_string(ownMoney));
                            Border();
                            AlignCenter("Press any key to continue...");

                            Border(bottomBorder);
                            pause(1, " ");
                            system("CLS");

                            break;
                        }

                        //...........................lost game..............................//

                        else {
                            NewScreen(topBorder);
                            EmptyLines(5, 32, leftBorder, rightBorder);

                            AlignCenter ("Unfortunately you lost", leftBorder, rightBorder);
                            AlignCenter ("The true answer was: " + to_string(trueAnswer) + ")" + q.trueAns, leftBorder, rightBorder);
                            AlignCenter ("Reward: " + to_string(ownMoney), leftBorder, rightBorder);

                            EmptyLines(5, 32, leftBorder, rightBorder);
                            Border(bottomBorder);
                            Border();

                            pause(1, "Press any key to return...");

                            if (categoryFile.is_open()) //close the file only if there is one open
                                categoryFile.close();
                            return;
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

    NewScreen(topBorder);
    EmptyLines(5, 32, leftBorder, rightBorder);

    AlignCenter("You won the game!!!", leftBorder, rightBorder);
    string rewardSt;
    rewardSt = "Reward: " + to_string(ownMoney);
    AlignCenter(rewardSt, leftBorder, rightBorder);

    EmptyLines(5, 32, leftBorder, rightBorder);

    Border(bottomBorder);
    BorderC(32, leftBorder, rightBorder);
    pause(1, "Press any key to return to main menu...");
    if(categoryFile.is_open())
        categoryFile.close();
    return;
}
