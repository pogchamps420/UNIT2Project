#include <iostream>

int main()
{
   int option, n;
   string message;
   string shift;

   std::cout << "Please enter a phrase to be encoded or decoded:\n";
   getline(std::cin, message);

   std::cout << "Please specify the shift amount:\n";
   std::cin << n;

   std::cout << "Type L for Left Shift or R for Right Shift:\n";
   std::cin << shift;
   
   std::cout << "What would you like to do? :\n"; 
   std::cout << "1 = Encryption.\n";
   std::cout << "2 = Decryption.\n";
   std::cin >> option;

   switch(option)
   {
      case 1:
         for(int i = 0; i < message.size(); i++)
            if(shift == "L") {
              message[i] = message[i] - n;
            }
            else if(shift == "R") {
               message[i] = message[i] + n;
            }
            else {
               std::cout << "Invalid shift option!\n";

         std::cout << "The encrypted message: " << message;
         break;


      case 2:
        for(int i = 0; i < message.size(); i++)
            if(shift == "L") {
              message[i] = message[i] - n;
            }
            else if(shift == "R") {
               message[i] = message[i] + n;
            }
            else {
               std::cout << "Invalid shift option!\n";

         std::cout << "The decrypted message: " << message;
         break;


      default:
         std::cout << "oopsy daisy you dumb motherfucker";
   }
   return 0;
}
