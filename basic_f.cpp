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
* <file with helpful functions>
*
*/
#pragma once

#include "fuctions.h"
#include "visual_functions.h"

void ShowCategories(int& row, fstream& categoryAll, int& delimiterPos, const bool closeFile, const int leftBorder, const int rightBorder, const bool finalOption) {
    categoryAll.open("AllCategories.txt", ios::in);
    if(!categoryAll.is_open()) {
        AlignCenter("Error with the opening of the file...");
        pause(1, "Press any key to return to the main menu");
        return;
    }

    string rowLine;
    string line;
    while (getline(categoryAll, line)) {
        delimiterPos = line.find("/");
        rowLine = to_string(row) + "." + line.substr(delimiterPos + 1);
        AlignCenter(rowLine, leftBorder, rightBorder);
        row++;
    }
    if (finalOption) { // used only for main menu
        rowLine = to_string(row) + ".All Categories";
        AlignCenter(rowLine, leftBorder, rightBorder);
    }

    categoryAll.clear();
    categoryAll.seekg(0);
    if(closeFile)
        categoryAll.close();
    return;
}

//calculates how many of one difficulty level is in the file
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

    if(numHardnesses < 1) { //in case there is not full category
            cout << "Upss... It seems that you did't finish a category" << endl;
            cout << "Please finish your category, it should have at least 2 questions from every difficulty level." << endl;
            cout << "This message will continue to show, until you complete your category!" << endl;
            cout << "Hope you make a lot of money next time!" << endl;
            system ("pause");
        }

    return numHardnesses;
}

void NextQuestion (ifstream& categoryFile, int chosedCategoryN, string& chosedCategory, int row) {
    NewScreen(32);

    //chose random category
    if (chosedCategoryN == row) {
        if (categoryFile.is_open())
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
    if (question == 2 || question == 4 || question == 11 || question == 13 || question == 15) {
        return ;    //stays the same difficylty
    }
    else difficulty++;
    return;
}

void Win (int& reward, const int question) {
    if (question == 5) {
        reward = 1000;
        return ;
    }

    if (question == 12){
        reward = 125000;
        return ;            //calculates the reward
    }

    if (question > 5){
        reward = reward*2;
        return ;
    }

    reward = reward + 100;
    return;
}

void ShowReward (const int reward, const int characterBorderTop, const int characterBorderL, const int characterBorderR) {
    Border(characterBorderTop);
    AlignCenter(" ", characterBorderL, characterBorderR);
    AlignCenter("Reward for the round: " + to_string(reward), characterBorderL, characterBorderR);
    AlignCenter(" ", characterBorderL, characterBorderR);
    return;
}
