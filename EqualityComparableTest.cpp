#include <iostream>
#include <concepts>
#include <stdlib.h>

template<typename T>
concept Equality_Comparable = requires(T a, T b) {
        { a==b } -> std::convertible_to<bool>;
        { a!=b } -> std::convertible_to<bool>;
    };

template<Equality_Comparable T>
void print_t(T value)
{
    std::cout << value << std::endl;
}

struct a {
    int z;
};

int main() {

    static_assert(Equality_Comparable<a>);

    std::cout << "Asserted" << std::endl;
}
