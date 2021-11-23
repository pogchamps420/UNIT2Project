#include <iostream>

/**** 
https://en.wikipedia.org/wiki/Caesar_cipher

In cryptography, a Caesar cipher, is one of the simplest and most widely known encryption techniques. 
It is a type of substitution cipher in which each letter in the plaintext is replaced by a letter some fixed number of positions down the alphabet. 
For example, with a left shift of 3, D would be replaced by A, E would become B, and so on. 
The method is named after Julius Caesar, who used it in his private correspondence.
***/

int main()
{
   int option, n; // The user picks if they want encryption/decryption and the shift amount
   std::string message; // Message to be processed
   std::string shift; // Shift amount for the caesar cipher

   std::cout << "Please enter a phrase to be encoded or decoded:\n";
   std::getline(std::cin, message);

   std::cout << "Please specify the shift amount:\n";
   std::cin >> n;

   std::cout << "Type L for Left Shift or R for Right Shift:\n";
   std::cin >> shift;
   
   std::cout << "What would you like to do?\n"; 
   std::cout << "1 = Encryption.\n";
   std::cout << "2 = Decryption.\n";
   std::cin >> option;

   switch(option)
   {
      case 1:
         for(int i = 0; i < message.size(); i++) {
            if(shift == "L") {
              message[i] = message[i] - n; // Left shift letters in message by n
            }
            else if(shift == "R") {
               message[i] = message[i] + n; // Right shift letters in message by n
            }
            else {
               std::cout << "Invalid shift option!\n";
            }
         }

         std::cout << "The encrypted message: " << message;
         break;


      case 2:
         for(int i = 0; i < message.size(); i++) {
            if(shift == "L") {
              message[i] = message[i] - n; // Left shift letters in message by n
            }
            else if(shift == "R") {
               message[i] = message[i] + n; // Right shift letters in message by n
            }
            else {
               std::cout << "Invalid shift option!\n";
            }
         }

         std::cout << "The decrypted message: " << message;
         break;


      default:
         std::cout << "oopsy daisy you dumb motherfucker";
   }
   return 0;
}
