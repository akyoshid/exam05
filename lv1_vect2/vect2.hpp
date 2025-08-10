#ifndef VECT2_HPP_
# define VECT2_HPP_

# include <iostream>

class vect2 {
 public:
    vect2();
    vect2(int x, int y);
    vect2(const vect2& src);
    vect2& operator=(const vect2& src);
    ~vect2();
    int get_x() const;
    int get_y() const;
 private:
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& lhs, const vect2& rhs);

#endif
