//
// Created by mbero on 11/07/2025.
//

#ifndef EYE_DETAIL_HPP
#define EYE_DETAIL_HPP
#include <compare>
#include <iostream>
#include <concepts>
#include <tuple>

namespace eye_pipe::pipeline {
    template<typename T1, typename T2>
    class pipe_pair;

    template<typename Func, typename ...Funcs>
    class fork_into;

    template<typename T>
    concept is_tuple = std::same_as<T, std::remove_cvref_t<T>>
                        && std::is_same_v<std::tuple<>, T>
                        || requires (T t){
        []<typename ...Ts>(const std::tuple<Ts ...>&){}(t);
    };




    template<typename T>
    auto test_is_tuple_t(T) -> void {
        if constexpr (is_tuple<T>) {
            std::cout << typeid(T).name() << " is a tuple" <<'\n';
        } else {
            std::cout << typeid(T).name() << " is not a tuple" <<'\n';
        }
    }

    inline auto run_test_is_tuple_t() {
        test_is_tuple_t(std::tuple<>{});
        test_is_tuple_t(std::tuple<int>{});
        test_is_tuple_t(std::tuple<int, double>{});
        test_is_tuple_t(5);
        test_is_tuple_t("hello");
    }

}

#endif //EYE_DETAIL_HPP
