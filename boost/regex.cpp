#include <boost/regex.hpp> 
//#include <locale> 
#include <iostream> 

int main() 
{ 
  //std::locale::global(std::locale("German")); 
  std::string s = "helloworld"; 
  boost::regex expr("\\w+\\s\\w+"); 
  std::cout << boost::regex_match(s, expr) << std::endl; 
} 