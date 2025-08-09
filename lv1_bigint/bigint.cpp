#include <string>
#include <iostream>
#include "bigint.hpp"

bigint::bigint() : digit("0") {
}

bigint::bigint(unsigned long long num) : digit(std::to_string(num)) {
}

bigint::bigint(const bigint &src) : digit(src.digit) {
}

bigint& bigint::operator=(const bigint& src) {
    if (this != &src)
        digit = src.digit;
    return (*this);
}

bigint::~bigint() {
}

const std::string& bigint::get_digit() const {
    return digit;
}

std::ostream& operator<<(std::ostream& lhs, bigint& rhs) {
    lhs << rhs.get_digit();
    return lhs;
}

int main() {
    bigint a;
    bigint b(a);
    bigint c(100);
    bigint d = c;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    return 0;
}
