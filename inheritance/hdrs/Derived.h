
#pragma once

#include "Base.h"
#include <iostream>
#include <string>

class Derived : public Base {
public:
    Derived(int v);
    ~Derived();
    void someMethod();
};
