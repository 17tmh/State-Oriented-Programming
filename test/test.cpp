#include <iostream>

class MyClass
{
public:
    void memberFunction(int x)
    {
        std::cout << "Inside memberFunction: " << x << std::endl;
    }
};

// Regular function that mimics the behavior of MyClass::memberFunction
void regularFunction(int x)
{
    std::cout << "Inside regularFunction: " << x << std::endl;
}

int main()
{
    // Create an object of MyClass
    MyClass obj;

    // Pointer to member function of MyClass
    void (MyClass::*memberFunctionPtr)(int) = &MyClass::memberFunction;

    // Call member function through object
    (obj.*memberFunctionPtr)(10); // Output: Inside memberFunction: 10

    // Cast member function pointer to regular function pointer
    // Note: This is not safe and may lead to undefined behavior
    void (*regularFunctionPtr)(int) = reinterpret_cast<void (*)(int)>(&regularFunction);

    // Call regular function (incorrect usage, may lead to undefined behavior)
    regularFunctionPtr(20); // Output: Inside regularFunction: 20

    return 0;
}
