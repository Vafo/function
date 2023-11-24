#ifndef FUNCTION_H
#define FUNCTION_H

#include <memory>

namespace func {

template<typename R, typename A1>
class function_owner_int {
public:
    virtual R operator()(A1 arg1) = 0;

};

template<typename funcType, typename R, typename A1>
class function_owner: public function_owner_int<R, A1> {

public:
    function_owner(funcType func):
        m_func(func)
    {}

    R operator()(A1 arg) {
        return m_func(arg);
    }

private:
    funcType m_func;
};


/*Template declaration*/
template<typename signature_Type>
class function;

/*Template specialization*/
/*Used to extract func sinature argument types and return type*/
template<typename R, typename A1>
class function<R(A1)> {

public:
    template<typename func_Type>
    function(
        func_Type target
    ):
        m_owner_ptr( 
            std::make_unique< function_owner<func_Type, R, A1> >(
                target
            )
        )
    {}

    R operator()(A1 arg) {
        return (*m_owner_ptr)(arg);
    }

private:
    std::unique_ptr< function_owner_int<R, A1> > m_owner_ptr;
};

}; // namespace func

#endif