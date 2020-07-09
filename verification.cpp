#include "verification.h"

using namespace std;

Verification::Verification(){}

bool Verification::check_command(string choice)
{
    /* Check the input command (y/n)  */
    while(true)
    {
        switch(toupper(choice.at(0)))
        {
            case 'Y':
                return true;
            case 'N':
                return false;
            default:
            {
                cout << "Not handled, please retry command (y/n)" << endl;
                choice.clear();
                cin >> choice;
            }
        }
     }
}

bool Verification::check_expression(string expression)
{
    string operater {"+-*/"};
    string digits   {"0123456789"};

    /* Check if 2 operators are next to each other */
    for(unsigned int i = 0; i < expression.length(); i++)
        if(operater.find(expression.at(i)) != string::npos)
            if(operater.find(expression.at(i+1)) != string::npos)
                return false;

    /* Check if there is an unknown character in the string */
    for(unsigned int i = 0; i < expression.length(); i++)
        if(operater.find(expression.at(i)) == string::npos && \
           digits.find(expression.at(i))   == string::npos)
                return false;

    return true;
}
