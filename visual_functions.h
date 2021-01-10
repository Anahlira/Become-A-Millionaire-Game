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
* <header file with visual functions>
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
//#include <conio.h> //getch() add for windows only

#include "structure.h"

//-----VISUAL FUNCTIONS-----//

void LetterByLetter (const string text, const int time = 0);
void Border (const int characterBorder = 32, const int length = 70);
void BorderC (const int characterBorder = 32, const int characterBorderB = 32, const int characterBorderE = 32, const int length = 68);
void EmptyLines (const int emptyLines = 1, const int characterBorder = 32, const int characterBorderB = 32, const int characterBorderE = 32, const int length = 70);
void NewScreen (const int border = 220);
void AlignCenter (const string text, const int characterBorder1 = 32, const int characterBorder2 = 32, const int time = 0, const int character = 32);
void AlignLeft (const string text, const int characterBorder1 = 32, const int characterBorder2 = 32, const int time = 0, const int character = 32);
void pause(const bool center = true, const string text = "Press any key to continue...");
void WaitUser (const string text, const bool center = 1, const int border = 32);
