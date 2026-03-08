#include <iostream>

class A
{
private:
	int m_x;
public:
	A(int x) : m_x{x}
	{
		/*if (x <= 0)
			throw 1; */
	}
};

class B : public A
{
public:
    /*	B(int x) : A{x} 
	{
		
	}*/
    B(int x) try : A{x} 
	{
		if (x <= 0)
			throw 1; 
	}
    catch(...)
    {
        std::cout << "Caught before main.\n";
    }
};

int main()
{
	try
	{
		B b{0};
	}
	catch (int)
	{
		std::cout << "Caught at main.\n";
	}
}