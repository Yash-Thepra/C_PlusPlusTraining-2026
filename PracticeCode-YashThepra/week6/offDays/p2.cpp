#include <iostream>

class ArrayException : public std::exception
{
    std::string errorMsg;
public:
    ArrayException(std::string msg) : errorMsg(msg)
    {
    }
    /*const std::string getError() const
    {
        return errorMsg;
    }*/
    const char* what() const noexcept 
    {
        return errorMsg.c_str();
    }
};

class intArray
{
    int m_data[3];
public:
    const int getLength() const
    {
        return 3;
    }
    int& operator[](const int index)
	{
		if (index < 0 || index >= getLength())
			throw ArrayException{ "Invalid index" };

		return m_data[index];
	}
};

int main()
{
    intArray array;
    try
    {
        int value = array[5];
    }
    catch(const ArrayException &e)
    {
        std::cout << "Error: " << /*e.getError()*/ e.what() << "\n";
    }
    catch(const std::exception &e)
    {
        std::cout << "Error: " << /*e.getError()*/ e.what() << "\n";
    }
}