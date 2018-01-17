#include <vector> 
#include <iostream>
#include <memory>

using namespace std;

int main() 
{ 
  vector<shared_ptr<int> > v; 
  v.push_back(shared_ptr<int>(new int(1))); 
  v.push_back(shared_ptr<int>(new int(2))); 

  for(vector<shared_ptr<int> >::iterator it = v.begin(); it != v.end(); it++) {
  	cout << **it << endl;
  }
} 
