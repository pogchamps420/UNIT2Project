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
            //Option1();
            break;
         case 2:
            //Option2();
            break;
         case 3:
            //Option3();
            break;
         case 4:
            //Option4();
            break;
         case 5:
            //Option5();
            break;
         default:
            break;
     }
}

int main() {
    Menu();
    return 0;
}