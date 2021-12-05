#include "buckboost.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <string>

/* Non - linear variables relating to buck / boost converters are the inductor voltage,
*  inductor selection, capacitor selection, peak to peak output voltage ripple and change in charge
*/

//see if that mf is a constant

bool is_number(const std::string& word) {
    return !word.empty() && std::all_of(word.begin(), word.end(), ::isdigit);
}

int main() {

    /*if (is_number("2")) {
        std::cout << "Nice" << std::endl;
        assert(is_number("2"));
    }*/

    std::string expression;
    std::cin >> expression;
    std::string exponent("^");

    // fuck fuck fuck ok we will implement the differentiation AND integration here
    // why doesnt c++ have calculus in the math library lol
    //let's just do switch/case...

    //we need to account for calculus with a constant and of variables with exponents..
    //first we should check if it is a constant using isdigit lmao

    char Calculus;
    std::cout << "Please enter 1 for Differentiation or 2 for Integration: ";
    std::cin >> Calculus;

    switch (Calculus) {
        // Differentiation
        case '1': {
            if (is_number(expression)) {
                //std::cout << "It's a constant.\n";
                std::cout << "0";
            }
            else {
                // it'll be a variable or exponent lol
                std::size_t found = exponent.find(expression);
                found = expression.find("^");

                if (found) {
                    std::cout << "It's a power term";
                    // do the differentiation

                }
                else {
                    std::cout << "It's a term with a linear coefficient";
                    //just remove the variable from the term hehe
                }
            }
            break;
        }
        // Integration
        case '2': {
            
            if (is_number(expression)) {
                std::cout << "It's a constant.";
                //return the constant plus the variable
            }
            else {
                // it'll be a linear coefficient variable or exponent lol
                std::size_t found = exponent.find(expression);
                found = expression.find("^");

                if (found) {
                    std::cout << "It's a power term";
                    // do the integration..
                    std::cout << "First occurrence is " << found << std::endl;
                }
                else {
                    std::cout << "It's a term with a linear coefficient";
                    //raise the power & divide by new power lol
                }
            }
        }
        default:
            std::cout << "oops";
    }
}






