#include <iostream>

#include "matrix.hpp"

int main() {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);

    Matrix s(a);
    s.add(b);
    Matrix m(a);
    m.mul(b);

    a.set(0, 0, 5.0);
    a.print(std::cout);
    std::cout << a.rows() << "x" << a.cols() << std::endl;

    std::cout << "sum(a) = " << a.sum() << std::endl;
    std::cout << "sum(s) = " << s.sum() << std::endl;
    std::cout << "sum(m) = " << m.sum() << std::endl;
    return 0;
}
