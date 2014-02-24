#ifndef LIBTEST_H
#define LIBTEST_H

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

class AssertFail: public std::exception {
    public:
        AssertFail(std::string message, int line, std::string file, std::string func);
        std::string what();

    private:
        std::string message;
        std::string file;
        std::string func;
        int line;
};

#define ASSERT(value, message) assert(value, message, __LINE__, __FILE__, __func__)
//#define ASSERT(value) ASSERT(value, "")

#define ASSERT_FALSE(value, message) assertFalse(value, message, __LINE__, __FILE__, __func__)
//#define ASSERT_FALSE(value) ASSERT_FALSE(value, "")

#define ASSERT_NULL(value, message) assertNull(value, message, __LINE__, __FILE__, __func__)
//#define ASSERT_NULL(value) ASSERT_NULL(value, "")

#define ASSERT_NOT_NULL(value, message) assertNotNull(value, message, __LINE__, __FILE__, __func__)
//#define ASSERT_NOT_NULL(value) ASSERT_NOT_NULL(value, "")

#define ASSERT_EQUAL(value1, value2, message) assertEqual(value, message, __LINE__, __FILE__, __func__)
//#define ASSERT_EQUAL(value1, value2) ASSERT_EQUAL(value1, value2, "")

void assert(bool value, std::string message="", int line=-1, std::string file="", std::string func="");

void assertFalse(bool value, std::string message="", int line=-1, std::string file="", std::string func="");

template<typename T>
void assertNull(T value, std::string message="", int line=-1, std::string file="", std::string func=""){
    assert(value == NULL, message, line, file, func);
}

template<typename T>
void assertNotNull(T value, std::string message="", int line=-1, std::string file="", std::string func=""){
    assert(value != NULL, message, line, file, func);
}
template<typename T, typename U>
void assertEqual(T value1, U value2, std::string message="", int line=-1, std::string file="", std::string func=""){
    assert(value1 != value2, message, line, file, func);
}

#endif // LIBTEST_H
