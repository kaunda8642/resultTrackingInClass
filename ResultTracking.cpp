// ResultTracking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>
#include <cassert>

template <typename Arg1, typename Arg2, typename Result>
class FunctionWrapper {
private:
    std::function<Result(Arg1, Arg2)> func;
    int apply_count = 0;
    Result last_result;

public:
    FunctionWrapper(std::function<Result(Arg1, Arg2)> f) : func(f) {}

    Result apply(Arg1 a, Arg2 b) {
        last_result = func(a, b);
        apply_count++;
        return last_result;
    }

    int getApplyCount() const {
        return apply_count;
    }

    Result getLastResult() const {
        return last_result;
    }
};

int main() {
    // Function 1: Addition
    auto add = [](int a, int b) { return a + b; };
    FunctionWrapper<int, int, int> fw1(add);
    assert(fw1.apply(2, 3) == 5);
    assert(fw1.getApplyCount() == 1);
    assert(fw1.getLastResult() == 5);

    // Apply again
    assert(fw1.apply(10, -4) == 6);
    assert(fw1.getApplyCount() == 2);
    assert(fw1.getLastResult() == 6);

    // Function 2: Concatenation
    auto concat = [](std::string a, std::string b) { return a + b; };
    FunctionWrapper<std::string, std::string, std::string> fw2(concat);
    assert(fw2.apply("Hello, ", "World!") == "Hello, World!");
    assert(fw2.getApplyCount() == 1);
    assert(fw2.getLastResult() == "Hello, World!");

    // Function 3: Max of two doubles
    auto max_double = [](double a, double b) { return (a > b) ? a : b; };
    FunctionWrapper<double, double, double> fw3(max_double);
    assert(fw3.apply(3.14, 2.72) == 3.14);
    assert(fw3.getApplyCount() == 1);
    assert(fw3.getLastResult() == 3.14);

    // Function 4: Reusing the same function as fw1
    FunctionWrapper<int, int, int> fw4(add);
    assert(fw4.apply(7, 8) == 15);
    assert(fw4.getApplyCount() == 1);
    assert(fw4.getLastResult() == 15);

    std::cout << "All tests passed.\n";
    return 0;
}


