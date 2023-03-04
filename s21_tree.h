#ifndef SRC_21_BINARY_TREE_TREE_H
#define SRC_21_BINARY_TREE_TREE_H
#include <iostream>
#include <vector>


namespace s21 {
    template <typename Key ,typename Compare = std::less<Key>>
    class BinaryTree {
    private:
        class Iterator;

        class ConstIterator;

        class Node;

    public:
        using key_type = Key;
        using value_type = Key;
        using reference = key_type&;
        using const_reference = const key_type&;
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        using size_type = size_t;

    public:
        BinaryTree() : before_root_(new Node()), nil_(new Node()), size_(0) {
            before_root_->parent_ = nil_;
        };

        BinaryTree(const BinaryTree<value_type, Compare> &binaryTree) : BinaryTree() {
            if (!binaryTree.empty()) {
                s21_copy_tree(binaryTree);
            }
        }

        BinaryTree(BinaryTree &&binaryTree) noexcept : BinaryTree() {
            if (!binaryTree.empty()) {
                *this = std::move(binaryTree);
            }
        }

        BinaryTree<value_type, Compare> &operator=(const BinaryTree<value_type, Compare> &binaryTree) {
            if (&binaryTree != this && !binaryTree.empty()) {
                clear();
                s21_copy_tree(binaryTree);
            }
            return *this;
        }

        BinaryTree<value_type, Compare> &operator=(
                BinaryTree<value_type, Compare> &&binaryTree) noexcept {
            if (&binaryTree != this) {
                clear();
                s21_swap(binaryTree);
                binaryTree.clear();
            }
            return *this;
        }

        ~BinaryTree() {
            clear();
            delete before_root_->parent_;
            delete before_root_;
            before_root_ = nil_ = nullptr;
        }

        iterator begin() noexcept {
            return iterator(s21_min_node(before_root_->parent_), this);
        }

        iterator end() noexcept { return iterator(nil_, this); }

        const_iterator cbegin() const noexcept {
            return const_iterator(s21_min_node(before_root_->parent_), this);
        }

        const_iterator cend() const noexcept { return const_iterator(nil_, this); }

        bool empty() const noexcept { return size_ == 0; }

        size_type size() const noexcept { return size_; }

        size_type max_size() const noexcept { return SIZE_MAX / (sizeof(Node) * 2); }

        void clear() noexcept {
            if (size_ != 0) {
                s21_delete_all(before_root_->parent_);
            }
            before_root_->parent_ = nil_;
            size_ = 0;
        }

        iterator insert_not_unique(const value_type &value) noexcept {
            Node *current = new Node(value);
            iterator res = insert(current, false).first;
            return res;
        }

        std::pair<iterator, bool> insert_unique(const value_type &value) noexcept {
            Node *current = new Node(value);
            std::pair<iterator, bool> res = insert(current, true);
            if (res.second == false) {
                delete current;
            }
            return res;
        }

        std::pair<iterator, bool> insert(Node *new_node, bool is_unique) noexcept {
            Node *current_node = before_root_->parent_;
            Node *parent_for_new_node = nullptr;
            while (current_node != nil_) {
                parent_for_new_node = current_node;
                if (compare_(new_node->key_, current_node->key_)) {
                    current_node = current_node->left_;
                } else {
                    if (is_unique && !compare_(current_node->key_, new_node->key_)) {
                        return std::pair<iterator, bool>(iterator(current_node, this), false);
                    }
                    current_node = current_node->right_;
                }
            }
            s21_nil_init(new_node);
            if (parent_for_new_node == nullptr) {
                before_root_->parent_ = new_node;
                new_node->red_ = false;
                new_node->parent_ = nil_;
            } else {
                new_node->parent_ = parent_for_new_node;
                if (compare_(new_node->key_, parent_for_new_node->key_)) {
                    parent_for_new_node->left_ = new_node;
                } else {
                    parent_for_new_node->right_ = new_node;
                }
            }
            ++size_;
            s21_balancing_tree_after_insert(new_node);
            if (before_root_->parent_->red_) {
                before_root_->parent_->red_ = false;
            }
            return std::pair<iterator, bool>(iterator(new_node, this), true);
        }

