#include <stringsimple.h>
#include <verification.h>
#include <stringcomplex.h>
#include<iostream>

using namespace std;

int main()
{
    StringComplex i_StringComplex;
    i_StringComplex.run();
    /*
    StringSimple i_StringSimple;
    Verification i_Verification;
    string expression;
    string input_choice;
    bool flag_again{true};

    while(flag_again)
    {
        cout << "Enter an expression with the form \na*b+c-d for example" << endl;
        expression.clear();
        cin >> expression;
        if(!i_Verification.check_expression(expression))
        {
            cerr << "Bad expression" << endl;
            return -1;
        }
        cout << "Result is " << i_StringSimple.calculation(expression) << endl;
        cout << "Do you want to continue ? (y/n)" << endl;
        input_choice.clear();
        cin >> input_choice;
        flag_again = i_Verification.check_command(input_choice);
    }
    return 0;
    */
}
