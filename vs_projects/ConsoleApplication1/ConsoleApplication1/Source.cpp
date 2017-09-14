#include<iostream>
using namespace std;

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */




struct MixedData
{
	char Data1;
	int Data3;
	short Data2;
	char Data4;
};

#pragma pack(pop)   /* restore original alignment from stack */

class Foo {
public:
	Foo() { cout << "constructor 1\n"; }
	Foo(Foo &b) {
		cout << "constructor 2\n";
	}
	Foo & operator=(Foo &b) {
		cout << "=\n";
	}
};


void main()
{
	Foo a;
	Foo b = a;
}