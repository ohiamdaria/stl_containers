#include <cstddef>
#include <iostream>
#include <utility>

namespace s21 {
template <class T>
    struct StackNode {
        StackNode<T>* next_;
        StackNode<T>* prev_;
        T data_;
        StackNode() : next_(nullptr), prev_(nullptr), T(0) {}
        StackNode(T i, StackNode<T>* p, StackNode<T>* n) : next_(n), prev_(p), data_(i) {}
    };
template <class T>
    class stack {
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;
        using node_type = StackNode<T>;

    private:
        node_type* front_;
        node_type* back_;
        size_type size_;

 public:
  // CONSTRUCTORS
  stack() : front_(nullptr), back_(nullptr), size_(0) {}

  stack(std::initializer_list<value_type> const& items)
      : front_(nullptr), back_(nullptr), size_(0) {
    for (auto i : items) {
      this->push(i);
    }
  }

  stack(const stack& other) : front_(nullptr), back_(nullptr), size_(0) {
      node_type* n = other.front_;
    while (n != nullptr) {
      this->push(n->data_);
      n = n->next_;
    }
  }

  stack(stack&& other) noexcept : front_(other.front_), back_(other.back_), size_(other.size_) {
      other.front_ = other.back_ = nullptr;
      other.size_ = 0;
  }

  ~stack() {
    while (front_ != nullptr) {
      this->pop();
    }
  }

  stack& operator=(stack&& other) noexcept {
    if (front_ != nullptr) {
      this->~stack();
    }
    front_ = other.front_;
    back_ = other.back_;
    size_ = other.size_;
      other.front_ = other.back_ = nullptr;
      other.size_ = 0;
    return *this;
  }
  stack& operator=(const stack& other) {
    if (this->front_ == other.front_) return *this;
    if (front_ != nullptr) {
      this->~stack();
    }
      node_type* n = other.front_;
    while (n != nullptr) {
      this->push(n->data_);
      n = n->next_;
    }
    return *this;
  }

  // ELEMENT ACCESS
  const_reference top() const { return back_->data_; }

  // CAPACITY
  [[nodiscard]] bool empty() const {
    if (size_ == 0) {
      return true;
    }
    return false;
  }
  [[nodiscard]] size_type size() const { return size_; }

  // ELEMENT ACCESS
  void push(const_reference value) {
    size_++;
      node_type* n = new node_type(value, back_, nullptr);
    if (back_ != nullptr) {
      back_->next_ = n;
    } else {
      front_ = n;
    }
    back_ = n;
  }
  void pop() {
    if (front_ != nullptr) {
      size_--;
        node_type* tmp = back_;
      back_ = back_->prev_;
      delete tmp;
      if (back_ == nullptr) {
        front_ = nullptr;
      }
    }
  }
  void swap(stack& other) {
    stack tmp = other;
    other = *this;
    *this = tmp;
  }

  template <class... Args>
  void emplace_front(Args&&... args) {
    value_type val(args...);
    this->push(val);
  }
};

}  // namespace s21
