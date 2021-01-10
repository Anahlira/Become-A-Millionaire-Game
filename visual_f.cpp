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
* <file with visual functions>
*
*/
#include "visual_functions.h"

void LetterByLetter(const string text, const int time) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        usleep(time);
    }
    return;
}

void AlignCenter (const string text, const int characterBorder1, const int characterBorder2, const int time, const int character) {
    string text2 = text;
    int length = text.length();
    char st[3];
    st[0] = character;
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    int lastSpace = 0;
    int startPos = 0;
    int rotations = 1;
    bool stop = false;

    text2.clear();
    do {
        if (text.length() / rotations > 66) {   //if the text is more than 70 symbols
            for (int i = 0; i < 67; i++) {
                if(text[startPos + i] == 32) {
                    lastSpace = i + startPos;   //calculate where is the last space
                }                               //before the 70th symbol
            }
            text2 = text.substr (startPos, lastSpace - startPos);
        }
        else {
            text2 = text.substr (lastSpace);
            stop = true;
        }
        length = text2.length();

        //.....display line.....//
        cout << " " <<st[1];

        for (int i = 0; i < (68 - length)/2; i++) {
            cout << st[0];
        }
        LetterByLetter(text2, time);
        for (int i = 0; i < (69 - length)/2; i++) {
            cout << st[0];
        }

        cout << st[2] << endl;
        //......................//

        startPos = lastSpace + 1;
        text2 = text;
        rotations++;

    } while (!stop);
    return;
}

void AlignLeft (const string text, const int characterBorder1, const int characterBorder2, const int time, const int character) {
    int length = text.length();
    char st[3];
    st[0] = character;
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    cout << " " << st[1] << " ";

    LetterByLetter(text, time);
    return;
}

void pause(const bool center, const string text) {
    if(center)
        AlignCenter(text);
    else AlignLeft(text);
    cin.ignore();   //remove for
    cin.get();      //windows and use getch()

    //getch(); //use only for windows
    return;
}

void Border (const int characterBorder, const int length) {
    char st[1];
    st[0] = characterBorder;
    cout << " ";
    for(int i = 0; i < length; i++) {
        cout << st[0];
    }
    cout << endl;
    return;
}

void BorderC (const int characterBorder, const int characterBorderB, const int characterBorderE, const int length) {
    char st[3];
    st[0] = characterBorder;
    st[1] = characterBorderB;
    st[2] = characterBorderE;
    cout << " " << st[1];
    for(int i = 0; i < length; i++) {
        cout << st[0];
    }
    cout << st[2] << endl;
    return;
}

void EmptyLines (const int emptyLines, const int characterBorder, const int characterBorderB, const int characterBorderE, const int length) {
    for(int i = 0; i < emptyLines ; i++) {
        BorderC (32, characterBorderB, characterBorderE, length - 2);
    }
    return;
}

void NewScreen (const int border) {
    system ("CLS");
    Border (border);
    return;
}

void WaitUser (const string text, const bool center, const int border) {
    if (center) {
        AlignCenter(text, border, border);
        Border(border);
    }
    else {
        cout << endl;
        AlignLeft(text, border, border);
        Border(border);
    }
    pause(0, "  ");
    return;
}

