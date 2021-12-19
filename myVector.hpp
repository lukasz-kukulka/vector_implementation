#pragma once

#include <type_traits>
#include <memory>

template<typename Type, class Allocator = std::allocator<Type>>
class myVector {
public:
    myVector() {
        
    }
    myVector(size_t size) {
        alloc_.allocate(size);
    }
    ~myVector();
private:
    size_t size_ {};
    size_t capacity_ {};
    std::allocator<Type>alloc_;
    Type* poiterAlloc_ { nullptr };
};