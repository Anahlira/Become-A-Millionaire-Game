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
* <file with functions for showing question>
*
*/

#include "fuctions.h"
#include "visual_functions.h"

string getAnswers (string line, int& i) {
    string sentance;
    while (line[i] != '|') {
        sentance = sentance + line[i];
        i++;
    }
    return sentance;
}

void CollectQuestion (int i, string line, Question &q) {
    string sentance;
    while (line[i] != '?') {
        sentance = sentance + line[i];
        i++;
    }
    q.question = sentance + "?";

    q.trueAns = getAnswers(line, ++i);
    q.ans1 = getAnswers(line, ++i);
    q.ans2 = getAnswers(line, ++i);
    q.ans3 = getAnswers(line, ++i);
    return;
}

void ShowAnswer (string ans1, string ans2, int characterBorder1, int characterBorder2, int choice1, int choice2) {
    char st[3];
    st[0] = 32; //space
    st[1] = characterBorder1;
    st[2] = characterBorder2;

    if(ans1 == " ") cout << st[1] << st[0] << " " << ans1;  //when the user chose 50/50
    else cout << st[1] << st[0] << choice1<< ")" << ans1;

    for(int i = ans1.length() + 3; i < 34; i++) {
        cout << st[0];
    }
    if(ans2 == " ") cout << " " << ans2;    //when the user chose 50/50
    else cout << choice2 << ")" << ans2;
    for (int i = 35 + ans2.length(); i < 69; i++) {
        cout << st[0];
    }

    cout << st[2] << endl;
    return ;
}

void ShowQuestion (int& trueAnswer, Question &q) {
    BorderC(254, 219, 219);

    AlignCenter(" ", 221, 222);
    AlignCenter(q.question, 221, 222, 50000);   //show the question
    AlignCenter(" ", 221, 222);

    BorderC(223, 223, 223);
    Border();

    trueAnswer = rand() % 4 + 1;

    switch (trueAnswer) {
        case 1:
            ShowAnswer(q.trueAns, q.ans1);
            ShowAnswer(q.ans2, q.ans3, 32, 32, 3, 4);
            break;
        case 2:
            ShowAnswer(q.ans1, q.trueAns);
            ShowAnswer(q.ans2, q.ans3, 32, 32, 3, 4);
            break;                                                //Random right answer place
        case 3:
            ShowAnswer(q.ans2, q.ans1);
            ShowAnswer(q.trueAns, q.ans3, 32, 32, 3, 4);
            break;
        case 4:
            ShowAnswer(q.ans3, q.ans1);
            ShowAnswer(q.ans2, q.trueAns, 32, 32, 3, 4);
            break;
    }
    Border();
    Border(31); //custom border
    Border();
    return;
}
