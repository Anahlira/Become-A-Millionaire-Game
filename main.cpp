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
* <main file>
*
*/


#include "main_functions.h"
#include "visual_functions.h"
#include "user_input.h"
#include "fuctions.h"
#include "structure.h"




int main() {
    Question q;
    const int topBorder = 220;
    const int bottomBorder = 223;
    const int leftBorder = 221;
    const int rightBorder = 222;
    const int middleBorder = 219;

//.....................................Main menu..........................................//

    int choice = 0;

    while (true) {
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
                NewGame(q, topBorder, bottomBorder, leftBorder, rightBorder, middleBorder);
                break;
            case 2:
                NewQuestion(q, topBorder, bottomBorder, leftBorder, rightBorder, middleBorder);
                break;
            case 3:
                ChangeQuestion(q, topBorder, bottomBorder, leftBorder, rightBorder, middleBorder);
                break;
            case 4:
                return 0;
                break;
        }
    }
    return 0;
}

