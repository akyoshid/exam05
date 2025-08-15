#include "set.hpp"
#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

set::set(searchable_bag& bag) : bag(bag) {
}

set::set(const set& src) : bag(src.bag) {
}

set& set::operator=(const set& src) {
    if (this != &src)
        bag = src.bag;
    return *this;
}

set::~set() {
}

void set::insert(int item) {
    if (has(item) == false)
        bag.insert(item);
}

void set::insert(int* items, int count) {
    for (int i = 0; i < count; ++i)
        insert(items[i]);
}

void set::print() const {
    bag.print();
}

void set::clear() {
    bag.clear();
}

bool set::has(int item) const {
    return bag.has(item);
}

const searchable_bag& set::get_bag() const {
    return bag;
}
