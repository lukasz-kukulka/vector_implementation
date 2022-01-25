#include "gtest/gtest.h"

#include <string>
#include <iostream>

#include "Vector.hpp"

class testClassToVector {
public:
    testClassToVector(int value) : value_(value) 
    {
    }

    int getValue() { return value_; }

private:
    int value_ { };
};

struct TestsVectorClass : public ::testing::Test {

};