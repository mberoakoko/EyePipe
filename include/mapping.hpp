//
// Created by mbero on 11/07/2025.
//

#ifndef MAPPING_HPP
#define MAPPING_HPP
#include <iostream>
#include <complex>
#include <future>
#include <type_traits>
#include <vector>

namespace eye_pipe::pipeline {


    template<typename Fn>
    class for_each {
        Fn fn_;
    public:
        explicit for_each(Fn fn) : fn_(fn) {}

        template<typename Container>
        auto operator()(Container&& args) -> decltype(auto) {
            // ge
            using result_tupe = std::result_of_t<Fn(typename std::decay_t<Container>::value_type&)>;
            if constexpr (std::is_same_v<result_tupe, void>) {
                std::vector<std::future<result_tupe>> futures{};
                for (auto & arg: std::forward<Container>(args)) {
                    futures.push_back(std::async(std::launch::async | std::launch::deferred, fn_, arg));
                }
                for (auto & future: futures) {
                    future.get();
                }
            } else {
                std::vector<result_tupe> results {};
                std::vector<std::future<result_tupe>> futures{};
                for (auto & arg: std::forward<Container>(args)) {
                    futures.push_back(std::async(std::launch::async | std::launch::deferred, fn_, arg));
                }

                for (auto & future: futures ) {
                    results.push_back(future.get());
                }
                return results;
            }
        }
    };

    template<typename T>
    inline auto print_something_ = [] (T something) {
        std::cout << something << std::endl;
    };

    template<typename T>
    inline auto add_one_ = [](T something) {
        return something + 1;
    };

    inline auto test_for_each() -> void {
        auto entity = for_each{print_something_<std::string>};
        entity(std::vector<std::string>{"hello ", "world ", "I dont know ", "if ", "this ", "can ", "work "});
        auto adder_for_each = for_each(add_one_<int>);
        auto result = adder_for_each(std::vector<int>{1, 2, 4, 5});
        auto int_printer = for_each{print_something_<int>};
        int_printer(result);
    }
}

#endif //MAPPING_HPP
