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
* <header file with input functions>
*
*/

#pragma once

#include <iostream>
#include <string>
#include <limits>   //numeric_limits<streamsize>::max()

using namespace std;

void UserInput (int& userAnswer, const int minValue = 1, const int maxValue = 4, const int center = 35);
bool ChooseLifeline (bool lifelines[], int& userAnswer);
string WriteAnswer (string text = "Enter true answer: ", const string errorText = "You didn't write the answer within the limitation!\n", const int limitation = 38);
