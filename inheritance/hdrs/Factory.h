
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
            Derived* d = new Derived();
            return d;
        }
        return NULL;
    }
};