        void erase(iterator pos) noexcept {
            Node *current_node = pos.get_node();
            if (current_node != nullptr && current_node != nil_) {
                s21_delete_node(current_node);
            }
        }

        void merge(BinaryTree<value_type, Compare> &other) noexcept {
            iterator it = other.begin();
            while (it != other.end()) {
                Node *other_current = it.get_node();
                ++it;

                if (other_current->right_ != other.end().get_node()) {
                    other_current->right_->parent_ = other_current->parent_;
                }
                if (other_current->parent_->left_ == other_current) {
                    other_current->parent_->left_ = other.end().get_node();
                } else if (other_current->parent_->right_ == other_current) {
                    other_current->parent_->right_ = other.end().get_node();
                }
                if (other_current->parent_ == other.end().get_node()) {
                    other.before_root_->parent_ = other_current->right_;
                }
                other_current->red_ = true;
                insert(other_current, false);
                --other.size_;
            }
        }

        void unique_merge(BinaryTree<value_type, Compare> &other) noexcept {
            iterator it = other.begin();
            while (it != other.end()) {
                Node *other_current = it.get_node();
                ++it;
                if (!contains(other_current->key_)) {
                    other_current = other.s21_cut_node(other_current);
                    if (other_current->parent_ == other.nil_) {
                        other.before_root_->parent_ = other_current->right_;
                    }
                    other_current->red_ = true;
                    insert(other_current, false);
                    --other.size_;
                }
            }
        }

        iterator find(const_reference value) noexcept {
            auto it = lower_bound(value);
            return (it == end() || compare_(value, *it)) ? end() : it;
        }

        bool contains(const Key &key) noexcept {
            iterator it = find(key);
            return it != end();
        }

        iterator lower_bound(const Key &key) noexcept {
            Node *current = before_root_->parent_;
            Node *result = nil_;
            while (current != nil_) {
                if (!compare_(current->key_, key)) {
                    result = current;
                    current = current->left_;
                } else {
                    current = current->right_;
                }
            }
            return iterator(result, this);
        }

        iterator upper_bound(const Key &key) noexcept {
            Node *current = before_root_->parent_;
            Node *result = nil_;
            while (current != nil_) {
                if (compare_(key, current->key_)) {
                    result = current;
                    current = current->left_;
                } else {
                    current = current->right_;
                }
            }
            return iterator(result, this);
        }

        void s21_swap(BinaryTree<value_type, Compare> &binaryTree) noexcept {
            std::swap(before_root_->parent_, binaryTree.before_root_->parent_);
            std::swap(size_, binaryTree.size_);
            std::swap(nil_, binaryTree.nil_);
            std::swap(compare_, binaryTree.compare_);
        }

        template <class... Args>
        std::vector<std::pair<iterator, bool>> emplace(Args &&...args) noexcept {
            std::vector<std::pair<iterator, bool>> res_vector;
            for (auto value : {std::forward<Args>(args)...}) {
                Node *new_node = new Node(value);
                std::pair<iterator, bool> temp = insert(new_node, false);
                res_vector.push_back(temp);
            }
            return res_vector;
        }

        template <class... Args>
        std::vector<std::pair<iterator, bool>> emplace_uniq(Args &&...args) noexcept {
            std::vector<std::pair<iterator, bool>> res_vector;
            for (auto value : {std::forward<Args>(args)...}) {
                Node *new_node = new Node(value);
                //  Node *new_node;
                // new_node = new Node(static_cast<value_type>(value));
                std::pair<iterator, bool> temp = insert(new_node, true);
                if (!temp.second) {
                    delete new_node;
                }
                res_vector.push_back(temp);
            }
            return res_vector;
        }

    private:
        void s21_nil_init(Node *current_node) {
            current_node->left_ = current_node->right_ = nil_;
        }

        void s21_delete_all(Node *current) {
            if (current != nil_) {
                s21_delete_all(current->left_);
                s21_delete_all(current->right_);
                delete current;
            }
        }

