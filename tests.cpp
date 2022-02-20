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
        //std::cout << "CONSTRUCTOR\n";
    }
    ~testClassToVector()
    {
        //std::cout << "DES\n";
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

TEST_F(TestsVectorClass, callThirdElementInVectorStringWithInitializerListConstructorShouldBeTEST003) {
    auto expect = "TEST003";
    ASSERT_EQ(stringVectorInitList[2].getValue(), expect);
}

TEST_F(TestsVectorClass, callSeventhElementInVectorStringWithInitializerListConstructorShouldBeTEST007) {
    auto expect = "TEST007";
    ASSERT_EQ(stringVectorInitList[6].getValue(), expect);
}

TEST_F(TestsVectorClass, callCopyConstructorShouldReturnRightResult) {
    auto copyVector(TestsVectorClass::intVectorSizeValue);
    ASSERT_EQ(copyVector[11].getValue(), intVectorSizeValue[22].getValue());
}

TEST_F(TestsVectorClass, callMoveConstructorShouldReturnCorrectValue) {
    auto copyVector(intVectorInitList);
    auto moveVector(std::move(intVectorInitList));
    ASSERT_EQ(moveVector[0].getValue(), copyVector[0].getValue());
}

TEST_F(TestsVectorClass, callComparisonOperatorShouldReturnCorrectValue) {
    luk::Vector<testClassToVector<int>> newVector;
    newVector = intVectorInitList;
    ASSERT_EQ(newVector[1].getValue(), intVectorInitList[1].getValue());
}

TEST_F(TestsVectorClass, callMoveComparisonOperatorShouldReturnRightValue) {
    auto expect = 222;
    luk::Vector<testClassToVector<int>> newVector;
    newVector = (std::move(intVectorInitList));
    ASSERT_EQ(newVector[0].getValue(), expect);
    ASSERT_EQ(intVectorInitList.size(), 0);
    ASSERT_EQ(intVectorInitList.capacity(), 0);
}

TEST_F(TestsVectorClass, callAssignWithInitListFunctionShouldChangeVectorValue) {
    auto expect = 5;
    intVectorInitList.assign({ 5, 6, 7 });
    ASSERT_EQ(intVectorInitList[0].getValue(), expect);
    expect = 6;
    ASSERT_EQ(intVectorInitList[1].getValue(), expect);
    expect = 7;
    ASSERT_EQ(intVectorInitList[2].getValue(), expect);
}

TEST_F(TestsVectorClass, callAssignWithSizeAndValueFunctionShouldChangeVectorValue) {
    testClassToVector<int> myValue = 876;
    auto expect = 876;
    intVectorSizeValue.assign(6, myValue);
    ASSERT_EQ(intVectorSizeValue[0].getValue(), expect);
}

///////////////////////////////////////
// dodać test z assign i iteratorami //
///////////////////////////////////////

TEST_F(TestsVectorClass, callCapacityFunctionShouldReturnRightCapacity) {
    auto expect = 10;
    luk::Vector<testClassToVector<int>> newVector(10, 9999);
    ASSERT_EQ(newVector.capacity(), expect);
}

TEST_F(TestsVectorClass, callSizeFunctionShouldReturnRightSize) {
    auto expect = 33;
    luk::Vector<testClassToVector<int>> newVector(33, 9999);
    ASSERT_EQ(newVector.size(), expect);
}

TEST_F(TestsVectorClass, callIteratorBeginShouldReturnFirsElement) {
    auto expect = 222;
    ASSERT_EQ(intVectorInitList.begin()->getValue(), expect);
}

TEST_F(TestsVectorClass, callIteratorCBeginShouldReturnFirsElement) {
    auto expect = 222;
    auto getIterator = intVectorInitList.cbegin();
    ASSERT_EQ(getIterator->getValue(), expect);
}

TEST_F(TestsVectorClass, callIteratorEndShouldReturnLastElement) {
    auto expect = 231;
    auto getIterator = intVectorInitList.end() - 1;
    ASSERT_EQ(getIterator->getValue(), expect);
}

///////////////////////////////////////
// dodać testy z reverse iteratorami //
///////////////////////////////////////

TEST_F(TestsVectorClass, callIteratorCEndShouldReturnLastElement) {
    auto expect = 231;
    auto getIterator = intVectorInitList.cend();
    ASSERT_EQ((getIterator - 1)->getValue(), expect);
}

TEST_F(TestsVectorClass, callFrontMethodShouldReturnFirstValue) {
    auto expect = 222;
    auto value = intVectorInitList.front();
    ASSERT_EQ(value.getValue(), expect);
}

TEST_F(TestsVectorClass, callBackMethodShouldReturnLastValue) {
    auto expect = 231;
    auto value = intVectorInitList.back();
    ASSERT_EQ(value.getValue(), expect);
}

///////////////////////////////////////
// dodać testy get_alocator          //
///////////////////////////////////////

///////////////////////////////////////
// dodać asercje z wyjatkiem at      //
///////////////////////////////////////