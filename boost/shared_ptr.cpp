#include <boost/shared_ptr.hpp> 
#include <vector> 
#include <iostream>

int main() 
{ 
  std::vector<boost::shared_ptr<int> > v; 
  v.push_back(boost::shared_ptr<int>(new int(1))); 
  v.push_back(boost::shared_ptr<int>(new int(2))); 

  for(std::vector<boost::shared_ptr<int> >::iterator it = v.begin(); it != v.end(); it++) {
  	std::cout << **it << std::endl;
  }
} 
