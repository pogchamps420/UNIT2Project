#include <iostream>

// define
void menu_option_1();
void menu_option_2();
void menu_option_3();
void menu_option_4();
void menu_option_5();

void Menu() {

    int option;

     std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
     std::cout << std::endl << "        Main Menu           " << std::endl;
     std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

     std::cout << std::endl << "Please select an option from 1-5: ";

     std::cin >> option;

     switch (option) {
         case 1:
            menu_option_1();
            //Option1();
            break;
         case 2:
            menu_option_2();
            //Option2();
            break;
         case 3:
            menu_option_3();
            //Option3();
            break;
         case 4:
            menu_option_4();
            //Option4();
            break;
         case 5:
            menu_option_5();
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

void menu_option_1() // option description
{
   std::cout << "~~~~~~~~~~~~~~~ 1 ~~~~~~~~~~~~~\n"; // title

   // actual code

   //back to main menu
   std::string exit = "";
   do {
      std::cout << "Press X to return. ";
      std::cin >> exit;
   } while (exit != "x" && exit != "X");
   Menu(); 
}

void menu_option_2() // option description
{
   std::cout << "~~~~~~~~~~~~~~~ 2 ~~~~~~~~~~~~~\n"; // title

   // actual code

   //back to main menu
   std::string exit = "";
   do {
      std::cout << "Press X to return. ";
      std::cin >> exit;
   } while (exit != "x" && exit != "X");
   Menu(); 
}

void menu_option_3() // option description
{
   std::cout << "~~~~~~~~~~~~~~~ 3 ~~~~~~~~~~~~~\n"; // title

   // actual code

   //back to main menu
   std::string exit = "";
   do {
      std::cout << "Press X to return. ";
      std::cin >> exit;
   } while (exit != "x" && exit != "X");
   Menu(); 
}

void menu_option_4() // option description
{
   std::cout << "~~~~~~~~~~~~~~~ 4 ~~~~~~~~~~~~~\n"; // title

   // actual code

   //back to main menu
   std::string exit = "";
   do {
      std::cout << "Press X to return. ";
      std::cin >> exit;
   } while (exit != "x" && exit != "X");
   Menu(); 
}

void menu_option_5() // option description
{
   std::cout << "~~~~~~~~~~~~~~~ 5 ~~~~~~~~~~~~~\n"; // title

   // actual code

   //back to main menu
   std::string exit = "";
   do {
      std::cout << "Press X to return. ";
      std::cin >> exit;
   } while (exit != "x" && exit != "X");
   Menu(); 
}