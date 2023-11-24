#include <catch2/catch_all.hpp>
#include "function.hpp"

#include <vector>
#include <numeric>

namespace func {

int zero_func() {
    return 0;
}

class Functor {

    int operator()() {
        return 1;
    }

    /*increment every element*/
    void operator(std::vector<int>& ivec) {
        for(
            std::vector<int>::iterator beg = ivec.begin();
            beg != ivec.end();
            ++beg
        )
            *beg += 1;
    }

};

TEST_CASE("function default construction", "[function][constructor]") {
    function<int()> ifunc;
    REQUIRE_THROWS(ifunc());
}

TEST_CASE("function copy construction", "[function][constructor]") {
    const int const_val = 2;
    function<int(int)> afunc = [] (int a) { return a + 1 };
    
    REQUIRE_NO_THROW(afunc(const_val));
    REQUIRES(afunc(const_val) == const_val + 1);
    
    function<int(int)> bfunc = afunc;

    REQUIRE_NO_THROW(bfunc(const_val));
    REQUIRES(bfunc(const_val) == const_val + 1);
}

TEST_CASE("function assignment", "[function][assignment]") {
    function<int()> afunc = zero_func;
    function<int()> bfunc = Functor;
    function<int()> tmpfunc;

    REQUIRES(afunc() == 0);
    REQUIRES(bfunc() == 1);

    /*intentional swap*/
    REQUIRE_NO_THROW(tmpfunc = afunc);
    REQUIRE_NO_THROW(afunc = bfunc);
    REQUIRE_NO_THROW(bfunc = tmpfunc);

    REQUIRES(afunc() == 1);
    REQUIRES(bfunc() == 0);
}

}; // namespace func