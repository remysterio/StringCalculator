#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <iostream>

class Verification
{
public:
    Verification();
    bool check_command(std::string);
    bool check_expression(std::string);
};

#endif // VERIFICATION_H
