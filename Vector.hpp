#pragma once

#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <type_traits>
#include <utility>

// dodać bool operator
namespace luk {

template<typename Vector>
class Iterator {
public:
    using value_type                                                 = Vector::value_type;
    using pointer                                                    = value_type*;
    using const_pointer                                              = const pointer;
    using reference                                                  = value_type&;
    using const_reference                                            = const reference;
    using size_type                                                  = size_t;

public:
    Iterator()
    {
    }

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

        return ptr_ + std::distance(other.ptr_, ptr_);
    }

    Iterator operator+(size_type value) {
        return ptr_ + value;
    }

    Iterator operator-(Iterator other) {
        return ptr_ - other.ptr_;
    }

    Iterator operator-(size_type value) {
        return ptr_ - value;
    }

private:
    pointer ptr_ { nullptr };

};

template<typename Type>
class ReverseIterator : public Iterator<Type> {
public:
    using value_type                                                 = Type;
    using pointer                                                    = value_type*;
    using const_pointer                                              = const pointer;
    using reference                                                  = value_type&;
    using const_reference                                            = const reference;
    using size_type                                                  = size_t;

public:
    ReverseIterator()
    {
    }

    ReverseIterator(pointer ptr) 
        :ptr_(ptr)
    {
    }

    ReverseIterator& operator++() {
        ptr_--;
        return *this;
    }

    ReverseIterator operator++(int) {
        Iterator iterator = *this;
        --(*this);
        return iterator;
    }

    ReverseIterator& operator--() {
        ptr_++;
        return *this;
    }

    ReverseIterator operator--(int) {
        Iterator iterator = *this;
        ++(*this);
        return iterator;
    }

