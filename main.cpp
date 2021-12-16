#include "myVector.hpp"

#include <vector>
#include <iostream>

int main() {
    std::vector<int>v;
    std::cout << v.capacity() << " - " << v.size() << '\n';
    myVector<int>v1(1);

    return 0;
}