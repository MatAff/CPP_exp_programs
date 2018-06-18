
#include <iostream>

#include "Base.h"
#include "Derived.h"
#include "Factory.h"

// Main program
int main(int argc,char ** argv)
{
    // Assing derived class to base pointer
    Base* b = new Derived();
    b->someMethod();

    // Use factory method
    Base* f = Factory::create("First");
    f->someMethod();

    return 0;
}