        void s21_copy_tree(const BinaryTree &binaryTree) {
            for (auto it = binaryTree.cbegin(); it != binaryTree.cend(); ++it) {
                insert_not_unique(*it);
            }
        }

        // https://temofeev.ru/info/articles/udalenie-uzlov-iz-krasno-chyernogo-dereva/

        void s21_delete_node(Node *del) {
            if (s21_is_red(del) && del->left_ != nil_ && del->right_ != nil_) {
                Node *left_max = s21_max_node(del->left_);
//      std::swap(left_max->key_, del->key_);
                s21_swap_node(del, left_max);
                s21_delete_node(del);
            } else if (s21_is_black(del) && del->left_ != nil_ && del->right_ != nil_) {
                Node *left_max = s21_max_node(del->left_);
//      std::swap(left_max->key_, del->key_);
                s21_swap_node(del, left_max);
                s21_delete_node(del);
            } else if (s21_is_black(del) &&
                       (del->left_ != nil_ || del->right_ != nil_)) {
                // у черного узла - если один ребенок, то точно красный без детей
                Node *son = del->left_ != nil_ ? del->left_ : del->right_;
//      std::swap(son->key_, del->key_);
                s21_swap_node(del, son);
                s21_delete_node(del);
            } else if (s21_is_red(del) && del->right_ == nil_ && del->left_ == nil_) {
                s21_delete_son(del);
            } else if (s21_is_black(del) && del->right_ == nil_ && del->left_ == nil_) {
                Node *parent = del->parent_;
                bool is_left = del == parent->left_;
                s21_delete_son(del);
                if (parent != nil_) {
                    is_left ? s21_balancing_tree_after_erase_left(parent)
                            : s21_balancing_tree_after_erase_right(parent);
                } else {
                    before_root_->parent_ = nil_;
                }
            }
        }

        void s21_delete_son(Node *son) {
            s21_cut_son(son);
            delete son;
            --size_;
        }

        Node *s21_cut_node(Node *current) {
            Node *result = current;
            if (s21_is_red(current) && current->left_ != nil_ &&
                current->right_ != nil_) {
                Node *left_max = s21_max_node(current->left_);
                s21_swap_node(current, left_max);
//      std::swap(left_max->key_, current->key_);
                s21_cut_node(current);
                result = current;
            } else if (s21_is_black(current) && current->left_ != nil_ &&
                       current->right_ != nil_) {
                Node *left_max = s21_max_node(current->left_);
                s21_swap_node(current, left_max);
//      std::swap(left_max->key_, current->key_);
                s21_cut_node(current);
                result = current;
            } else if (s21_is_black(current) &&
                       (current->left_ != nil_ || current->right_ != nil_)) {
                // у черного узла - если один ребенок, то точно красный без детей
                Node *son = current->left_ != nil_ ? current->left_ : current->right_;
                s21_swap_node(current, son);
                s21_cut_node(current);
                result = current;
            } else if (s21_is_red(current) && current->right_ == nil_ &&
                       current->left_ == nil_) {
                s21_cut_son(current);
            } else if (s21_is_black(current) && current->right_ == nil_ &&
                       current->left_ == nil_) {
                Node *parent = current->parent_;
                bool is_left = current == parent->left_;
                s21_cut_son(current);
                if (parent != nil_) {
                    is_left ? s21_balancing_tree_after_erase_left(parent)
                            : s21_balancing_tree_after_erase_right(parent);
                } else {
                    before_root_->parent_ = nil_;
                }
            }
            return result;
        }

        void s21_cut_son(Node *son) {
            if (son == son->parent_->left_) {
                son->parent_->left_ = nil_;
            } else {
                son->parent_->right_ = nil_;
            }
        }


