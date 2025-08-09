#include <string>
#include <iostream>
#include <algorithm>
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

std::ostream& operator<<(std::ostream& lhs, const bigint& rhs) {
    lhs << rhs.get_digit();
    return lhs;
}

bigint::bigint(const std::string& digit) : digit(digit) {
}

bigint bigint::operator+(const bigint& rhs) const {
    std::string a = this->digit;
    std::string b = rhs.digit;
    std::string result = "";
    size_t a_len = a.length();
    size_t b_len = b.length();
    int carry = 0;
    for (size_t i = 0; i < a_len || i < b_len; ++i) {
        int sum = carry;
        if (i < a_len)
            sum += a[a_len - i - 1] - '0';
        if (i < b_len)
            sum += b[b_len - i - 1] - '0';
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    if (carry != 0)
        result.push_back(carry + '0');
    std::reverse(result.begin(), result.end());
    return bigint(result);
}

bigint& bigint::operator+=(const bigint& rhs) {
    *this = *this + rhs;
    return *this;
}

bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint ret(*this);
    ++(*this);
    return ret;
}

bigint bigint::operator<<(const unsigned int shift) const {
    if (this->digit == "0")
        return bigint(0);
    else {
        bigint ret(*this);
        ret.digit.append(shift, '0');
        return ret;
    }
}

bigint& bigint::operator<<=(const unsigned int shift) {
    *this = *this << shift;
    return *this;
}

bigint bigint::operator>>(const unsigned int shift) const {
    size_t len = this->digit.length();
    if (shift == 0)
        return *this;
    else if (len <= shift)
        return bigint(0);
    else
        return bigint(this->digit.substr(0, len - shift));
}

bigint& bigint::operator>>=(const unsigned int shift) {
    *this = *this >> shift;
    return *this;
}

bool bigint::operator==(const bigint& rhs) const {
    return this->digit == rhs.digit;
}

bool bigint::operator!=(const bigint& rhs) const {
    return !(*this == rhs);
}

bool bigint::operator<(const bigint& rhs) const {
    size_t l_len = this->digit.length();
    size_t r_len = rhs.digit.length();
    if (l_len == r_len)
        return this->digit < rhs.digit;
    else
        return l_len < r_len;
}

bool bigint::operator<=(const bigint& rhs) const {
    return !(*this > rhs);
}

bool bigint::operator>(const bigint& rhs) const {
    return rhs < *this;
}

bool bigint::operator>=(const bigint& rhs) const {
    return !(*this < rhs);
}
