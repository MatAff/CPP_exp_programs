
#pragma once

#include <string>
#include "Base.h"
#include "Derived.h"

class Factory {

public:
    static Base* create(std::string derivedName)
    {
        if (derivedName=="First")
        {
            Derived* d = new Derived(1);
            return d;
        }
        return NULL;
    }
};
