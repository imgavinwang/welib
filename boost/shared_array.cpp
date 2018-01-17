#include <boost/shared_array.hpp> 
#include <iostream> 

int main() 
{ 
  boost::shared_array<int> i1(new int[0]); 
  boost::shared_array<int> i2(i1); 
  i1[0] = 1; 
  i1[1] = 2;
  i1[2] = 3;
  std::cout << i2[2] << std::endl; 
} 