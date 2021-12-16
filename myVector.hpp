#pragma once

#include <type_traits>
#include <memory>
#include <iostream>

template<typename Type, class Allocator = std::allocator<Type>>
class myVector {
public:
    myVector() {
        
    }
    myVector(size_t size) {
        poiterAlloc_ = alloc_.allocate(size);
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[0] << "       *poiterAlloc_ = " << *poiterAlloc_ << "        &poiterAlloc_ = " << &poiterAlloc_[0] << '\n';
        // using traits_t = std::allocator_traits<decltype(alloc_)>;
        // traits_t::construct(alloc_, poiterAlloc_ + 1, 7);   
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[1] << "       *poiterAlloc_ = " << *poiterAlloc_ + 1 << "        &poiterAlloc_ = " << &poiterAlloc_[1] << '\n';
        // traits_t::construct(alloc_, poiterAlloc_ + 2, 22);   
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[2] << "       *poiterAlloc_ = " << *poiterAlloc_ + 2 << "        &poiterAlloc_ = " << &poiterAlloc_[2] << '\n';
    }
    ~myVector() {
        alloc_.deallocate(poiterAlloc_, capacity_);
    }
private:
    size_t size_ {};
    size_t capacity_ {};
    std::allocator<Type>alloc_;
    Type* poiterAlloc_ { nullptr };
};