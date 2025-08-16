#include "searchable_tree_bag.hpp"
#include "searchable_bag.hpp"
#include "tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : searchable_bag(), tree_bag() {
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& src)
    : searchable_bag(), tree_bag(src) {
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& src) {
    if (this != &src)
        *this = src;
    return *this;
}

searchable_tree_bag::~searchable_tree_bag() {
}

bool searchable_tree_bag::has(int item) const {
    return check_node(tree, item);
}

bool searchable_tree_bag::check_node(node* node, int item) {
    if (node == nullptr)
        return false;
    else {
        if (node->value < item)
            check_node(node->l, item);
        else if (node->value > item)
            check_node(node->r, item);
        else
            true;
    }
}
