//
// Created by mbero on 11/07/2025.
//

#ifndef MAPPING_HPP
#define MAPPING_HPP
#include <complex>
#include <future>
#include <type_traits>
#include <vector>

namespace pipeline {
    template<typename Fn>
    class for_each {
        Fn fn_;
    public:
        explicit for_each(Fn fn) : fn_(fn) {}

        template<typename Container>
        auto operator()(Container&& args) -> decltype(auto) {
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
}

#endif //MAPPING_HPP
