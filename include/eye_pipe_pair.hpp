//
// Created by mbero on 12/07/2025.
//

#ifndef EYE_PIPE_PAIR_HPP
#define EYE_PIPE_PAIR_WISE_HPP
#include "../include/eye_detail.hpp"

namespace eyepipe::pipeline {
    template<typename T1, typename T2>
    class pipe_pair {
        T1 left_;
        T2 right_;
    public:
        pipe_pair(T1 left, T2 right): left_(left), right_(right) {}

        template<typename ...T>
        auto operator()(T&& ... args) -> decltype(auto) {
            using lhs_result_type = std::result_of_t<T1(T...)>;
            if constexpr (!std::is_same_v<lhs_result_type, void>) {
                return right_(left_(std::forward<T>(args)...));
            } else {
                left_(std::forward<T>(args)...);
                right_();
            }
        }

        template<typename T3>
        auto operator | (T3&& rhs) -> pipe_pair<pipe_pair<T1, T2>, T3> {
            return pipe_pair<pipe_pair<T1, T2>, T3>(*this, std::forward<T3>(rhs));
        }

        auto pipe(T1&& t1, T2&& t2) -> pipe_pair {
            return pipe_pair(std::forward<T1>(t1), std::forward<T2>(t2));
        }

        template<typename ...T>
        auto pipe(T1&& t1, T2&& t2, T&&... args) -> pipe_pair {
            return pipe(pipe(std::forward<T1>(t1), std::forward<T2>(t2)), std::forward<T>(args)...);
        }
    };
}
#endif //PIPE_PAIR_WISE_HPP
