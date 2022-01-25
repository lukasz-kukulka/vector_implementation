#include "gtest/gtest.h"

#include <string>
#include <iostream>

#include "Vector.hpp"

template <typename Type>
class testClassToVector {
public:
    testClassToVector(Type value) : value_(value) 
    {
    }

    Type getValue() { return value_; }

private:
    Type value_ { };
};

struct TestsVectorClass : public ::testing::Test {
    luk::Vector<testClassToVector<int>>intVectorEmpty;

};