#pragma once

#include "searchable_bag.hpp"
#include "tree_bag.hpp"

class searchable_tree_bag : public searchable_bag, public tree_bag {
 public:
    searchable_tree_bag();
    searchable_tree_bag(const searchable_tree_bag& src);
    searchable_tree_bag& operator=(const searchable_tree_bag& src);
    ~searchable_tree_bag();
    bool has(int item) const;
 private:
    static bool check_node(node* tree, int item);
};
