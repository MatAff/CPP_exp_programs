
#include "Derived.h"

#include "Base.h"
#include <iostream>
#include <string>

Derived::Derived(int v) : Base(v) { } 
Derived::~Derived() { }

void Derived::someMethod()
{
  std::cout << "Derived method" << std::endl;
}
