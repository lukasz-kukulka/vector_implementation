#include "Vector.hpp"

#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<int> v ({ 1, 2, 3, 4, 5 });
    std::cout << *(v.rend() - 2) << std::endl;
    // std::vector<int> v33 (50);
    // v.resize(22);
    // v.clear();
    // std::cout << v33.capacity() << " - " << v33.size() << '\n';
    // std::cout << " ==================================================== " << '\n';
    // v33[22] = 33;
    // std::cout << v33[22] << '\n';
    // luk::Vector<std::string>v1({"1"});
    // // v1.begin();
    // luk::Vector<int>v2(10, 33);
    // luk::Vector<int>v3({12, 22, 44, 66, 77});
    // std::cout << v[1] << '\n';

    return 0;
}