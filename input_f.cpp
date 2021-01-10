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
* <file input functions>
*
*/

#include "user_input.h"
#include "visual_functions.h"
#include "fuctions.h"

void UserInput (int& userAnswer, const int minValue, const int maxValue, const int center) {
    string invalid;
    invalid = "Enter only numbers between " + to_string(minValue) + " and " + to_string(maxValue) + "!";
    while(true) {
        for (int i = 0; i < center; i++)
            cout << " ";
        cin >> userAnswer;

        if (userAnswer >= minValue && userAnswer <= maxValue)
            break;

        if(center != 0)
            AlignCenter (invalid);
        else AlignLeft (invalid);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return ;
}

bool ChooseLifeline (bool lifelines[], int& userAnswer) {
    string llInput;
    while (true) {
        cin >> llInput;
        if(llInput == "y" || llInput == "Y") {
            NewScreen(31);

            ShowLifelines(lifelines);
            while(true) {
                AlignLeft ("What would you like to use:");
                cin >> userAnswer;
                if (userAnswer == 1 && lifelines[0] == 1) {
                    lifelines[0] = 0;
                    break;
                }
                else if (userAnswer == 2 && lifelines[1] == 1) {
                    lifelines[1] = 0;
                    break;
                }
                else if (userAnswer == 3 && lifelines[2] == 1) {
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
        AlignLeft ("Chose [y] or [n]: ");
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return 1;
}

string WriteAnswer (string text, const string textError, const size_t limitation) {
    string answer;
    while (true) {
        AlignLeft (text);
        getline (cin, answer);

        if (answer.length() < limitation && answer.length() > 1)
            break;

        AlignLeft (textError);

        cin.clear();
    }
    return answer;
}
