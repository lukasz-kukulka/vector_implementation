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
    luk::Vector<testClassToVector<std::string>>stringVectorEmpty;
    luk::Vector<testClassToVector<std::string>>stringVectorSizeValue = luk::Vector<testClassToVector<std::string>>(500, std::string("TEST"));
    luk::Vector<testClassToVector<std::string>>stringVectorInitList { {"TEST001"}, 
                                                                      {"TEST002"}, 
                                                                      {"TEST003"}, 
                                                                      {"TEST004"}, 
                                                                      {"TEST005"}, 
                                                                      {"TEST006"}, 
                                                                      {"TEST007"} , 
                                                                      {"TEST008"}, 
                                                                      {"TEST009"}, 
                                                                      {"TEST0010"}};
};


// check constructors

TEST_F(TestsVectorClass, callIntVectorCapacityShouldBeZero) {
    auto expect = 0;
    ASSERT_EQ(intVectorEmpty.capacity(), expect);
}

TEST_F(TestsVectorClass, callStringVectorCapacityShouldBeZero) {
    auto expect = 0;
    ASSERT_EQ(stringVectorEmpty.capacity(), expect);
}

TEST_F(TestsVectorClass, callIntVectorSizeShouldBeZero) {
    auto expect = 0;
    ASSERT_EQ(intVectorEmpty.size(), expect);
}

TEST_F(TestsVectorClass, callStringVectorSizeShouldBeZero) {
    auto expect = 0;
    ASSERT_EQ(stringVectorEmpty.size(), expect);
}

TEST_F(TestsVectorClass, callIntVectorCapacityShouldBe50) {
    auto expect = 50;
    ASSERT_EQ(intVectorSize.capacity(), expect);
}

TEST_F(TestsVectorClass, callIntVectorSizeShouldBe50) {
    auto expect = 50;
    ASSERT_EQ(intVectorSize.size(), expect);
}

TEST_F(TestsVectorClass, allValueInIntVectorFromConstructorWithSizeShouldBeZero) {
    auto expect = 0;
    ASSERT_EQ(intVectorSize[0].getValue(), expect);
    ASSERT_EQ(intVectorSize[10].getValue(), expect);
    ASSERT_EQ(intVectorSize[20].getValue(), expect);
    ASSERT_EQ(intVectorSize[49].getValue(), expect);
}

TEST_F(TestsVectorClass, callIntVectorCapacityShouldBe99) {
    auto expect = 99;
    ASSERT_EQ(intVectorSizeValue.capacity(), expect);
}

TEST_F(TestsVectorClass, callIntVectorSizeShouldBe99) {
    auto expect = 99;
    ASSERT_EQ(intVectorSizeValue.size(), expect);
}

TEST_F(TestsVectorClass, allValueInIntVectorFromConstructorWithSizeShouldBe111) {
    auto expect = 111;
    ASSERT_EQ(intVectorSizeValue[0].getValue(), expect);
    ASSERT_EQ(intVectorSizeValue[33].getValue(), expect);
    ASSERT_EQ(intVectorSizeValue[66].getValue(), expect);
    ASSERT_EQ(intVectorSizeValue[98].getValue(), expect);
}

TEST_F(TestsVectorClass, callIntVectorCapacityShouldBe10) {
    auto expect = 10;
    ASSERT_EQ(intVectorInitList.capacity(), expect);
}

TEST_F(TestsVectorClass, callIntVectorSizeShouldBe10) {
    auto expect = 10;
    ASSERT_EQ(intVectorInitList.size(), expect);
}

TEST_F(TestsVectorClass, callFirstElementInVectorWithInitializerListConstructorShouldBe222) {
    auto expect = 222;
    ASSERT_EQ(intVectorInitList[0].getValue(), expect);
}

TEST_F(TestsVectorClass, callFourthElementInVectorWithInitializerListConstructorShouldBe225) {
    auto expect = 225;
    ASSERT_EQ(intVectorInitList[3].getValue(), expect);
}

TEST_F(TestsVectorClass, callSeventhElementInVectorWithInitializerListConstructorShouldBe228) {
    auto expect = 228;
    ASSERT_EQ(intVectorInitList[6].getValue(), expect);
}

TEST_F(TestsVectorClass, callTenthElementInVectorWithInitializerListConstructorShouldBe231) {
    auto expect = 231;
    ASSERT_EQ(intVectorInitList[9].getValue(), expect);
}

TEST_F(TestsVectorClass, callStringVectorCapacityShouldBe500) {
    auto expect = 500;
    ASSERT_EQ(stringVectorSizeValue.capacity(), expect);
}

TEST_F(TestsVectorClass, callStringVectorSizeShouldBe500) {
    auto expect = 500;
    ASSERT_EQ(stringVectorSizeValue.size(), expect);
}

TEST_F(TestsVectorClass, allValueInStringVectorFromConstructorWithSizeShouldBeTEST) {
    auto expect = "TEST";
    ASSERT_EQ(stringVectorSizeValue[0].getValue(), expect);
    ASSERT_EQ(stringVectorSizeValue[111].getValue(), expect);
    ASSERT_EQ(stringVectorSizeValue[333].getValue(), expect);
    ASSERT_EQ(stringVectorSizeValue[499].getValue(), expect);
}

TEST_F(TestsVectorClass, callStringVectorCapacityShouldBe10) {
    auto expect = 10;
    ASSERT_EQ(stringVectorInitList.capacity(), expect);
}

TEST_F(TestsVectorClass, callStringVectorSizeShouldBe10) {
    auto expect = 10;
    ASSERT_EQ(stringVectorInitList.size(), expect);
}

TEST_F(TestsVectorClass, callFirstElementInVectorStringWithInitializerListConstructorShouldBeTEST001) {
    auto expect = "TEST001";
    ASSERT_EQ(stringVectorInitList[0].getValue(), expect);
}