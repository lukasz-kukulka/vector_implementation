#include "myVector.hpp"

#include <vector>
#include <iostream>

int main() {
    std::vector<int>v;
    std::cout << v.capacity() << " - " << v.size() << '\n';

    return 0;
}