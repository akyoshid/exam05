#pragma once

#include "searchable_bag.hpp"

class set {
 public:
    set(searchable_bag &bag);
    set(const set& src);
    set& operator=(const set& src);
    ~set();
    void insert(int item);
    void insert(int* items, int count);
    void print() const;
    void clear();
    bool has(int item) const;
    const searchable_bag& get_bag() const;
 private:
    set() = delete;
    searchable_bag &bag;
};
