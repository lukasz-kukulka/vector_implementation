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
#include <exception>

namespace luk {

template<typename Vector>
class Iterator {
public:
    Iterator(Vector::pointer ptr) {

    }
public:

private:


};

template<typename Type, class Allocator = std::allocator<Type>>
class Vector {
public:
      typedef Type                                                              value_type;
      typedef value_type*                                                       pointer;
      typedef const pointer                                                     const_pointer;
      typedef value_type&                                                       reference;
      typedef const reference                                                   const_reference;
      typedef Iterator<Vector>                                                  iterator;
      typedef const iterator                                                    const_iterator;
      typedef std::reverse_iterator<iterator>                                   reverse_iterator;
      typedef std::reverse_iterator<const_iterator>	                            const_reverse_iterator;
      typedef size_t                                                            size_type;
      typedef ptrdiff_t                                                         difference_type;
      typedef Allocator                                                         allocator_type;

public:
    Vector() {
        
    }
    Vector(size_type size) {
        reserve(size);
    }
    Vector(size_type size, value_type element) {
        reserve(size);
        for (size_type i = 0; i < size; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, element);   
        }
    }
    Vector(std::initializer_list<value_type> list) {
        reserve(list.size());
        initializerListInit(list);
        // auto iteratorList { 0 };
        // for (const auto& ele : list) {
        //     traits_t::construct(alloc_, poiterAlloc_ + iteratorList, ele);   
        //     iteratorList++;
        // }
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[0] << "       *poiterAlloc_ = " << *poiterAlloc_ << "        &poiterAlloc_ = " << &poiterAlloc_[0] << '\n';  
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[1] << "       *poiterAlloc_ = " << *poiterAlloc_ + 1 << "        &poiterAlloc_ = " << &poiterAlloc_[1000] << '\n';
        // std::cout << "poiterAlloc_ = " << poiterAlloc_[2] << "       *poiterAlloc_ = " << *poiterAlloc_ + 2 << "        &poiterAlloc_ = " << &poiterAlloc_[2] << '\n';  
        // std::cout << capacity() << '\n';
    }
    Vector(const Vector& copy) 
        : capacity_(copy.capacity_)
        , alloc_(copy.alloc_)
        , poiterAlloc_(copy.poiterAlloc_)
        , size_(copy.size_)
    {
    }

    Vector(const Vector&& move) noexcept
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

    Vector& operator=(const Vector& copy) 
    {    
        capacity_ = copy.capacity_;
        alloc_ = copy.alloc_;
        poiterAlloc_ = copy.poiterAlloc_;
        size_ = copy.size_;
        return *this;
    }

    Vector& operator=(const Vector&& move) noexcept {
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

    reference operator[](int element) {
        return poiterAlloc_[element];
    }

    ~Vector() {
        alloc_.deallocate(poiterAlloc_, capacity_);
    }

    constexpr void assign(size_type size, const_reference data) {
        reserve(size);
        for (size_type i = 0; i < size; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, data); 
        }
    }
    
    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    constexpr void assign(InputIterator first, InputIterator last) {
        difference_type elementsAmount = last - first;
        reserve(elementsAmount);
        std::cout << *first <<'\n';
        for (auto i = 0; i < elementsAmount; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, &(*(first + i))); 
        }
    }

    constexpr void assign(std::initializer_list<value_type> list ) {
        initializerListInit(list);
    }

    size_type capacity() const{
        return capacity_;
    }

    iterator begin() {
        
    }

    const_iterator cbegin() const {
        // TO DO 
    }

    reverse_iterator rbegin() const {
        // TO DO 
    }

    const_reverse_iterator crbegin() const {
        // TO DO 
    }

    iterator end() {
        // TO DO 
    } 

    const_iterator cend() const {
        // TO DO 
    } 

    reverse_iterator rend() {
        // TO DO 
    }

    const_reverse_iterator crend() const {
        // TO DO 
    }

    value_type front() {
        // TO DO 
    }

    value_type back() {
        // TO DO 
    }

    std::allocator<value_type> get_allocator() {
        return alloc_;
    }

    void at(size_type size) {
        if (size > size_) {
            throw std::out_of_range("Out of range");
        }
    }

    pointer data() {
        if (empty()) {
            return &front();
        }
        return nullptr;
    }

    bool empty() {
        return poiterAlloc_ == nullptr;
    }

    size_type size() const {
        return size_;
    }

    size_type max_size() const {
        return traits_t::max_size();
    }

    void reserve(size_type space) {
        poiterAlloc_ = traits_t::allocate(alloc_, space);
        capacity_ = space;
    }

    void shrink_to_fit() {
        alloc_.deallocate(poiterAlloc_[size_ - 1], capacity_ - size_);
    }

    void clear() {
        traits_t::destroy(poiterAlloc_);
    }

private:
    bool checkCapacity() {
        if (size_ < capacity_) {
            return true;
        }
        return false;
    }

    constexpr void initializerListInit(const std::initializer_list<value_type>& list) {
        reserve(list.size());
        for(auto iteratorList = 0, i = list.begin(); i < list.end(); i++, iteratorList++) {
            traits_t::construct(alloc_, poiterAlloc_ + iteratorList, *i); 
        }
    }

    size_type size_ { };
    size_type capacity_ { };
    std::allocator<value_type>alloc_;
    pointer poiterAlloc_ { nullptr };
    using traits_t = std::allocator_traits<decltype(alloc_)>;
};

} //  end namespace