    ReverseIterator operator+(ReverseIterator other) {
        return ptr_ - other.ptr_;
    }

private:
    pointer ptr_ { nullptr };
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
    using reverse_iterator                                           = ReverseIterator<value_type>;
    using const_reverse_iterator                                     = const reverse_iterator;
    using size_type                                                  = size_t;
    using difference_type                                            = ptrdiff_t;
    using allocator_type                                             = Allocator;

public:
    Vector() {
        
    }
    Vector(size_type size) {
        reserve(size);
        for (size_type i = 0; i < size; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, 0);   
        }
        size_ = size;
    }
    Vector(size_type size, value_type element) {
        reserve(size);
        for (size_type i = 0; i < size; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, element);   
        }
        size_ = size;
    }
    Vector(std::initializer_list<value_type> list) {
        reserve(list.size());
        initializerListInit(list);
        size_ = list.size();
    }
    Vector(const Vector& copy) 
    {
        size_ = copy.size_;
        capacity_ = copy.capacity_;
        reserve(copy.capacity_);
        for (size_type i = 0; i < size_; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, *(copy.poiterAlloc_ + i));   
        }
    }

    Vector(Vector&& move) noexcept
        : capacity_(move.capacity_)
        , alloc_(move.alloc_)
        , poiterAlloc_(move.poiterAlloc_)
        , size_(move.size_)
    {
        std::cout << "C-TOR MOVE\n";
        move.capacity_ = 0;
        move.poiterAlloc_ = nullptr;
        move.size_ = 0;
    }

    Vector& operator=(const Vector& copy) 
    {   
        std::cout << "OPERATOR = COPY\n";
        capacity_ = copy.capacity_;
        size_ = copy.size_;
        reserve(capacity_);
        for (size_type i = 0; i < size_; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, *(copy.poiterAlloc_ + i));   
        }
        return *this;
    }

    Vector& operator=(Vector&& move) noexcept {
        std::cout << "OPERATOR = MOVE\n";
        if (this != &move) {
            if (capacity_ < 0) {
                alloc_.deallocate(poiterAlloc_, capacity_);
            }
            capacity_ = move.capacity_;
            alloc_ = move.alloc_;
            poiterAlloc_ = move.poiterAlloc_;
            size_ = move.size_;
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

    void assign(size_type size, reference data) {
        reserve(size);
        for (size_type i = 0; i < size; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, data); 
        }
        size_ = size;
    }
    
    template<typename InputIterator, typename = std::_RequireInputIter<InputIterator>>
    void assign(InputIterator first, InputIterator last) {
        difference_type elementsAmount = last - first;
        reserve(elementsAmount);
        std::cout << *first <<'\n';
        for (auto i = 0; i < elementsAmount; i++) {
            traits_t::construct(alloc_, poiterAlloc_ + i, &(*(first + i))); 
        }
        size_ = elementsAmount;
    }

    void assign(std::initializer_list<value_type> list ) {
        initializerListInit(list);
    }

    size_type capacity() const{
        return capacity_;
    }

    iterator begin() {
        return iterator(poiterAlloc_);
    }

    const_iterator cbegin() {
        return begin();
    }

    // reverse_iterator rbegin() {
    //     return begin();
    // }

    // const_reverse_iterator crbegin() const {
    //     return cend();
    // }

    iterator end() {
        return iterator(poiterAlloc_ + size_); 
    } 

    const_iterator cend() {
        return end();
    } 

    // reverse_iterator rend() {
    //     return begin(); 
    // }

    // const_reverse_iterator crend() const {
    //     return cbegin();  
    // }

    value_type front() {
        return *poiterAlloc_; 
    }

    value_type back() {
         return *(poiterAlloc_ + size_ - 1); 
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
        return empty() ? nullptr : poiterAlloc_;
    }

    bool empty() {
        return poiterAlloc_ == nullptr;
    }

    size_type size() const {
        return size_;
    }

    size_type max_size() const {;
        return traits_t::max_size(alloc_);
    }

    void reserve(size_type space) {
        std::allocator<value_type>tempAlloc;
        auto tempAllocPtr = traits_t::allocate(tempAlloc, space);
        // for (size_type i = 0; i < capacity_; i++) {
        //     traits_t::construct(tempAlloc, tempAllocPtr + i, *(poiterAlloc_ + i)); 
        // }
        alloc_.deallocate(poiterAlloc_, capacity_);
        alloc_ = std::move(tempAlloc); 
        poiterAlloc_ = std::move(tempAllocPtr);
        capacity_ = space;
    }

    void shrink_to_fit() {
        alloc_.deallocate(poiterAlloc_[size_ - 1], capacity_ - size_);
        capacity_ = size_;
    }

    void clear() {
        traits_t::destroy(poiterAlloc_);
        size_ = 0;
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
        size_++;
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
        size_ = size_ + count;
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
        size_ = size_ + std::distance(first, last);
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
        size_ = size_ + list.size();
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
        size_--;
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
        size_ = size_ - std::distance(first, last);
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
        size++;
    }

    void push_back(value_type&& value) {
        emplace_back(std::move(value));
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        emplace_back(std::forward<value_type>(args...));
    }

    template<typename... Args>
    reference emplace_back(Args&&... args) {
        if (capacity_ < size + (sizeof...(args))) {
            reserve(size + (sizeof...(args)));
        }
        std::initializer_list<value_type> tempArgsList { std::forward<value_type>(args...) };
        auto itReturn = poiterAlloc_ + size_ + 1;
        for (auto i = tempArgsList.begin(); i < tempArgsList.end(); i++) {
            traits_t::construct(alloc_, poiterAlloc_ + size_, *tempArgsList);
        }
        size+= (sizeof...(args));
        return itReturn;
    }

    void pop_back() {
        traits_t::destroy(poiterAlloc_ + (size_ - 1));
        size--;
        
    }

    void resize(size_type count) {
        if (count < size_) {
            traits_t::destroy(poiterAlloc_ + (size_ - (size_ - count)));
            size_ = count;
        } else {
            reserve(count);
            traits_t::construct(alloc_, poiterAlloc_ + size, 0);
            size_ = count;
        }

    }

    void resize(size_type count, value_type value = value_type()) {
        if (count < size_) {
            traits_t::destroy(poiterAlloc_ + (size_ - (size_ - count)));
            size_ = count;
        } else {
            reserve(count);
            for (auto i = 0; i < size_ - count; i++)
            traits_t::construct(alloc_, poiterAlloc_ + size + i, value);
            size_ = count;
        }
    }

    void swap(Vector& other) {
        auto tempPoiterAlloc = poiterAlloc_;
        poiterAlloc_ = other.poiterAlloc_;
        other.poiterAlloc_ = tempPoiterAlloc;
        auto tempAlloc = alloc_;
        alloc_ = other.alloc_;
        other.alloc_ = tempAlloc;
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

    size_type size_ { 0 };
    size_type capacity_ { 0 };
    std::allocator<value_type>alloc_;
    pointer poiterAlloc_ { nullptr };
    using traits_t = std::allocator_traits<decltype(alloc_)>;
};

} //  end namespace