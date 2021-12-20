#pragma once

        // std::cout << "poiterAlloc_ = " << poiterAlloc_[0] << "       *poiterAlloc_ = " << *poiterAlloc_ << "        &poiterAlloc_ = " << &poiterAlloc_[0] << '\n';
        // traits_t::construct(alloc_, poiterAlloc_ + 1000, 7);   
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[1] << "       *poiterAlloc_ = " << *poiterAlloc_ + 1 << "        &poiterAlloc_ = " << &poiterAlloc_[1000] << '\n';
        // traits_t::construct(alloc_, poiterAlloc_ + 2, 22);   
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[2] << "       *poiterAlloc_ = " << *poiterAlloc_ + 2 << "        &poiterAlloc_ = " << &poiterAlloc_[2] << '\n';  
        // poiterAlloc_ = traits_t::allocate(alloc_, size); 
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[3] << "       *poiterAlloc_ = " << *poiterAlloc_<< "        &poiterAlloc_ = " << &poiterAlloc_[3] << '\n';

        // konsruktor pusty DONE
        // konstruktor z wielkoscia DONE
        // konstruktor z wielkoscia i inicjalizowanymi elementami done
        // konstruktor initializer list
        // konstruktor kopiujący
        // konstruktor przenoszący
        // operator przypisania kopiujacy
        // operator przypisania przenoszący
        // assign 
        // get_allocator 
        // Element access 
        // at 
        // operator[] 
        // front 
        // back 
        // data 
        // Iterators 
        // begincbegin 
        // end cend 
        // rbegincrbegin 
        // rendcrend 
        // Capacity 
        // empty 
        // size 
        // max_size 
        // reserve 
        // capacity 
        // shrink_to_fit 
        // Modifiers 
        // clear 
        // insert 
        // emplace 
        // erase 
        // push_back 
        // emplace_back 
        // pop_back 
        // resize 
        // swap 
        // wyjatki

#include <initializer_list>
#include <type_traits>
#include <memory>
#include <iostream>

template<typename Type, class Allocator = std::allocator<Type>>
class myVector {
public:
    myVector() {
        
    }
    myVector(size_t size) {
        capacity_ += size;
        using traits_t = std::allocator_traits<decltype(alloc_)>;
        poiterAlloc_ = traits_t::allocate(alloc_, capacity_);
    }
    myVector(size_t size, Type element) {
        capacity_ += size;
        using traits_t = std::allocator_traits<decltype(alloc_)>;
        poiterAlloc_ = traits_t::allocate(alloc_, capacity_);
        for (size_t i = 0; i < size; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, element);   
        }
    }
    myVector(std::initializer_list<Type> list) {
        capacity_ += list.size();
        using traits_t = std::allocator_traits<decltype(alloc_)>;
        poiterAlloc_ = traits_t::allocate(alloc_, capacity_);
        auto iteratorList { 0 };
        for (const auto& ele : list) {
            traits_t::construct(alloc_, poiterAlloc_ + iteratorList, ele);   
            iteratorList++;
        }
    }
    ~myVector() {
        alloc_.deallocate(poiterAlloc_, capacity_);
    }

    size_t capacity() const{
        return capacity_;
    }
private:
    size_t capacity_ {};
    std::allocator<Type>alloc_;
    Type* poiterAlloc_ { nullptr };
};