#include "../queue.h"

#include "gtest/gtest.h"
#include "queue"

template <class T>
using queue = s21::queue<T>;

template <class T>
using og_queue = std::queue<T>;

using std::pair;

class S21QueueTest : public ::testing::Test {};

TEST(S21QueueTest, DefaultConstructor) {
    queue<int> A;
    const queue<int> AC;
    queue<int> B{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::deque<int> B_OG {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(B.front(), B_OG.front());
        B.pop();
        B_OG.pop_front();
    }
}

TEST(S21QueueTest, Constructors) {
      queue<int> A;
      og_queue<int> B;
      for (int i = 0; i < 100; i++) {
          A.push(i);
          B.push(i);
      }

      queue<int> A_copy(A);
      queue<int> A_move(std::move(A));
      for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A_copy.front(), A_move.front());
        A_copy.pop();
        A_move.pop();
      }
}

TEST(S21QueueTest, Constructors2) {
    queue<int> A;
    og_queue<int> B;
    for (int i = 0; i < 100; i++) {
        A.push(i);
        B.push(i);
    }

    queue<int> A_copy(A);
    queue<int> A_move(std::move(A));
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A_copy.front(), A_move.front());
        A_copy.pop();
        A_move.pop();
    }
}

TEST(S21QueueTest, PushAndPop) {
      queue<int> A;
      og_queue<int> B;
      for (int i = 0; i < 100; i++) {
        A.push(i);
        B.push(i);
      }
      for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A.front(), B.front());
        EXPECT_EQ(A.back(), B.back());
        A.pop();
        B.pop();
      }
}

TEST(S21QueueTest, Emplace) {
      queue<int> A;
      og_queue<int> B;
      for (int i = 0; i < 100; i++) {
        A.emplace_back(i);
        B.emplace(i);
      }
      for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A.front(), B.front());
        EXPECT_EQ(A.back(), B.back());
        A.pop();
        B.pop();
      }
}

TEST(S21QueueTest, Other) {
    queue<int> A;
    og_queue<int> A_OG;
    for (int i = 0; i < 100; i++) {
        A.emplace_back(i);
        A_OG.emplace(i);
    }

    EXPECT_EQ(A.size(), A_OG.size());
    EXPECT_EQ(A.size(), 100);
    while (A.size() != 0) {
        A.pop();
    }
    EXPECT_EQ(A.size(), 0);
}

