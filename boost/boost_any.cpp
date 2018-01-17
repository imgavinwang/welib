#include <boost/any.hpp> 
#include <iostream> 

using namespace boost;

int main() 
{ 
  any a = 1; 
  std::cout << any_cast<int>(a) << std::endl; 
  a = 3.14; 
  std::cout << any_cast<double>(a) << std::endl; 
  a = true; 
  std::cout << any_cast<bool>(a) << std::endl; 
} 
