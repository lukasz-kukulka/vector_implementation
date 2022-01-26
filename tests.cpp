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
    luk::Vector<testClassToVector<std::string>>intVectorSize { luk::Vector<testClassToVector<std::string>>(100) };

};

TEST_F(TestsVectorClass, allValueInIntVectorFromConstructorWithSizeShouldBeZero) {
    auto expect = 0;
    ASSERT_EQ(intVectorSize[0].getValue(), expect);
    ASSERT_EQ(intVectorSize[10].getValue(), expect);
    ASSERT_EQ(intVectorSize[20].getValue(), expect);
    ASSERT_EQ(intVectorSize[49].getValue(), expect);
}