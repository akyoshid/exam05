#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() : searchable_bag(), tree_bag() {
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& src)
    : searchable_bag(), tree_bag(src) {
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& src) {
    if (this != &src)
        tree_bag::operator=(src);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag() {
}

bool searchable_tree_bag::has(int item) const {
    return search_node(tree, item);
}

bool searchable_tree_bag::search_node(node* current_node, int item) {
    if (current_node == nullptr)
        return false;
    else if (current_node->value > item)
        return search_node(current_node->l, item);
    else if (current_node->value < item)
        return search_node(current_node->r, item);
    else
        return true;
}