        /*
         * Исходим из того, что при вызове функции - current выше по дереву чем other
         * Т.е. если меняем отца с сыном, то current - это отец
         */
        void s21_swap_node(Node *current, Node *other) {
            if (before_root_->parent_ == current) {
                before_root_->parent_ = other;
            }
            if (current->parent_ != nullptr && current->parent_->right_ == current) {
                current->parent_->right_ = other;
            } else if (current->parent_ != nullptr && current->parent_->left_ == current) {
                current->parent_->left_ = other;
            }
            if (current != other->parent_ && other->parent_->right_ == other) {
                other->parent_->right_ = current;
            } else if (current != other->parent_ && other->parent_->left_ == other) {
                other->parent_->left_ = current;
            }
            if (current->right_ != nil_ && current->right_ != other) {
                current->right_->parent_ = other;
            }
            if (current->left_ != nil_ && current->left_ != other) {
                current->left_->parent_ = other;
            }
            if (other->left_ != nil_) {
                other->left_->parent_ = current;
            }
            if (other->right_ != nil_) {
                other->right_->parent_ = current;
            }
            s21_swap_parent(current, other);
            s21_swap_left_son(current, other);
            s21_swap_right_son(current, other);
            std::swap(current->red_, other->red_);
        }

        void s21_swap_parent(Node *current, Node *other) {
            std::swap(other->parent_, current->parent_);
            if (current->parent_ == current) {
                current->parent_ = other;
            }
        }

        void s21_swap_right_son(Node *current, Node *other) {
            std::swap(other->right_, current->right_);
            if (other->right_ == other) {
                other->right_ = current;
            }
        }

        void s21_swap_left_son(Node *current, Node *other) {
            std::swap(other->left_, current->left_);
            if (other->left_ == other) {
                other->left_ = current;
            }
        }

        //  https://habr.com/ru/company/otus/blog/521034/
        void s21_balancing_tree_after_erase_left(Node *current) {
            if (s21_is_red(current) && s21_is_black(current->right_) &&
                s21_is_black(current->right_->left_) &&
                s21_is_black(current->right_->right_)) {
                current->right_->red_ = true;
                current->red_ = false;
            } else if (s21_is_red(current) && s21_is_black(current->right_) &&
                       s21_is_red(current->right_->right_)) {
                current->red_ = false;
                current->right_->red_ = true;
                current->right_->right_->red_ = false;
                s21_rotate_left(current);
            } else if (s21_is_black(current) && s21_is_red(current->right_) &&
                       s21_is_black(current->right_->left_->left_) &&
                       s21_is_black(current->right_->left_->right_)) {
                current->right_->left_->red_ = true;
                current->right_->red_ = false;
                s21_rotate_left(current);
            } else if (s21_is_black(current) && s21_is_red(current->right_) &&
                       s21_is_red(current->right_->left_->right_)) {
                current->right_->left_->right_->red_ = false;
                s21_rotate_right(current->right_);
                s21_rotate_right(current);
            } else if (s21_is_black(current) && s21_is_black(current->right_) &&
                       s21_is_red(current->right_->left_)) {
                current->right_->left_->red_ = false;
                s21_rotate_right(current->right_);
                s21_rotate_right(current);
            } else {
                if (current->parent_ != nil_) {
                    s21_balancing_tree_after_erase_left(current->parent_);
                }
            }
        }

        void s21_balancing_tree_after_erase_right(Node *current) {
            if (s21_is_red(current) && s21_is_black(current->left_) &&
                s21_is_black(current->left_->left_) &&
                s21_is_black(current->left_->right_)) {
                current->left_->red_ = true;
                current->red_ = false;
            } else if (s21_is_red(current) && s21_is_black(current->left_) &&
                       s21_is_red(current->left_->right_)) {
                current->red_ = false;
                current->left_->red_ = true;
                current->left_->right_->red_ = false;
                s21_rotate_right(current);
            } else if (s21_is_black(current) && s21_is_red(current->left_) &&
                       s21_is_black(current->left_->right_->right_) &&
                       s21_is_black(current->left_->right_->left_)) {
                current->left_->right_->red_ = true;
                current->left_->red_ = false;
                s21_rotate_right(current);
            } else if (s21_is_black(current) && s21_is_red(current->left_) &&
                       s21_is_red(current->left_->right_->right_)) {
                current->left_->right_->right_->red_ = false;
                s21_rotate_left(current->left_);
                s21_rotate_left(current);
            } else if (s21_is_black(current) && s21_is_black(current->left_) &&
                       s21_is_red(current->left_->right_)) {
                current->left_->right_->red_ = false;
                s21_rotate_left(current->left_);
                s21_rotate_left(current);
            } else {
                if (current->parent_ != nil_) {
                    s21_balancing_tree_after_erase_right(current->parent_);
                }
            }
        }

