#include <vector>
#include <iostream>
#include <exception>

#define TEST() int main(){ std::vector<func_struct> test_vector = TESTVEC; return test(test_vector); }

#define T(func) {#func, func}

typedef void (*test_func) (void);

struct func_struct {
    std::string name;
    test_func ptr;
};

int test(std::vector<func_struct> testvec);

void assert(bool value, std::string message="Assert failed");

class AssertFail: public std::exception {
    public:
        AssertFail(std::string message);
        std::string what();

    private:
        std::string message;
};