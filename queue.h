#include <cstddef>
#include <iostream>
#include <utility>

namespace s21 {
    template <class T>
    struct QueueNode {
      QueueNode<T>* next_;
      QueueNode<T>* prev_;
      T data_;
      QueueNode() : next_(nullptr), prev_(nullptr), data_(0) {}
      QueueNode(T i, QueueNode<T>* p, QueueNode<T>* n) : next_(n), prev_(p), data_(i) {}
    };
    template <class T>
    class queue {
      using value_type = T;
      using reference = T&;
      using const_reference = const T&;
      using size_type = size_t;
      using node_type = QueueNode<T>;

     private:
        node_type* front_;
        node_type* back_;
        size_type size_;

     public:

      queue() : front_(nullptr), back_(nullptr), size_(0) {}

      queue(std::initializer_list<value_type> const& items)
          : front_(nullptr), back_(nullptr), size_(0) {
            for (auto item : items) {
              this->push(item);
            }
      }
      queue(const queue& other) : front_(nullptr), back_(nullptr), size_(0) {
        node_type* node = other.front_;
        while (node != nullptr) {
            this->push(node->data_);
            node = node->next_;
        }
      }

      queue(queue&& other) noexcept {
          front_ = other.front_;
          back_ = other.back_;
          size_ = other.size_;
          other.front_ = other.back_ = nullptr;
          other.size_ = 0;
      }

      ~queue() {
        while (front_ != nullptr) {
          this->pop();
        }
      }
      queue& operator=(queue&& other) noexcept {
        if (front_ != nullptr) {
          while (front_ != nullptr) {
            this->pop();
          }
        }
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;
          other.front_ = other.back_ = nullptr;
          other.size_ = 0;
        return *this;
      }
      queue& operator=(const queue& other) {
        if (this == other) return *this;
        if (front_ != nullptr) {
            while (front_ != nullptr) {
                this->pop();
            }
        }
        front_ = back_ = nullptr;
        node_type* node = other.front_;
        while (node != nullptr) {
            this->push(node->data_);
            node = node->next_;
        }
        return *this;
      }

      const_reference front() { return front_->data_; }
      const_reference back() { return back_->data_; }

      [[nodiscard]] bool empty() const { return size_ == 0; }
      [[nodiscard]] size_type size() const { return size_; }

      void push(const_reference value) {
            size_++;
            node_type* node = new node_type(value, back_, nullptr);
            if (back_ != nullptr) {
                back_->next_ = node;
            } else {
                front_ = node;
            }
            back_ = node;
        }

        void pop() {
            if (front_ != nullptr) {
                size_--;
                node_type* tmp = front_;
                front_ = front_->next_;
                delete tmp;
                if (front_ == nullptr) {
                    back_ = nullptr;
                }
            }
        }

      void swap(queue& other) {
            queue tmp = other;
            other = *this;
            *this = tmp;
      }

      template <class... Args>
      void emplace_back(Args&&... args) {
        value_type val(args...);
        this->push(val);
      }
    };

}  // namespace s21