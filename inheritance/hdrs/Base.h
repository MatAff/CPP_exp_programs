
#pragma once

class Base {
public:
    Base(int v) {}
    virtual ~Base() {}
    virtual void someMethod()=0;
};
