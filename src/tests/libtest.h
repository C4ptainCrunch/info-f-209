#include <vector>
#include <iostream>

#define TEST() int main(){ std::vector<func_struct> test_vector = TESTVEC; return test(test_vector); }

#define T(func) {#func, func}

typedef void (*test_func) (void);

struct func_struct {
    std::string name;
    test_func ptr;
};

int test(std::vector<func_struct> testvec);