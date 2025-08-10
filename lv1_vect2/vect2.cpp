#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {
}

vect2::vect2(int x, int y) : x(x), y(y) {
}

vect2::vect2(const vect2& src) : x(src.x), y(src.y) {
}

vect2& vect2::operator=(const vect2& src) {
    if (this != &src) {
        this->x = src.x;
        this->y = src.y;
    }
    return (*this);
}

vect2::~vect2() {
}

int vect2::get_x() const {
    return (x);
}

int vect2::get_y() const {
    return (y);
}

std::ostream& operator<<(std::ostream& lhs, const vect2& rhs) {
    lhs << rhs.get_x() << "," << rhs.get_y();
    return lhs;
}