        bool s21_is_red(Node *current) { return current != nullptr && current->red_; }

        bool s21_is_black(Node *current) {
            return current != nullptr && !current->red_;
        }

        Node *s21_max_node(Node *node) const noexcept {
            Node *result = node;
            if (result == cend().get_node()) {
                result = before_root_->parent_;
            }
            while (result != cend().get_node() && result->right_ != cend().get_node()) {
                result = result->right_;
            }
            return result;
        }

        Node *s21_node_prev(const Node *node) const noexcept {
            Node *result;
            if (node != cend().get_node()) {
                if (node->left_ != cend().get_node()) {
                    result = s21_max_node(node->left_);
                } else if (node == node->parent_->right_) {
                    result = node->parent_;
                } else {
                    while (node == node->parent_->left_) {
                        node = node->parent_;
                    }
                    result = node->parent_;
                }
            } else {
                result = s21_max_node(before_root_->parent_);
            }
            return result;
        }

        Node *s21_min_node(Node *node) const noexcept {
            Node *result = node;
            if (result == cend().get_node()) {
                result = before_root_->parent_;
            }
            while (result != cend().get_node() && result->left_ != cend().get_node()) {
                result = result->left_;
            }
            return result;
        }

        Node *s21_node_next(const Node *node) const noexcept {
            Node *result = const_cast<Node *>(node);
            if (node != cend().get_node() && node->right_ != nullptr) {
                if (node->right_ != cend().get_node()) {
                    result = s21_min_node(node->right_);
                } else if (node == node->parent_->left_) {
                    result = node->parent_;
                } else {
                    while (node == node->parent_->right_) {  // while x is a right son
                        node = node->parent_;
                    }
                    result = node->parent_;
                }
            }
            return result;
        }

        void s21_balancing_tree_after_insert(Node *current_node) {
            while (current_node != before_root_->parent_ &&
                   current_node->parent_->red_) {
                if (current_node->parent_ ==
                    current_node->parent_->parent_
                            ->left_) {  //  parent of cn - is left son
                    Node *node = current_node->parent_->parent_->right_;
                    if (node != nil_ && node->red_) {
                        current_node->parent_->red_ = false;
                        node->red_ = false;
                        current_node = current_node->parent_->parent_;
                        current_node->red_ = true;
                    } else {
                        if (current_node == current_node->parent_->right_) {
                            current_node = current_node->parent_;
                            s21_rotate_left(current_node);
                        }
                        current_node->parent_->red_ = false;
                        current_node->parent_->parent_->red_ = true;
                        s21_rotate_right(current_node->parent_->parent_);
                    }
                } else if (current_node->parent_ ==
                           current_node->parent_->parent_->right_) {
                    // parent of cn - is right son
                    Node *node = current_node->parent_->parent_->left_;
                    if (node != nil_ && node->red_) {
                        current_node->parent_->red_ = false;
                        node->red_ = false;
                        current_node = current_node->parent_->parent_;
                        if (before_root_->parent_ != current_node) {
                            current_node->red_ = true;
                        }
                    } else {
                        if (current_node == current_node->parent_->left_) {
                            current_node = current_node->parent_;
                            s21_rotate_right(current_node);
                        }
                        current_node->parent_->red_ = false;
                        current_node->parent_->parent_->red_ = true;
                        s21_rotate_left(current_node->parent_->parent_);
                    }
                } else if (current_node->parent_ == before_root_->parent_) {
                    break;
                }
            }
        }

