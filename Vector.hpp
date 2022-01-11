#pragma once

#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace luk {

template<typename Vector>
class Iterator {
public:
    using value_type                                                 = typename Vector::value_type;
    using pointer                                                    = value_type*;
    using const_pointer                                              = const pointer;
    using reference                                                  = value_type&;
    using const_reference                                            = const reference;

public:
    Iterator(pointer ptr) 
        :ptr_(ptr)
    {
    }

    Iterator& operator++() {
        ptr_++;
        return *this;
    }

    Iterator operator++(int) {
        Iterator iterator = *this;
        ++(*this);
        return iterator;
    }

    Iterator& operator--() {
        ptr_--;
        return *this;
    }

    Iterator operator--(int) {
        Iterator iterator = *this;
        --(*this);
        return iterator;
    }

    reference operator[](int index) {
        return *(ptr_ + index);
    }

    pointer operator->() {
        return ptr_;
    }

    reference operator*() {
        return *ptr_;
    }

    bool operator==(const Iterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator& other) const {
        return !(*this == other);
    }

    bool operator<(const Iterator& other) const {
        return &ptr_ < &other.ptr_;
    }

    bool operator<=(const Iterator& other) const {
        return &ptr_ <= &other.ptr_;
    }

    bool operator>(const Iterator& other) const {
        return &ptr_ > &other.ptr_;
    }

    bool operator>=(const Iterator& other) const {
        return &ptr_ >= &other.ptr_;
    }

    Iterator operator+(Iterator other) {
        return ptr_ + other.ptr_;
    }

    Iterator operator-(Iterator other) {
        return ptr_ - other.ptr_;
    }

private:
    pointer ptr_;

};

