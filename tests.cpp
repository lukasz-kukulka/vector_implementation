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
    luk::Vector<testClassToVector<int>>intVectorSize { luk::Vector<testClassToVector<int>>(50) };
    luk::Vector<testClassToVector<int>>intVectorSizeValue { luk::Vector<testClassToVector<int>>(99, 111) };
    luk::Vector<testClassToVector<int>>intVectorInitList { luk::Vector<testClassToVector<int>>({222, 223, 224, 225, 226, 227, 228, 229, 230, 231})};
};