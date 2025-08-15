#pragma once

#include <string>
#include <iostream>

class bigint {
 public:
    bigint();
    bigint(unsigned long long num);
    bigint(const bigint& src);
    bigint& operator=(const bigint& src);
    ~bigint();
    bigint operator+(const bigint& rhs) const;
    bigint& operator+=(const bigint& rhs);
    bigint& operator++();
    bigint operator++(int);
    bigint operator<<(unsigned long long rhs) const;
    bigint& operator<<=(unsigned long long rhs);
    bigint operator>>(unsigned long long rhs) const;
    bigint& operator>>=(unsigned long long rhs);
    std::string get_digit() const;
 private:
    bigint(const std::string& str);
    std::string digit;
};

std::ostream& operator<<(std::ostream& lhs, const bigint& rhs);
