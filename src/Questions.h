//
//  questions.h
//

#ifndef QUESTIONS_h
#define QUESTIONS_h

#include <string>
using namespace std;

class Questions{
public:
    //
    // Variables
    //
    string question = "";   // Question
    string options[4];      // Options
    int rightChoose = 0;    // Right choose
    int optionsType = 0;    // 0: Ask name | 1: Ask year | 2: Ask

    //
    // Constructors
    //
    Questions(){}
    Questions(string q, int r){
        question = q;       // Set question
        rightChoose = r;    // Set right answer
    }

    //
    // Set options variables
    //
    void createOptions(string a, string b, string c, string d){
        options[0] = a;
        options[1] = b;
        options[2] = c;
        options[3] = d;
    }
};
#endif /* questions_h */
