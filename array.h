#ifndef SRC_ARRAY
#define SRC_ARRAY

#include <cstddef>
#include <cstring>
#include <iostream>
#include <utility>

namespace s21 {

    template <class T, std::size_t N = 0>
    class array {
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = value_type*;
        using const_iterator = const value_type*;

    private:
        value_type array_[N] = {};

    public:
        array() = default;
        array(std::initializer_list<value_type> const& items) {
            pointer ptr = array_;
            for (auto item : items)
                *(ptr++) = item;
        }
        array(const array& other) {
            for (size_type i = 0; i < other.size(); ++i)
                array_[i] = other.array_[i];
        }
        array(array&& other) noexcept {
            for (size_type i = 0; i < N; ++i)
                this->array_[i] = other.array_[i];
        }

        ~array() = default;

        array& operator=(const array& other) {
            for (size_type i = 0; i < other.size(); ++i)
                array_[i] = other.array_[i];
            return *this;
        }

        array& operator=(array&& other) {
            for (size_type i = 0; i < other.size(); ++i)
                array_[i] = std::move(other.array_[i]);
            return *this;
        }


        constexpr reference operator[]( size_type pos ) { return array_[pos]; }
        constexpr const_reference operator[](size_type pos) const { return *(array_ + pos); }

        constexpr reference front() { return *array_; }
        constexpr const_reference front() const { return *array_; }

        constexpr reference back() { return *(array_ + N - 1); }
        constexpr const_reference back() const { return *(array_ + N - 1); }

        constexpr T* data() noexcept { return array_; }
        constexpr const T* data() const noexcept { return array_; }


        reference at(size_type pos) {
            if (pos >= N)
                throw std::out_of_range("Index of the element out of range");
            return array_[pos];
        }

        const_reference at(size_type pos) const {
            if (pos >= N)
                throw std::out_of_range("Index of the element out of range");
            return array_[pos];
        }

        constexpr iterator begin() noexcept { return array_; }
        constexpr iterator end() noexcept { return array_ + N; }
        constexpr const_iterator begin() const noexcept { return array_; }
        constexpr const_iterator end() const noexcept { return array_ + N; }

        [[nodiscard]] constexpr bool empty() const noexcept {
            if (N == 0) {
                return true;
            }
            return false;
        }
        [[nodiscard]] constexpr size_type size() const noexcept { return N; }
        [[nodiscard]] constexpr size_type max_size() const noexcept { return N; }

        constexpr void swap( array& other ) noexcept {
            for (auto first1 = begin(), last1 = end(), first2 = other.begin();
                 first1 != last1; ++first1, ++first2) {
                T tmp = std::move(*first1);
                *first1 = std::move(*first2);
                *first2 = std::move(tmp);
            }
        }

        constexpr void fill( const T& value ) {
            for ([[maybe_unused]] auto i : *this) {
                i = value;
            }
        }
    };

}  // namespace s21

#endif  // SRC_ARRAY