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
* <header file containing the main functions>
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

using namespace std;

#include "structure.h"
#include "visual_functions.h"
#include "fuctions.h"
#include "user_input.h"

void NewGame (Question &q, const int topBorder = 220, const int bottomBorder = 223, const int leftBorder = 221, const int rightBorder = 222, const int middleBorder = 219);
void NewQuestion (Question &q, const int topBorder = 220, const int bottomBorder = 223, const int leftBorder = 221, const int rightBorder = 222, const int middleBorder = 219);
void ChangeQuestion (Question &q, const int topBorder = 220, const int bottomBorder = 223, const int leftBorder = 221, const int rightBorder = 222, const int middleBorder = 219);
