#include "stringsimple.h"
#include<string>
#include<iostream>
#include<sstream>

#define PLUS  '+'
#define MINUS '-'
#define MULT  '*'
#define DIV   '/'

StringSimple::StringSimple(){}

/* We use the sub string method to calculate the expression
 * When we meet an operand we sub the string into 2 expression
 * We evaluate the expression and we apply the operand
 * We apply recursivity for each expression until we met a final expression without operand
 */
int StringSimple::calculation(std::string expression)
{
    for(int i=expression.length()-2;i>=0;i--)
    {
        switch(expression.at(i))
        {
        case PLUS:
            return (calculation(expression.substr(0,i)) + calculation(expression.substr(i+1,expression.length()-i-1)));
        case MINUS:
            return  calculation(expression.substr(0,i)) - calculation(expression.substr(i+1,expression.length()-i-1));
        case MULT:
            return  calculation(expression.substr(0,i)) * calculation(expression.substr(i+1,expression.length()-i-1));
        case DIV:
            return  calculation(expression.substr(0,i)) / calculation(expression.substr(i+1,expression.length()-i-1));
        }
    }
    /* stoi Convert from string to int */
    return std::stoi(expression);
}
