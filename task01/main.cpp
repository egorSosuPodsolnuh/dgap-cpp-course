#include <iostream>
#include "complex.h"

int main()
{
    Complex a, b(2.0), c(1.0, 1.0);

    std::cin >> a;
    std::cout << a << ", " << b << ", abs: " << b.abs() << std::endl;

    a = b + c.conj();
    a = a * Complex(2.0);
    a += c;
    c = a + 2 * b;

    std::cout << a << ", " << c << std::endl;

    // Add your usage examples

    return 0;
}


