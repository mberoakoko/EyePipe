#include <iostream>
#include "include/eye_detail.hpp"
#include "include/mapping.hpp"
#include "include/eye_pipe_from.hpp"

int main() {
    eye_pipe::pipeline::run_test_is_tuple_t();
    eye_pipe::pipeline::test_specialization();
    eye_pipe::pipeline::test_apply();
    eye_pipe::pipeline::test_for_each();
    eye_pipe::pipeline::test_from_functions();
    eye_pipe::pipeline::test_func_closure();
    return 0;

}