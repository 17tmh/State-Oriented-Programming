#include <iostream>

class MyClass
{
public:
    // Default constructor
    MyClass();

    // Second constructor with parameters
    MyClass(int value);
};

// Definition of default constructor
MyClass::MyClass()
{
    // Your default constructor code here
    std::cout << "Default constructor called." << std::endl;
}

// Definition of second constructor
MyClass::MyClass(int value)
{
    // Your second constructor code here
    std::cout << "Parameterized constructor called with value: " << value << std::endl;
}

int main()
{
    MyClass obj1;     // Creating an object using default constructor
    MyClass obj2(10); // Creating an object using second constructor with parameter
    return 0;
}
