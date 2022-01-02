#include "myVector.hpp"

#include <vector>
#include <iostream>
#include <string>

int main() {
    std::vector<int> v ({ 1, 1, 3 });
    v.assign(4, 99);
    for (auto ele: v) {
        std::cout << ele << '\n';
    }
    //auto it = v.end();
    v.reserve(5);
    std::cout << v.capacity() << " - " << v.size() << '\n';
    std::cout << " ==================================================== " << '\n';
    luk::myVector<std::string>v1({"1"});
    std::string a = "sss";
    const std::string extra(6, 'b');
    v1.assign(extra.begin(), extra.end());
    std::cout << extra[5] << '\n';
    luk::myVector<int>v2(10, 33);
    luk::myVector<int>v3({12, 22, 44, 66, 77});

    return 0;
}