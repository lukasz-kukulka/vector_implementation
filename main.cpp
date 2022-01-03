#include "Vector.hpp"

#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<int> v ({ 1, 1, 3 });
    auto aaa = v.begin();
    aaa++;
    v.assign(4, 99);
    for (auto ele: v) {
        std::cout << ele << '\n';
    }
    v.reserve(5);
    std::cout << v.capacity() << " - " << v.size() << '\n';
    std::cout << " ==================================================== " << '\n';
    luk::Vector<std::string>v1({"1"});;
    luk::Vector<int>v2(10, 33);
    luk::Vector<int>v3({12, 22, 44, 66, 77});
    std::cout << v3[2] << '\n';

    return 0;
}