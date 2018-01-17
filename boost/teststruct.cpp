#include <assert.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct base1
{
	int my_val;
	virtual void* GetThis1() = 0;
};

struct base2
{
	virtual void* GetThis() = 0;
};

struct device : base1, base2
{
	void* GetThis() 
	{
		return this;
	}

	void* GetThis1() 
	{
		return this;
	}
};

int main()
{
	device* pd = new device;
	base2* pd2 = pd;
	//printf("%0x %0x\n", pd, pd2);
	//printf("%0x %0x\n", pd->GetThis(), pd2->GetThis());
	cout << pd->GetThis() << " " << pd2->GetThis();

	printf("pass\n");
	return 0;
}
