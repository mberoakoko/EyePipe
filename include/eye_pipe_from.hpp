//
// Created by mbero on 15/07/2025.
//

#ifndef EYE_PIPE_FROM_HPP
#define EYE_PIPE_FROM_HPP

#include <functional>
#include "../include/eye_detail.hpp"
#include "../include/eye_functional.hpp"

namespace eye_pipe::pipeline {

    /**
     * Factory method to create a functional closure from a specific value
     * @tparam T template parameter of value
     * @param value R-value of parameter
     * @return functional closure of created value
     */
    template<typename T>
    auto from(T&& value) {
        auto binding_lambda = []<typename ValueType>(ValueType&& value) -> auto&& {
            return std::forward<ValueType>(value);
        };
        return func_closure(std::bind(binding_lambda, std::forward<T>(value)));
    }

    template<typename T>
    auto from(T& value ) {
        return func_closure([&value]() -> auto {return value;});
    }

    template<typename T>
    auto from(const T& value) {
        return func_closure([&value]() -> const T&{return  value;} );
    }

    inline auto test_from_functions() {
        int value = 1;
        auto captured_value = from(value);
        auto printer = from([]<typename ValueType>(ValueType&& value) {
                std::cout << value << std::endl;
        });
        std::cout << "value" << std::endl;
        printer()("What is going on here ?");
        printer(123);
        std::apply(printer(), std::tuple{"Am printing this using std::apply \n"});
        std::cout << "--------------------------------------------------------------------"<<std::endl;
    }
}

#endif //EYE_PIPE_FROM_HPP
