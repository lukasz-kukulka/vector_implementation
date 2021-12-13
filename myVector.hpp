#pragma once

#include <type_traits>
#include <memory>

template<typename Type, class Allocator = std::allocator<Type>>
class myVector {
public:
    myVector();
    ~myVector();
private:
    uint size_ {};
    uint capacity_ {};
};