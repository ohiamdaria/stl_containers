#include "../queue.h"

#include "gtest/gtest.h"
#include "queue"

template <class T>
using queue = s21::queue<T>;

template <class T>
using og_queue = std::queue<T>;

using std::pair;

class QueueTest : public ::testing::Test {};

TEST(QueueTest, DefaultConstructor) {
    queue<char> A;
    const queue<char> AC;
    queue<char> B {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'};
    std::deque<char> B_OG {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'};

    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(B.front(), B_OG.front());
        B.pop();
        B_OG.pop_front();
    }
}

TEST(QueueTest, Constructors) {
      queue<double> A;
      og_queue<double> B;
      for (int i = 0; i < 100; i++) {
          A.push(8 * i + 3.0);
          B.push(8 * i + 3.0);
      }

      queue<double> A_copy(A);
      queue<double> A_move(std::move(A));
      for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A_copy.front(), A_move.front());
        A_copy.pop();
        A_move.pop();
      }
}

TEST(QueueTest, Constructors2) {
    queue<char> A;
    og_queue<char> B;
    for (int i = 0; i < 100; i++) {
        A.push(i);
        B.push(i);
    }

    queue<char> A_copy(A);
    queue<char> A_move(std::move(A));
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A_copy.front(), A_move.front());
        A_copy.pop();
        A_move.pop();
    }
}

TEST(QueueTest, PushAndPop) {
      queue<char> A;
      og_queue<char> B;
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

TEST(QueueTest, Emplace) {
      queue<char> A;
      og_queue<char> B;
      for (int i = 0; i < 666; i++) {
        A.emplace_back(i);
        B.emplace(i);
      }
      for (int i = 0; i < 666; i++) {
        EXPECT_EQ(A.front(), B.front());
        EXPECT_EQ(A.back(), B.back());
        A.pop();
        B.pop();
      }
}

TEST(QueueTest, Other) {
    queue<double> A;
    og_queue<double> A_OG;
    for (int i = 0; i < 666; i++) {
        A.emplace_back(i * 0.23456 + i);
        A_OG.emplace(i * 0.23456 + i);
    }

    EXPECT_EQ(A.size(), A_OG.size());
    EXPECT_EQ(A.size(), 666);
    while (A.size() != 0) {
        A.pop();
    }
    EXPECT_EQ(A.size(), 0);
}

