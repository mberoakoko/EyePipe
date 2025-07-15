//
// Created by mbero on 16/07/2025.
//

#ifndef EYPE_PIPE_FORK_INTO_HPP
#define EYPE_PIPE_FORK_INTO_HPP
#include "eye_detail.hpp"
#include "eye_functional.hpp"
#include <bits/stdc++.h>

namespace eye_pipe::pipeline {

    template<typename Fn, typename ...Fns>
    class fork_into {
        std::tuple<Fn, Fns...> fns_;
    public:
        explicit fork_into(Fn first, Fns... others): fns_{first, others...} {}

        template<typename ...Args>
        auto operator() (Args... args) -> decltype(auto) {
            using result_type = std::result_of_t<Fn(Args...)>;
            std::vector<std::future<result_type>> results{};
            auto apply_fn = [&results, args_tuple = std::tuple<Args...>(std::forward<Args>(args)...)](auto fn) {

                auto unpack_operator = [](auto tuple, auto fn){ pipeline::apply(tuple, fn);};
                results.push_back(
                    std::async(std::launch::async | std::launch::deferred, unpack_operator, args_tuple, fn)
                    );
            };
        }
    };

}

#endif //EYPE_PIPE_FORK_INTO_HPP
