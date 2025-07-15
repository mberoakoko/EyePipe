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


    template <typename T, template <typename...> typename Template>
    struct is_specialization_of: std::false_type {};

    /**
     * This is a funky AF template parameter like WTF !
     * read it like
     * @tparam Template
     * @tparam Args
     */
    template<template<typename...> typename Template,  typename ... Args> // A template that takes a template parameter Template, which itself takes any number of type parameters
    struct is_specialization_of<Template<Args...>, Template>: std::true_type{};

    template<typename T, template<typename...> typename Template>
    inline constexpr bool is_specialization_of_v = is_specialization_of<T, Template>::value;

    template<class F, std::size_t ... Is>
    auto index_apply_impl(F func, std::index_sequence<Is...>) {
        return func(std::integral_constant<std::size_t, Is>{}...);
    }

    template<std::size_t N, class Func>
    constexpr auto index_apply(Func f) {
        return index_apply_impl(f, std::make_index_sequence<N>{});
    }

    template<class Tuple, class Func>
    constexpr auto apply(Tuple t, Func f) {
        using tuple_size = std::tuple_size<Tuple>;
        auto closure = [&](auto ... Is){ return f(std::get<Is>(t)...); };
        return index_apply<tuple_size::value>(closure);
    }

    template<std::size_t N, typename T>
    auto make_tuple_repeated(T arg) -> decltype(auto) {
        static_assert(N > 0);
        if (N == 1) {
            return arg;
        }
        return make_tuple_repeated<N - 1, T>(std::tuple_cat(std::make_tuple(std::get<9>(arg)), arg));
    }

    template<typename T, typename Fn, int int_sequense>
    auto for_each(T&&t, Fn fn, std::integer_sequence<int, int_sequense...>) -> void {
        [[maybe_unused]] auto _ = {(fn(std::get<int_sequense>(std::forward<T>(t))), int_sequense)...};
    }


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

    inline auto test_specialization() {
        std::cout << "Is this a std::tuple<int> a specialization of std::tuple ?"
                    << (is_specialization_of<std::tuple<int>, std::tuple>() ? "true": "false") << '\n';
    }

    inline auto test_apply() {
        std::tuple<int, double, char> test_tuple {1, 1.2, 'a'};
        apply(test_tuple, [](auto ... args) {
            std::cout << "tuple ( ";
            ((std::cout << args << " | "), ...);
            std::cout << " )\n";
        });
    }

}

#endif //EYE_DETAIL_HPP
