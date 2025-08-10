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

int& vect2::operator[](const int index) {
    if (index == 0)
        return this->x;
    else
        return this->y;
}

const int& vect2::operator[](const int index) const {
    if (index == 0)
        return this->x;
    else
        return this->y;
}

vect2& vect2::operator++() {
    ++(this->x);
    ++(this->y);
    return *this;
}

vect2 vect2::operator++(int) {
    vect2 ret(*this);
    ++(this->x);
    ++(this->y);
    return ret;
}

vect2& vect2::operator--() {
    --(this->x);
    --(this->y);
    return *this;
}

vect2 vect2::operator--(int) {
    vect2 ret(*this);
    --(this->x);
    --(this->y);
    return ret;
}

vect2 vect2::operator+(const vect2& rhs) const {
    vect2 ret(*this);
    ret.x += rhs.x;
    ret.y += rhs.y;
    return ret;
}

vect2& vect2::operator+=(const vect2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

vect2 vect2::operator-(const vect2& rhs) const {
    vect2 ret(*this);
    ret.x -= rhs.x;
    ret.y -= rhs.y;
    return ret;
}

vect2& vect2::operator-=(const vect2& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

vect2 vect2::operator*(const int rhs) const {
    vect2 ret(*this);
    ret.x *= rhs;
    ret.y *= rhs;
    return ret;
}

vect2& vect2::operator*=(const int rhs) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}

vect2 vect2::operator-() const {
    vect2 ret(*this);
    ret.x *= -1;
    ret.y *= -1;
    return ret;
}

bool vect2::operator==(const vect2& rhs) const {
    if (this->x == rhs.x && this->y == rhs.y)
        return true;
    else
        return false;
}

bool vect2::operator!=(const vect2& rhs) const {
    return !(*this == rhs);
}

vect2 operator*(const int lhs, const vect2& rhs) {
    return vect2(lhs * rhs.get_x(), lhs * rhs.get_y());
}

std::ostream& operator<<(std::ostream& lhs, const vect2& rhs) {
    lhs << rhs.get_x() << "," << rhs.get_y();
    return lhs;
}
