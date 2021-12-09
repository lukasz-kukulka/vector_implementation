#pragma once

#include <type_traits>
#include <memory>

template<typename Type, class Allocator = std::allocator<Type>>
class vector {
public:
    vector() = default;
    ~vector();
private:

};