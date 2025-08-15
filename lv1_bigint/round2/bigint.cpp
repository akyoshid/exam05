#include <string>
#include <algorithm>
#include "bigint.hpp"

bigint::bigint() : digit("0") {
}

bigint::bigint(unsigned long long num) : digit(std::to_string(num)) {
}

bigint::bigint(const bigint& src) : digit(src.digit) {
}

bigint& bigint::operator=(const bigint& src) {
    if (this != &src)
        digit = src.digit;
    return *this;
}

bigint::~bigint() {
}

bigint bigint::operator+(const bigint& rhs) const {
    std::string result = "";
    int l_len = this->digit.length();
    int r_len = rhs.digit.length();
    int carry = 0;
    for (int i = 0; (i < l_len || i < r_len); ++i) {
        int sum = carry;
        if (i < l_len)
            sum += this->digit[l_len - i - 1] - '0';
        if (i < r_len)
            sum += rhs.digit[r_len - i - 1] - '0';
        result.push_back('0' + sum % 10);
        carry = sum / 10;
    }
    if (carry > 0)
        result.push_back('0' + carry);
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
    *this += bigint(1);
    return ret;
}

std::string bigint::get_digit() const {
    return digit;
}

bigint bigint::operator<<(unsigned long long rhs) const {
    bigint ret(*this);
    ret.digit.append(rhs, '0');
    return ret;
}

bigint& bigint::operator<<=(unsigned long long rhs) {
    *this = *this << rhs;
    return *this;
}

bigint bigint::operator>>(unsigned long long rhs) const {
    size_t len = digit.length();
    if (len <= rhs)
        return bigint(0);
    else
        return bigint(digit.substr(0, len - rhs));
}

bigint& bigint::operator>>=(unsigned long long rhs) {
    *this = *this >> rhs;
    return *this;
}

bigint::bigint(const std::string& str) : digit(str) {
}

std::ostream& operator<<(std::ostream& lhs, const bigint& rhs) {
    lhs << rhs.get_digit();
    return lhs;
}
