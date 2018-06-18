
#include "Derived.h"

#include "Base.h"
#include <iostream>
#include <string>

Derived::Derived() { }
Derived::~Derived() { }

void Derived::someMethod()
{
  std::cout << "Derived method" << std::endl;
}
