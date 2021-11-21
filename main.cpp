#include <iostream>

void Menu() {

    int option;

     std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
     std::cout << std::endl << "        Main Menu           " << std::endl;
     std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

     std::cout << std::endl << "Please select an option from 1-5: ";

     std::cin >> option;

     switch (option) {
         case 1:
            std::cout << std::endl << "~~~~~~~~~~~~~~~ 1 ~~~~~~~~~~~~~\n" << std::endl; 
            //Option1();
            break;
         case 2:
            std::cout << std::endl << "~~~~~~~~~~~~~~~ 2 ~~~~~~~~~~~~~\n" << std::endl;
            //Option2();
            break;
         case 3:
            std::cout << std::endl << "~~~~~~~~~~~~~~~ 3 ~~~~~~~~~~~~~\n" << std::endl;
            //Option3();
            break;
         case 4:
            std::cout << std::endl << "~~~~~~~~~~~~~~~ 4 ~~~~~~~~~~~~~\n" << std::endl;
            //Option4();
            break;
         case 5:
            std::cout << std::endl << "~~~~~~~~~~~~~~~ 5 ~~~~~~~~~~~~~\n" << std::endl;
            //Option5();
            break;
         default:
            break;
     }
}

int main() {
    Menu(); // launch menu
    return 0;
}