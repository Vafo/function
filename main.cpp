#include <iostream>

#include <vector>

#include "function.hpp"

int kek(int a) {
    return a + 1;
}

void funky(void) {
    std::cout << "Hello!" << std::endl;
}

template<typename el_Type>
void vec_out(std::vector<el_Type>& ivec) {
    for(
        std::vector<int>::iterator beg = ivec.begin();
        beg != ivec.end();
        ++beg
    )
        std::cout << *beg << " ";
}

int main(int argc, char* argv[]) {

    func::function<int(int)> aboba(kek);

    func::function<void(std::vector<int>&)> lolus(vec_out<int>);

    std::cout << aboba(1) << std::endl;

    std::vector<int> ivec = {1, 2, 3, 5, 5, 7};

    lolus(ivec);
    std::cout << std::endl;

    func::function<void(int)> kekus(funky);

    kekus(0);

    return 0;
}