        void s21_rotate_left(Node *node) {
            Node *right_son = node->right_;
            if (right_son != nil_) {
                Node *parent = node->parent_;
                right_son->parent_ = parent;
                if (parent != nil_) {
                    if (node == parent->left_) {
                        parent->left_ = right_son;
                    } else {
                        parent->right_ = right_son;
                    }
                } else {
                    before_root_->parent_ = right_son;
                    right_son->parent_ = nil_;
                }
                node->right_ = right_son->left_;
                if (right_son->left_ != nil_) {
                    right_son->left_->parent_ = node;
                }
                right_son->left_ = node;
                node->parent_ = right_son;
            }
        }

        void s21_rotate_right(Node *node) {
            Node *left_son = node->left_;
            if (left_son != nil_) {
                Node *parent = node->parent_;
                left_son->parent_ = parent;
                if (parent != nil_) {
                    if (node == parent->left_) {
                        parent->left_ = left_son;
                    } else {
                        parent->right_ = left_son;
                    }
                } else {
                    before_root_->parent_ = left_son;
                    left_son->parent_ = nil_;
                }
                node->left_ = left_son->right_;
                if (left_son->right_ != nil_) {
                    left_son->right_->parent_ = node;
                }
                left_son->right_ = node;
                node->parent_ = left_son;
            }
        }

    private:
        class Node {
        public:
            bool red_;
            Node *parent_;
            Node *left_;
            Node *right_;
            value_type key_;

        public:
            Node()
                    : red_(false),
                      parent_(nullptr),
                      left_(nullptr),
                      right_(nullptr),
                      key_(value_type{}){};

            explicit Node(Key key)
                    : red_(true),
                      parent_(nullptr),
                      left_(nullptr),
                      right_(nullptr),
                      key_(key){};
        };

        class Iterator {
        public:
            Iterator() = delete;
            explicit Iterator(Node *n, BinaryTree *binaryTree)
                    : current_node_(n), binaryTree_(binaryTree){};

            reference operator*() noexcept { return current_node_->key_; }

            iterator &operator++() noexcept {
                current_node_ = binaryTree_->s21_node_next(current_node_);
                return *this;
            }

            Node *get_node() { return current_node_; }

            iterator operator++(int) noexcept {
                iterator current = iterator(current_node_, binaryTree_);
                ++(*this);
                return current;
            }

            iterator &operator--() noexcept {
                current_node_ = binaryTree_->s21_node_prev(current_node_);
                return *this;
            }

            iterator operator--(int) noexcept {
                iterator current = iterator(current_node_, binaryTree_);
                --(*this);
                return current;
            }

            bool operator==(const iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator!=(const iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }

        private:
            Node *current_node_;
            BinaryTree *binaryTree_;
        };

        class ConstIterator {
        public:
            ConstIterator() = delete;

            ConstIterator(const Node *n, const BinaryTree<value_type, Compare> *binaryTree)
                    : current_node_(n), binaryTree_(binaryTree){};

            reference operator*() const noexcept {
                Node *temp = const_cast<Node *>(current_node_);
                return temp->key_;
            }

            const_iterator &operator++() noexcept {
                current_node_ = binaryTree_->s21_node_next(current_node_);
                return *this;
            }

            const Node *get_node() const noexcept { return current_node_; }

            const_iterator operator++(int) noexcept {
                const_iterator current = const_iterator(current_node_, binaryTree_);
                ++(*this);
                return current;
            }

            const_iterator &operator--() noexcept {
                current_node_ = binaryTree_->s21_node_prev(current_node_);
                return *this;
            }

            const_iterator operator--(int) noexcept {
                const_iterator current = const_iterator(current_node_, binaryTree_);
                --(*this);
                return current;
            }

            bool operator==(const const_iterator &other) const noexcept {
                return current_node_ == other.current_node_;
            }

            bool operator!=(const const_iterator &other) const noexcept {
                return current_node_ != other.current_node_;
            }

        private:
            const Node *current_node_;
            const BinaryTree<value_type, Compare> *binaryTree_;
        };

    private:
        Node *before_root_;
        Node *nil_;
        size_type size_{};
        Compare compare_;
    };

}  //  namespace s21

#endif  // SRC_21_BINARY_TREE_TREE_H
