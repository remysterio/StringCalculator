#ifndef STRINGCOMPLEX_H
#define STRINGCOMPLEX_H

#include<iostream>
#include <vector>

class StringComplex
{
public:
    StringComplex();
    void   run();
    bool   isOperator( const std::string& token);
    bool   isParenthesis( const std::string& token);
    bool   isAssociative( const std::string& token, const int& type);
    int    cmpPrecedence( const std::string& token1, const std::string& token2 );
    double RPNtoDouble( std::vector<std::string> tokens );
    void   infixToRPN( const std::vector<std::string>& inputTokens,
                       const int& size,
                       std::vector<std::string>& strArray );
    std::vector<std::string> getExpressionTokens( const std::string& expression );
};

#endif // STRINGCOMPLEX_H
