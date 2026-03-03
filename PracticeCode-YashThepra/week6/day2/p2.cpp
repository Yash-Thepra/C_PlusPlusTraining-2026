#include <iostream>

int divint(int, int);  
int main() 
{ 
   int x = 5, y = 2; 
   std::cout << divint(x, y); 
   
   x = 3; y = 0; 
   std::cout << divint(x, y); 
   
   return 0; 
}  

int divint(int a, int b) 
{ 
   return a / b; 
}   

// debugged this program using dgb