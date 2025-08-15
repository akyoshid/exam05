#ifndef BIGINT_HPP_
# define BIGINT_HPP_

# include <string>
# include <iostream>

class bigint {
 public:
    bigint();
    bigint(unsigned long long num);
    bigint(const bigint &src);
    bigint& operator=(const bigint& src);
    ~bigint();
    const std::string& get_digit() const;
    bigint operator+(const bigint& rhs) const;
    bigint& operator+=(const bigint& rhs);
    bigint& operator++();
    bigint operator++(int);
    bigint operator<<(const unsigned int shift) const;
    bigint& operator<<=(const unsigned int shift);
    bigint operator>>(const unsigned int shift) const;
    bigint& operator>>=(const unsigned int shift);
    bool operator==(const bigint& rhs) const;
    bool operator!=(const bigint& rhs) const;
    bool operator<(const bigint& rhs) const;
    bool operator<=(const bigint& rhs) const;
    bool operator>(const bigint& rhs) const;
    bool operator>=(const bigint& rhs) const;
 private:
    bigint(const std::string& digit);
    std::string digit;
};

std::ostream& operator<<(std::ostream& lhs, const bigint& rhs);

#endif
