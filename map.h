#ifndef SRC_S21_CONTAINERS_S21_SET_H
#define SRC_S21_CONTAINERS_S21_SET_H

#include <iostream>

#include "s21_tree.h"

namespace s21 {
    template<class Key, class T>
    class map {
    public:

        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type &;

        struct Compare
        {
            bool operator()(const_reference __x, const_reference __y) const
            { return  __x.first < __y.first; }
        };

        using iterator = typename BinaryTree<value_type, Compare>::iterator;
        using const_iterator = typename BinaryTree<value_type, Compare>::const_iterator;
        using size_type = std::size_t;
        using rb_tree = BinaryTree<value_type, Compare>;

        map() : rbTree_(new rb_tree{}) {}

        map(std::initializer_list<value_type> const &items) : map() {
            for (auto item: items)
                rbTree_->insert_unique(item);
        }

        map(const map &s) : rbTree_(new rb_tree(*s.rbTree_)) {}

        map(map &&s) noexcept: rbTree_(new rb_tree(std::move(*s.rbTree_))) {}

        ~map() {
            delete rbTree_;
            rbTree_ = nullptr;
        }

        map &operator=(const map &s) {
            *rbTree_ = *s.rbTree_;
            return *this;
        }

        map &operator=(map &&s) noexcept {
            *rbTree_ = std::move(*s.rbTree_);
            return *this;
        }

        iterator begin() noexcept { return rbTree_->begin(); }

        iterator end() noexcept { return rbTree_->end(); }

        const_iterator begin() const noexcept { return rbTree_->cbegin(); }

        const_iterator end() const noexcept { return rbTree_->cend(); }

        mapped_type &at(const key_type &key) {
            value_type search_pair(key, mapped_type{});
            iterator it_search = rbTree_->find(search_pair);

            if (it_search == end()) {
                throw std::out_of_range("s21::map::at: No element exists with key");
            } else {
                return (*it_search).second;
            }
        }

//        const mapped_type &at(const key_type &key) const {
//            return const_cast<map<Key, T> *>(this)->at(key);
//        }

        bool empty() const noexcept { return rbTree_->empty(); }

        size_type size() const noexcept { return rbTree_->size(); }

        size_type max_size() const noexcept { return rbTree_->max_size(); }

        void clear() noexcept { return rbTree_->clear(); }

        std::pair<iterator, bool> insert(const value_type &value) noexcept {
            return rbTree_->insert_unique(value);
        }

        std::pair<iterator, bool> insert(const key_type& k, mapped_type&& obj) {
            return rbTree_->insert_unique(value_type{k, obj});
        }

         std::pair<iterator, bool> insert_or_assign( key_type &&k, mapped_type&& obj ) {
             iterator result = rbTree_->find(value_type{k, obj});
             if (result == end())
                 return rbTree_->insert_unique(value_type{k, obj});
             (*result).second = obj;

             return {result, false};

        }

        void erase(iterator pos) noexcept { rbTree_->erase(pos); }

        void swap(map &other) noexcept { rbTree_->s21_swap(*other.rbTree_); }

        void merge(map &other) noexcept { rbTree_->unique_merge(*other.rbTree_); }

        iterator find(const Key &key) noexcept {
            value_type search_pair(key, mapped_type{});
            if (rbTree_->contains(search_pair)) {
                auto result = rbTree_->find(search_pair);
                return result == end() ? end() : result;
            } else return end();
        }

        // need noexcept?
        template<class... Args>
        std::vector<std::pair<iterator, bool>> emplace(Args &&...args) noexcept {
            return rbTree_->emplace_uniq(args...);
        }

    private:
        rb_tree *rbTree_;

    };  // namespace s21
}
#endif  //  SRC_S21_CONTAINERS_S21_SET_H