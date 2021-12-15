#pragma once

#include <type_traits>
#include <memory>

template<typename Type, class Allocator = std::allocator<Type>>
class myVector {
public:
    myVector() {
        
    }
    myVector(int size) {
        array = new Type[size];
    }
    ~myVector();
private:
    int size_ {};
    int capacity_ {};
    Type* array { nullptr };
};