template<typename Type, class Allocator = std::allocator<Type>>
class Vector {
public:
    using value_type                                                 = Type;
    using pointer                                                    = value_type*;
    using const_pointer                                              = const pointer;
    using reference                                                  = value_type&;
    using const_reference                                            = const reference;
    using iterator                                                   = Iterator<Vector<value_type>>;
    using const_iterator                                             = const iterator;
    using reverse_iterator                                           = std::reverse_iterator<iterator>;
    using const_reverse_iterator                                     = std::reverse_iterator<const_iterator>;
    using size_type                                                  = size_t;
    using difference_type                                            = ptrdiff_t;
    using allocator_type                                             = Allocator;

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
        return iterator(poiterAlloc_);
    }

    const_iterator cbegin() const {
        return begin();
    }

    reverse_iterator rbegin() {
        return end();
    }

    const_reverse_iterator crbegin() const {
        return cend();
    }

    iterator end() {
        return iterator(poiterAlloc_ + size_); 
    } 

    const_iterator cend() const {
        return end();
    } 

    reverse_iterator rend() {
        return begin(); 
    }

    const_reverse_iterator crend() const {
        return cbegin();  
    }

    value_type front() {
        return *poiterAlloc_; 
    }

    value_type back() {
         return *(poiterAlloc_ + size - 1); 
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
        std::allocator<value_type>tempAlloc;
        auto tempAllocPtr = traits_t::allocate(tempAlloc, space);
        for (size_type i = 0; i < capacity_; i++) {
            traits_t::construct(tempAlloc, tempAllocPtr + i, *(poiterAlloc_ + i)); 
        }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
        capacity_ = space;
    }

    void shrink_to_fit() {
        alloc_.deallocate(poiterAlloc_[size_ - 1], capacity_ - size_);
    }

    void clear() {
        traits_t::destroy(poiterAlloc_);
    }

    iterator insert(const_iterator pos, const value_type& value) {
        std::allocator<value_type>tempAlloc;
        size_type reserveSpaceTemp { capacity_ };
        if (capacity_ == size_) {
            reserveSpaceTemp++;
        }
        auto tempAllocPtr = traits_t::allocate(tempAlloc, reserveSpaceTemp);
        size_type itPos { 0 };
        for (const_iterator i = begin(); i < end(); i++) {
            if (i == pos) {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, value); 
            } else {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, *(poiterAlloc_ + itPos));
            }
            itPos++;
        }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
        return pos;
    }

    void insert(const_iterator pos, size_type count, const value_type& value ) {
        std::allocator<value_type>tempAlloc;
        size_type reserveSpaceTemp { capacity_ };
        if (capacity_ + count < size_) {
            reserveSpaceTemp += capacity_ + count;
        }
        auto tempAllocPtr = traits_t::allocate(tempAlloc, reserveSpaceTemp);
        size_type itPos { 0 };
        for (const_iterator i = begin(); i < end(); i++) {
            if (i >= pos && i <= pos + count) {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, value); 
            } else {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, *(poiterAlloc_ + itPos));
            }
            itPos++;
        }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
    }

    void insert(const_iterator pos, iterator first, iterator last) {
        std::allocator<value_type>tempAlloc;
        size_type reserveSpaceTemp { capacity_ };
        if (capacity_ < size_ + std::distance(first, last)) {
            reserveSpaceTemp += std::distance(first, last);
        }
        auto tempAllocPtr = traits_t::allocate(tempAlloc, reserveSpaceTemp);
        size_type itPos { 0 };
        for (const_iterator i = begin(); i < end(); i++) {
            if (i == pos) {
                for (auto j = first; j <= last; j++) {
                    traits_t::construct(tempAlloc, tempAllocPtr + itPos, *j); 
                }
            } else {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, *(poiterAlloc_ + itPos));
            }
            itPos++;
        }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
    }

    iterator insert(const_iterator pos, std::initializer_list<value_type> list ) {
        std::allocator<value_type>tempAlloc;
        size_type reserveSpaceTemp { capacity_ };
        if (capacity_ < size_ + list.size()) {
            reserveSpaceTemp += size_ + list.size();
        }
        auto tempAllocPtr = traits_t::allocate(tempAlloc, reserveSpaceTemp);
        size_type itPos { 0 };
        for (const_iterator i = begin(); i < end(); i++) {
            if (i == pos) {
                for (auto j = list.begin(); j < list.end(); j++) {
                    traits_t::construct(tempAlloc, tempAllocPtr + itPos, *j); 
                }
            } else {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, *(poiterAlloc_ + itPos));
            }
            itPos++;
        }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
        if (list.size() == 0) {
            return pos;
        }
        return ++pos;
    }
    
    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        constexpr size_type argSize = sizeof...(args);
        if (size_ + argSize < capacity_) {
            reserve(size_ + argSize);
        }
        std::initializer_list<value_type> tempArgsList { std::forward<value_type>(args...) };
        auto returnIt = insert(pos, tempArgsList);
        return ++pos;
    }

    iterator erase(iterator pos) {
        iterator tempIt = nullptr;
        std::allocator<value_type>tempAlloc;
        auto tempAllocPtr = traits_t::allocate(tempAlloc, capacity_);
        size_type itPos { 0 };
        for (const_iterator i = begin(); i < end(); i++) {
            if (i == pos) {
                i++;
                tempIt = i;
            } else {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, *(poiterAlloc_ + itPos));
            }
            itPos++;
        }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
        return tempIt; 
    }

    iterator erase(iterator first, iterator last) {
        iterator tempIt = nullptr;
        std::allocator<value_type>tempAlloc;
        auto tempAllocPtr = traits_t::allocate(tempAlloc, capacity_);
        size_type itPos { 0 };
        for (const_iterator i = begin(); i < end(); i++) {
            if (i == first) {
                for (auto j = first; j <= last; j++) {
                    i++;
                }
                tempIt = i;
            } else {
                traits_t::construct(tempAlloc, tempAllocPtr + itPos, *(poiterAlloc_ + itPos));
            }
            itPos++;
        }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
        return tempIt; 
    }

    void push_back(const value_type value) {
        if (capacity_ == size_) {
            reserve(size + 1);
        }
        traits_t::construct(alloc_, poiterAlloc_ + size_, value);
    }

    void push_back(value_type&& value) {
        emplace_back(std::move(value));
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (capacity_ < size + (sizeof...(args))) {
            reserve(size + (sizeof...(args)));
        }
        std::initializer_list<value_type> tempArgsList { std::forward<value_type>(args...) };
        for (auto i + tempArgsList.begin(); i < tempArgsList.end(); i++) {
            traits_t::construct(alloc_, poiterAlloc_ + size_, value);
            size++;
        }
    }

    template<typename... Args>
    reference emplace_back(Args&&... args) {
        // to do
        // add return
    }

    void pop_back() {
        // to do
    }

    void resize(size_type count) {
        // to do
    }

    void resize(size_type count, value_type value = value_type()) {
        // to do
    }

    void resize(size_type count, const_reference value) {
        // to do
    }

    void swap(Vector& other) {
        // to do
        // add return
    }

        // split insert
        // sparwdzic size czy zwiekszam i capacity

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

    size_type size_ { 0 };
    size_type capacity_ { 0 };
    std::allocator<value_type>alloc_;
    pointer poiterAlloc_ { nullptr };
    using traits_t = std::allocator_traits<decltype(alloc_)>;
};

} //  end namespace