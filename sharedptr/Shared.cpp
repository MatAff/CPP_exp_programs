#include <vector>
#include <memory>
#include <iostream>

class Base
{
public:
    Base() { }
    ~Base () { }
    void virtual action()=0;
};

class Derived : public Base
{
public:
    Derived() { }
    ~Derived() { }
    void action() { std::cout << "Action!" << std::endl; }
};

int main()
{
    // Create vector
    std::vector<std::shared_ptr<Base*> > vec;

    // Loop to create objects
    for(size_t i = 0; i < 3; ++i) {
        std::shared_ptr<Base*> ptr = std::make_shared<Base*>(new Derived());
        vec.push_back(ptr);

    }

    // Loop to use object (that without the shared pointer would have gone out of scope)
    for(std::shared_ptr<Base*> e : vec) {
        Base* b = *e;
        b->action();
    }

}

// Compile using: g++ Shared.cpp -o Shared

/* Questions
1. Is this the correct use of shared pointers?
2. std::shared_ptr<Base*> seems to indicate a shared pointer of a pointer. Is this
level of pointyness needed? We can use Base as action is a virtual method, right?
3. The references to the objects created in the first loop would have gone out of
scope without the shared pointers, right? How was this dealt with before the intro-
duction of smart pointers?
*/
