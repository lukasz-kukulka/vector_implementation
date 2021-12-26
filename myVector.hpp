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
        // konstruktor z wielkoscia i inicjalizowanymi elementami DONE
        // konstruktor initializer list DONE
        // konstruktor kopiujący DONE
        // konstruktor przenoszący DONE
        // operator przypisania kopiujacy DONE
        // operator przypisania przenoszący DONE
        // assign 
        // get_allocator 
        // Element access 
        // at 
        // operator[] 
        // front 
        // back 
        // data 
        // Iterators 
        // begin DONE
        // cbegin 
        // end DONE
        // cend 
        // rbegin 
        // crbegin 
        // rend 
        // crend 
        // Capacity DONE
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
#include <iterator>
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
        // for(std::initializer_list<decltype(this)>::iterator i = list.begin(); i < list.end(); i++) {

        // }
        auto iteratorList { 0 };
        for (const auto& ele : list) {
            traits_t::construct(alloc_, poiterAlloc_ + iteratorList, ele);   
            iteratorList++;
        }
    }
    myVector(const myVector& copy) 
    : capacity_(copy.capacity_)
    , alloc_(copy.alloc_)
    , poiterAlloc_(copy.poiterAlloc_)
    , size_(copy.size_)
    {
    }

    myVector(const myVector&& move) noexcept
    : capacity_(move.capacity_)
    , alloc_(move.alloc_)
    , poiterAlloc_(move.poiterAlloc_)
    , size_(move.size_)
    {
        move.alloc_ = 0;
        move.capacity_ = 0;
        move.poiterAlloc_ = nullptr;
        move.size_ = 0;
    }

    myVector& operator=(const myVector& copy) 
    {    
        capacity_ = copy.capacity_;
        alloc_ = copy.alloc_;
        poiterAlloc_ = copy.poiterAlloc_;
        size_ = copy.size_;
        return *this;
    }

    myVector& operator=(const myVector&& move) noexcept {
        if (this != move) {
            if (capacity_ < 0) {
                alloc_.deallocate(poiterAlloc_, capacity_);
            }
            capacity_ = move.capacity_;
            alloc_ = move.alloc_;
            poiterAlloc_ = move.poiterAlloc_;
            size_ = move.size_;
            move.alloc_ = 0;
            move.capacity_ = 0;
            move.poiterAlloc_ = nullptr;
            move.size_ = 0;
        }
        return *this;
    }

    ~myVector() {
        alloc_.deallocate(poiterAlloc_, capacity_);
    }


    void assign(size_t size, const Type& data) {
        // TO DO 
    }

    void assign(const Type& data) {
        // TO DO 
    }

    size_t capacity() const{
        return capacity_;
    }

    Type* begin() {
        // TO DO 
    }

    Type* cbegin() const {
        // TO DO 
    }

    Type* rbegin() const {
        // TO DO 
    }

    Type* crbegin() const {
        // TO DO 
    }

    Type* end() {
        // TO DO 
    } 

    Type* cend() const {
        // TO DO 
    } 

    Type* rend() const {
        // TO DO 
    }

    Type front() {
        // TO DO 
    }

    Type back() {
        // TO DO 
    }


private:
    bool checkCapacity() {
        if (size_ < capacity_) {
            return true;
        }
        return false;
    }
    size_t size_ { };
    size_t capacity_ { };
    std::allocator<Type>alloc_;
    Type* poiterAlloc_ { nullptr };
};