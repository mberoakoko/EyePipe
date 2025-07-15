//
// Created by mbero on 11/07/2025.
//

#ifndef FUNCTIONAL_HPP
#define FUNCTIONAL_HPP
#include "../include/eye_detail.hpp"

namespace eye_pipe::pipeline {

    template<typename Fn>
    class func_closure {
        Fn fn_;
    public:
        explicit func_closure(Fn func): fn_(func){};

        /**
         *
         * @tparam Args  A parameter pack representing the types of the arguments to be passed to the function.
         * @param args A parameter pack representing the arguments to be passed to the function.
         * @return The return type of the function is deduced from the return type of the underlying function object fn_ when called with the same arguments.
         */
        template<typename ... Args>
        auto operator()(Args ... args) -> decltype(fn_(args...)) {
            return fn_(args...);
        }

        template<typename ... Args>
        static constexpr auto is_invocable_on() {
            return std::is_invocable_v<Fn, Args...>;
        }

        template<typename T>
        auto operator | (T&& rhs) -> eye_pipe::pipeline::pipe_pair<func_closure<Fn>, T> {
            return eye_pipe::pipeline::pipe_pair<func_closure<Fn>, T>(*this, std::forward<T>(rhs));
        }

    };

    inline auto test_func_closure() -> void {
        auto printer_fn_closure = func_closure([](auto val) -> void {std::cout << val;});
        printer_fn_closure("hello world\n");
        auto identity_fn_closure = func_closure([]<typename Arg>(Arg val) -> Arg {return val;});
        printer_fn_closure(identity_fn_closure("hello world\n"));
    }
}

#endif //FUNCTIONAL_HPP
