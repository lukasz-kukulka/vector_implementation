#include "gtest/gtest.h"

#include <string>
#include <iostream>
#include <initializer_list>

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
    luk::Vector<testClassToVector<std::string>>stringVectorSizeValue = luk::Vector<testClassToVector<std::string>>(500, std::string("TEST"));
    luk::Vector<testClassToVector<std::string>>stringVectorInitList { {"TEST001"}, {"TEST002"}, {"TEST003"}, {"TEST004"}, {"TEST005"}, {"TEST006"}, {"TEST007"} };
};

TEST_F(TestsVectorClass, allValueInIntVectorFromConstructorWithSizeShouldBeZero) {
    auto expect = 0;
    ASSERT_EQ(intVectorSize[0].getValue(), expect);
    ASSERT_EQ(intVectorSize[10].getValue(), expect);
    ASSERT_EQ(intVectorSize[20].getValue(), expect);
    ASSERT_EQ(intVectorSize[49].getValue(), expect);
}

TEST_F(TestsVectorClass, allValueInIntVectorFromConstructorWithSizeShouldBe111) {
    auto expect = 111;
    ASSERT_EQ(intVectorSize[0].getValue(), expect);
    ASSERT_EQ(intVectorSize[33].getValue(), expect);
    ASSERT_EQ(intVectorSize[66].getValue(), expect);
    ASSERT_EQ(intVectorSize[98].getValue(), expect);
}