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
* <header file with secondary functions>
*
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // rand
#include <unistd.h> // sleep
#include <ctime>    //srand
#include <limits>   //numeric_limits<streamsize>::max()

#include "structure.h"

using namespace std;

void ShowCategories(int& row, fstream& categoryAll, int& delimiterPos, const bool closeFile = true, const int leftBorder = 221, const int rightBorder = 222, const bool finalOption = false);
int DifrentDifficulties (ifstream& category, int currentHardnesL);
string getAnswers (string line, int& i);
void CollectQuestion(int i, string line, Question &q);
void ShowAnswer (string ans1, string ans2, int characterBorder1 = 32, int characterBorder2 = 32, int choice1 = 1, int choice2 = 2);
void ShowQuestion (int& trueAnswer, Question &q);

void NextQuestion (ifstream& categoryFile, int chosedCategoryN, string& chosedCategory, int row);
void NextDifficulty (int question, int& difficulty);

void Win (int& reward, const int question);
void ShowReward (const int reward, const int characterBorderTop = 220, const int characterBorderL = 221, const int characterBorderR = 222);

void ShowLifelines (bool lifelines[]);
int GuessTheAnsewer (int difficulty);
void ActivateLifeline (int userAnswer, int difficulty, Question &q);

