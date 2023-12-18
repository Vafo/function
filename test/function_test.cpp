#include <catch2/catch_all.hpp>
#include "function.hpp"

#include <vector>
#include <numeric>

namespace func {

int zero_func() {
    return 0;
}

int addition(int a, int b) {
    return a + b;
}

class Functor {
public:
    int operator()() {
        return 1;
    }

    int operator()(int a, int b) {
        return a - b;
    }

    /*increment every element*/
    void operator()(std::vector<int>& ivec) {
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
    function<int(int)> afunc ([] (int a) -> int { return a + 1; });
    
    REQUIRE_NOTHROW(afunc(const_val));
    REQUIRE(afunc(const_val) == const_val + 1);
    
    function<int(int)> bfunc = afunc;

    REQUIRE_NOTHROW(bfunc(const_val));
    REQUIRE(bfunc(const_val) == const_val + 1);
}

TEST_CASE("function assignment", "[function][assignment]") {
    function<int()> afunc = zero_func;
    function<int()> bfunc = Functor();
    function<int()> tmpfunc;

    REQUIRE(afunc() == 0);
    REQUIRE(bfunc() == 1);

    /*intentional swap*/
    REQUIRE_NOTHROW(tmpfunc = afunc);
    REQUIRE_NOTHROW(afunc = bfunc);
    REQUIRE_NOTHROW(bfunc = tmpfunc);

    REQUIRE(afunc() == 1);
    REQUIRE(bfunc() == 0);
}

TEST_CASE("function validity", "[function]") {
    function<int(int, int)> some_func;

    REQUIRE( static_cast<bool>(some_func) == false );

    some_func = addition;
    REQUIRE( static_cast<bool>(some_func) == true );

    REQUIRE(some_func(1, 2) == 3);
}

int apply_func(int arg1, int arg2, const function<int(int, int)>& func) {
    return func(arg1, arg2);
}

TEST_CASE("function as parameter", "[function]") {
    function<int(int, int)> classic_func = addition; /*addition*/
    function<int(int, int)> functor_func = Functor(); /*difference*/
    function<int(int, int)> lambda_func = [] (int a, int b) -> int {return a * b;}; /*multiplication*/

    const int arg1 = 5, arg2 = 12;

    REQUIRE(apply_func(arg1, arg2, classic_func) == arg1 + arg2);
    REQUIRE(apply_func(arg1, arg2, functor_func) == arg1 - arg2);
    REQUIRE(apply_func(arg1, arg2, lambda_func) == arg1 * arg2);
}

TEST_CASE("const function", "[function]") {
    const function<int(int, int)> const_func = addition;
    function<int(int, int)> other_func = const_func;

    const int arg1 = 5, arg2 = 12;

    REQUIRE(const_func(arg1, arg2) == arg1 + arg2);
    REQUIRE(other_func(arg1, arg2) == arg1 + arg2);
}

TEST_CASE("function with object arguments", "[function]") {
    function<void(std::vector<int>&)> vec_incr = Functor();
    
    const int N = 5;
    const int init_val = 0;
    std::vector<int> ivec(N);
    std::iota(ivec.begin(), ivec.end(), init_val);
    
    std::vector<int> ivec_test(N);
    std::iota(ivec_test.begin(), ivec_test.end(), init_val + 1);

    REQUIRE_NOTHROW(vec_incr(ivec));
    REQUIRE_THAT(ivec, Catch::Matchers::RangeEquals(ivec_test));
}

}; // namespace func