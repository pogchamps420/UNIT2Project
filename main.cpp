#include <iostream>
#include <vector>
#include "menu.h"
#include "menuelement.h"
#include "PD.h"
#include "Tise.h"
#include "eseries.h"
#include "componentmatch.h"
#include "potentialdivider.h"
#include "System.h"
#include "rafal.h"

int main()
{
    //intro title
    System::Clear();
    std::cout << "Welcome to our sandbox\n\Project by Tise Olayinka, Delilah Hague, Rafal Kalisz\nGroup 35\tELEC2645\n" << std::endl;
    System::Sleep(1);
    std::cout << "Press enter to start: ";
    while (std::cin.get() != '\n');

    //Display menu

    while (true)
    {
        System::Clear();

        std::vector<MenuItem> mainItems{};
        std::vector<MenuOption> mainOptions
        {
            MenuOption('T', "Tise's menu"),
            MenuOption('D', "Delilah's menu"),
            MenuOption('R', "Rafal's menu"),
            MenuOption('x', "Exit the application")
        };

        Menu mainMenu("Main Menu", mainOptions, mainItems);
        mainMenu.PrintMenu();
        char chosenOption = mainMenu.ChooseOption();

        T::Tise TMenu;

        switch (chosenOption)
        {
        
        case 'T':
            TMenu.TiseMenu();
            break;
        
        case 'R':
            rafal::Rafal();
            break;
        
        case 'x':
            goto break_main_while;
            break;
        }
    }
break_main_while:;


    

    
    

    // D's stuff - transfer to Tise.cpp
    /*
    std::string expression;
    std::cin >> expression;
    std::string exponent("^");

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

                if (found != std::string::npos) {
                    // do the differentiation
                    std::cout << "It's a power term\n";
                    std::string coeff = expression.substr(0, found);
                    std::cout << coeff << "\n";
                    std::string power = expression.substr(found + 1);
                    std::cout << power << "\n";
                    //std::string new_coeff = coeff * power;
                    //std::cout << new_coeff;

                    double new_coeff = std::stod(coeff);
                    std::cout << typeid(new_coeff).name() << "\n";

                    double new_power = std::stod(power);
                    std::cout << typeid(new_power).name() << "\n";

                    double result = new_coeff * new_power;
                    std::cout << result << "\n";

                    new_power -= 1;
                    std::cout << new_power << "\n";

                    std::cout << result << "x^" << new_power;
                }
                else {
                    std::cout << "It's a term with a linear coefficient\n";

                    //just remove the variable from the term hehe
                    int index = 0;
                    for (int x = 0; x < expression.length(); x++) {
                        if (isdigit(expression[x])) {
                            expression[index] = expression[x];
                            index++;
                        }
                    }

                    std::cout << expression.substr(0, index);
                }
            }
            break;
        }
        // Integration
        case '2': {

            if (is_number(expression)) {
                std::cout << "It's a constant.\n";
                //return the constant plus the variable
                std::cout << expression << "x\n";
            }
            else {
                // it'll be a linear coefficient variable or exponent lol
                std::size_t found = exponent.find(expression);
                found = expression.find("^");

                std::string coeff = expression.substr(0, found);
                std::cout << coeff << "\n";

                double new_coeff = std::stod(coeff);
                std::cout << typeid(new_coeff).name() << "\n";

                if (found != std::string::npos) {
                    std::cout << "It's a power term";
                    // do the integration..
                    std::string power = expression.substr(found + 1);
                    std::cout << power << "\n";
                    //std::string new_coeff = coeff * power;
                    //std::cout << new_coeff;

                    double new_power = std::stod(power);
                    std::cout << typeid(new_power).name() << "\n";

                    new_power += 1;
                    std::cout << new_power << "\n";

                    double result = new_coeff / new_power;
                    std::cout << result << "\n";
                    std::cout << result << "x^" << new_power << "\n";
                }
                else {
                    std::cout << "It's a term with a linear coefficient\n";
                    std::cout << new_coeff / 2 << "x^2";
                }
            }
        }
    default:
        std::cout << "oops";
    } */

    //outro sequence
    std::cout << "\n\nThank you for using our Sandbox\n\Project by Tise Olayinka, Delilah Hague, Rafal Kalisz\nGroup 35\tELEC2645" << std::endl;
    System::Sleep(1);
    std::cout << "\n\tBye <3";
    while (std::cin.get() != '\n');
}