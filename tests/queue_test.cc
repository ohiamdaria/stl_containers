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
    queue<char> C {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'};
    og_queue<char> C_OG ({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});

    queue<char> B;
    std::queue<char> B_OG;
    for (int i = 48; i < 100; i++) {
        B.push(char(i));
        B_OG.push(char(i));
    }

    for (int i = 48; i < 100; i++) {
        EXPECT_EQ(B.front(), B_OG.front());
        B.pop();
        B_OG.pop();
    }

    for (int i = 0; i < 9; i++) {
        EXPECT_EQ(C.front(), C_OG.front());
        C.pop();
        C_OG.pop();
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

TEST(QueueTest, CapacityTest) {
    queue<double> A;
    og_queue<double> B;
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
    for (int i = 0; i < 666; i++) {
        A.push(i * 0.12345);
        B.push(i * 0.12345);
    }
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
    for (int i = 0; i < 66; i++) {
        A.pop();
        B.pop();
    }

    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
}

TEST(QueueTest, Swap) {
    queue<double> A;
    queue<double> B;
    og_queue<double> AA;
    og_queue<double> BB;
    for (int i = 0; i < 666; i++) {
        A.push(i * 0.23456 + i);
        B.push(i * 0.98764 + i);

        AA.push(i * 0.23456 + i);
        BB.push(i * 0.98764 + i);
    }

    A.swap(B);
    AA.swap(BB);
    EXPECT_EQ(A.size(), AA.size());
    EXPECT_EQ(A.size(), 666);
    while (!A.empty()) {
        EXPECT_EQ(A.back(), AA.back());
        A.pop();
        AA.pop();
    }
    EXPECT_EQ(A.size(), 0);
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
    while (!A.empty())
        A.pop();
    EXPECT_EQ(A.size(), 0);
}

