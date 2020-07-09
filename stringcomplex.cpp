#include "stringcomplex.h"
#include <sstream>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

#define NB_OPERAND 5


/*
 * Modify from https://www.technical-recipes.com/2011/a-mathematical-expression-parser-in-java-and-cpp/
 */

struct operator_t
{
    std::string  operandValue;
    int operandPrecedence;
    int operandAssoc;
};

const int LEFT_ASSOC  {0};
const int RIGHT_ASSOC {0};
const operator_t PLUS  {"+",2,LEFT_ASSOC};
const operator_t MINUS {"-",2,LEFT_ASSOC};
const operator_t MULT  {"*",3,LEFT_ASSOC};
const operator_t DIV   {"/",3,LEFT_ASSOC};
const operator_t EXP   {"^",4,RIGHT_ASSOC};
const operator_t op_list[NB_OPERAND] {PLUS, MINUS, MULT, DIV, EXP};

// Test if token is an pathensesis
bool StringComplex::isParenthesis( const std::string& token)
{
    return token == "(" || token == ")";
}

// Test if token is an operator
bool StringComplex::isOperator( const std::string& token)
{
    return token == "+" || token == "-" ||
           token == "*" || token == "/";
}

// Test associativity of operator token
bool StringComplex::isAssociative( const std::string& token, const int& type)
{
    for(int i = 0; i < NB_OPERAND; i++)
        if(token == op_list[i].operandValue)
            if(type == op_list[i].operandAssoc)
                return true;
    return false;
}

// Test precedence of operators.
int StringComplex::cmpPrecedence( const std::string& token1, const std::string& token2 )
{
    int prec1, prec2;
    for(int i = 0; i < NB_OPERAND; i++)
    {
        if(token1 == op_list[i].operandValue)
            prec1 = op_list[i].operandPrecedence;
        if(token2 == op_list[i].operandValue)
            prec2 = op_list[i].operandPrecedence;
    }
    return prec1 - prec2;
}

// Convert from Infix to RPN Expression
void StringComplex::infixToRPN( const std::vector<std::string>& inputTokens,
                                const int& size,
                                std::vector<std::string>& outputTokens )
{
    std::list<std::string> out;
    std::stack<std::string> stack;

    // Read all the tokens
    for ( int i = 0; i < size; i++ )
    {
        // token reading
        const std::string token = inputTokens[ i ];


        if ( isOperator( token ) )
        {
            // While there is an operator token, o2, at the top of the stack
            // AND ( either o2 has greater precedence
            //      OR o2 has equal precedence and o1 is left associative,
            // AND o1 has precedence less than that of o2,
            const std::string o1 = token;

            if ( !stack.empty() )
            {
                std::string o2 = stack.top();


                while ( isOperator( o2 ) &&
                        ( ( isAssociative( o1, LEFT_ASSOC ) &&  cmpPrecedence( o1, o2 ) == 0 ) ||
                        ( cmpPrecedence( o1, o2 ) < 0 ) ) )
                {
                    // pop o2 off the stack, onto the output queue;
                    stack.pop();
                    out.push_back( o2 );

                    if ( !stack.empty() )
                        o2 = stack.top();
                    else
                        break;
                }
            }

            // push o1 onto the stack.
            stack.push( o1 );
        }

        else if ( token == "(" )
            // Push token to top of the stack
            stack.push( token );

        else if ( token == ")" )
        {
            // Until the token at the top of the stack is a left parenthesis,
            // pop operators off the stack onto the output queue.
            std::string topToken  = stack.top();

            while ( topToken != "(" )
            {
                out.push_back(topToken );
                stack.pop();

                if ( stack.empty() ) break;
                topToken = stack.top();
            }

            // Pop the left parenthesis from the stack, but not onto the output queue.
            if ( !stack.empty() )
                stack.pop();
        }

        // If the token is a number, then add it to the output queue.
        else
            out.push_back( token );
    }

    // While there are still operator tokens in the stack:
    while ( !stack.empty() )
    {
        const std::string stackToken = stack.top();
        out.push_back( stackToken );
        stack.pop();
    }


    outputTokens.assign( out.begin(), out.end() );
    for (auto i = outputTokens.begin(); i != outputTokens.end(); ++i)
        std::cout << *i << ' ';
}

// Convert a string to a vector of string
std::vector<std::string> StringComplex::getExpressionTokens( const std::string& expression )
{
    std::vector<std::string> tokens;
    std::string str = "";

    for ( unsigned int i = 0; i < expression.length(); i++ )
    {
        const std::string token( 1, expression[ i ] );

        if ( isOperator( token ) || isParenthesis( token ) )
        {
            if ( !str.empty() )
            {
               tokens.push_back( str ) ;
            }
            str = "";
            tokens.push_back( token );
        }
        else
        {
            // Append the numbers
            if ( !token.empty() && token != " " )
            {
                str.append( token );
            }
            else
            {
                if ( str != "" )
                {
                    tokens.push_back( str );
                    str = "";
                }
            }
        }
    }
    return tokens;
}

// Calcul the value of the RPN Expression
double StringComplex::RPNtoDouble( std::vector<std::string> tokens )
{
    std::stack<std::string> st;

    // For each token
    for ( int i = 0; i < (int) tokens.size(); ++i )
    {
        const std::string token = tokens[ i ];

        // If the token is a value push it onto the stack
        if ( !isOperator(token) )
        {
            st.push(token);
        }
        else
        {
            double result =  0.0;

            // Token is an operator: pop top two entries
            const std::string val2 = st.top();
            st.pop();
            const double d2 = strtod( val2.c_str(), NULL );

            if ( !st.empty() )
            {
                const std::string val1 = st.top();
                st.pop();
                const double d1 = strtod( val1.c_str(), NULL );

                //Get the result
                result = token == "+" ? d1 + d2 :
                         token == "-" ? d1 - d2 :
                         token == "*" ? d1 * d2 :
                                        d1 / d2;
            }
            else
            {
                if ( token == "-" )
                    result = d2 * -1;
                else
                    result = d2;
            }
            // Push result onto stack
            std::ostringstream s;
            s << result;
            st.push( s.str() );
        }
    }

    return strtod( st.top().c_str(), NULL );
}

// System call
void StringComplex::run()
{
    std::string s = "( 1 + 2) * ( 3 / 4 )-(5+6)";
    std::vector<std::string> tokens;
    std::vector<std::string> rpn;
    double result;

    tokens =  = getExpressionTokens( s );
    infixToRPN( tokens, tokens.size(), rpn );
    result = RPNtoDouble( rpn );
    std::cout << "Result = " << result << std::endl;
}

StringComplex::StringComplex(){}
