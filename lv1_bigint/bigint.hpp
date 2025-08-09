#ifndef BIGINT_HPP_
# define BIGINT_HPP_

# include <string>

class bigint {
 public:
    bigint();
    bigint(unsigned long long num);
    bigint(const bigint &src);
    bigint& operator=(const bigint& src);
    ~bigint();
    const std::string& get_digit() const;
 private:
    std::string digit;
};

std::ostream& operator<<(std::ostream& lhs, bigint& rhs);

#endif
