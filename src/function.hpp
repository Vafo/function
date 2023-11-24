#ifndef FUNCTION_H
#define FUNCTION_H

#include <memory>

namespace func {

template<typename R, typename ...Args>
class function_owner_int {
public:
    virtual R operator()(Args... args) = 0;

};

template<typename funcType, typename R, typename ...Args>
class function_owner: public function_owner_int<R, Args...> {

public:
    function_owner(funcType func):
        m_func(func)
    {}

    R operator()(Args... args) {
        return m_func(args...);
    }

private:
    funcType m_func;
};


/*Template declaration*/
template<typename signature_Type>
class function;

/*Template specialization*/
/*Used to extract func sinature argument types and return type*/
template<typename R, typename ...Args>
class function<R(Args...)> {
public:
    template<typename func_Type>
    function(
        func_Type target
    ):
        m_owner_ptr( 
            std::make_unique< function_owner<func_Type, R, Args...> >(
                target
            )
        )
    {}

    R operator()(Args... args) {
        return (*m_owner_ptr)(args...);
    }

private:
    std::unique_ptr< function_owner_int<R, Args...> > m_owner_ptr;
};

}; // namespace func

#endif