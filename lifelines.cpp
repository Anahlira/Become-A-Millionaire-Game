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
* <file with functions for lifeline>
*
*/

#include "fuctions.h"
#include "visual_functions.h"

void ShowLifelines (bool lifelines[]){
    AlignLeft ("Available lifeline: ");
    Border();
    if (lifelines[0]) {
        AlignLeft ("[1] 50/50");
        cout << endl;
    }
    if (lifelines[1]) {
        AlignLeft ("[2] Call your friend");
        cout << endl;
    }
    if (lifelines[2]) {
        AlignLeft ("[3] Help from the audience");
        cout << endl;
    }
    Border();
    return;
}

int GuessTheAnsewer(int difficulty) {
    int random = rand() % 100 + 1; //percent
    difficulty = difficulty - 47; //difficulty from 0 to 10

    if (difficulty >=0 && difficulty < 3) { //easy
        if(random > 0 && random < 81)
            return 4;
        else return rand() % 3 + 1;
    }
    else  if (difficulty >=4 && difficulty < 6) { //middle
        if(random > 0 && random < 61)
            return 4;
        else return rand() % 3 + 1;
    }
    else {
        if(random > 0 && random < 31)   //hard
            return 4;
        else return rand() % 3 + 1;
    }
}

void ActivateLifeline (int userAnswer, int difficulty, Question &q){

    string friendName = "My friend";
    int random = rand() % 3 + 1;
    int randomP = 0;    //to save the first eliminated answer (50/50)

    int helpAnswer = GuessTheAnsewer(difficulty);
    string answer;
    if (helpAnswer == 1) answer = q.ans1;
    else if (helpAnswer == 2) answer = q.ans2;
    else if (helpAnswer == 3) answer = q.ans3;
    else answer = q.trueAns;

    switch(userAnswer) {
        case 1:
            for(int i = 0; i < 2; i++) {
                if (random == 1)
                    q.ans1 = " ";
                if (random == 2)
                    q.ans2 = " ";
                if (random == 3)
                    q.ans3 = " ";
                randomP = random;
                random = rand() % 3 + 1;
                while(random == randomP) {
                    random = rand() % 3 + 1;
                }
            }
            system("CLS");
            break;

        case 2:
            NewScreen(220);
            AlignLeft("Who do you wanna call: ", 32);
            cin.ignore();
            getline(cin, friendName);
            NewScreen();
            AlignCenter("Calling " + friendName);
            AlignCenter(". . . . .", 32, 32, 300000);

            NewScreen(220);
            BorderC(32, 221, 222);
            AlignCenter("Pres any key to continue the conversation.", 221, 222);
            BorderC(32, 221, 222);
            Border(223);

            WaitUser(friendName + ": Hello? What's up? Need help?", 0);
            WaitUser("Yes. " + q.question, 0);
            WaitUser(friendName + ": Just... Let me think for a second.", 0);
            Border();
            AlignLeft("Waiting...", 32, 32, 80000);
            Border();
            WaitUser(friendName + ": Ok, I think it is " + answer, 0);
            system("CLS");
            Border();
            AlignCenter(friendName + " thinks the true answer is " + answer);
            break;

        case 3:

            //....percentage of the vote....//
            string a,b,c,d;
            a = q.trueAns;
            b = q.ans1;
            c = q.ans2;
            d = q.ans3;
            switch (rand() % 4 + 1) {
            case 1:
                a = q.ans1;
                b = q.trueAns;
                break;
            case 2:
                a = q.ans2;
                c = q.trueAns;
                break;
            case 3:
                a = q.ans3;
                d = q.trueAns;
                break;
            case 4://to keep the first values
                break;
            }
            string answerS[4] = {a, b, c, d};

            int percentage = 0;
            int usePr[3];
            size_t longestAns = 0;
            int randMax = 0;

            for (int j = 0; j < 4; j++) {
                if (answerS[j].length() > longestAns)
                    longestAns = answerS[j].length();
            }

            //....percentage of the vote....//
            if (difficulty < 4) {
                percentage = rand() % 12 + 15;
            }
            else percentage = rand() % 3 + 15;
            randMax = 31 - percentage;

            usePr[0] = rand() % randMax/2 + 1;
            randMax = randMax - usePr[0];

            if(randMax > 0) {
                usePr[1] = rand() % randMax + 1;
                randMax = randMax - usePr[1];
                if (randMax > 0) {
                    usePr[2] = rand() % randMax + 1;
                }
                else usePr[2] = 0;
            }
            else  usePr[1] = 0;

            //-------- show pow lines----------//
            system("CLS");
            AlignLeft("         Audience poll"); //spaces are for visuals
            Border();
            Border();
            int z = 0;

            for(int j = 0; j < 4; j++) {
                if(answerS[j] == answer) {
                    cout << answer << ": ";
                    for(size_t i = answer.length(); i < longestAns; i++)
                        cout << " ";

                    Border(220, percentage);
                }
                else {
                    cout << answerS[j] << ": ";
                    for(size_t i = answerS[j].length(); i < longestAns; i++)
                        cout << " ";

                    Border(220, usePr[z]);
                    z++;
                }
            }
            //----------------------------------//
            Border();
            break;
        }

    return;
}

