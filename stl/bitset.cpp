#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	bitset<8> b;
	cout  << "b = " << b << endl;
	cout << "b.set(1) = " << b.set(1) << endl;
	cout << "b.any() = " << b.any() << endl;
	cout << "b.none() = " << b.none() << endl;
	cout << "b.size() = " << b.size() << endl;
	cout << "b.test(1) = " << b.test(1) << endl;
	cout << "b.test(2) = " << b.test(2) << endl;
	cout << "b.to_ulong() = " << b.to_ulong() << endl;
	cout << "b.to_string() = " << b.to_string() << endl;
}