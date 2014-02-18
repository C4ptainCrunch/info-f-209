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

void assertFalse(bool value, std::string message="");
template<typename T>
void assertNull(T value, std::string message="");
template<typename T>
void assertNotNull(T value, std::string message="");
template<typename T, typename U>
void assertEqual(T value1, U value2, std::string message="");

class AssertFail: public std::exception {
    public:
        AssertFail(std::string message);
        std::string what();

    private:
        std::string message;
};
