#include "../stack.h"

#include "gtest/gtest.h"
#include "stack"

template <class T>
using stack = s21::stack<T>;

template <class T>
using og_stack = std::stack<T>;

using std::pair;

class StackTest : public ::testing::Test {};

TEST(StackTest, DefaultConstructor) {
    stack<int> A;
    const stack<int> AA;
}

TEST(StackTest, Constructors) {
    stack<double> A;
    og_stack<double> B;
    for (double i = 0; i < 100; i++) {
        A.push(i * 0.2345);
        B.push(i * 0.2345);
    }
    stack<double> A_copy(A);
    stack<double> A_move(std::move(A));
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A_copy.top(), A_move.top());
        A_copy.pop();
        A_move.pop();
    }
}

TEST(StackTest, InitializerConstructor) {
    stack<char> A({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
    og_stack<char> B({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
    while (B.size() != 0) {
        EXPECT_EQ(A.top(), B.top());
        A.pop();
        B.pop();
    }
}

TEST(StackTest, AssignmentOperators) {
    stack<char> A({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
    stack<char> AA({0, 0, 0});
    AA = A;
    og_stack<char> B({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'k'});
    og_stack<char> BB({0, 0, 0});
    BB = B;
    while (BB.size() != 0) {
        EXPECT_EQ(AA.top(), BB.top());
        AA.pop();
        BB.pop();
    }
}

TEST(StackTest, PushAndPop) {
    stack<double> A;
    og_stack<double> B;
    for (int i = 0; i < 100; i++) {
        A.push(8 * i + 3.0);
        B.push(8 * i + 3.0);
    }
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(A.top(), B.top());
        A.pop();
        B.pop();
    }
}
TEST(StackTest, PushPop2) {
    stack<char> A;
    og_stack<char> B;
    for (int i = 0; i < 25; i++) {
        A.push(char(i));
        B.push(char(i));
    }
    for (int i = 0; i < 25; i++) {
        EXPECT_EQ(A.top(), B.top());
        A.pop();
        B.pop();
    }
}

TEST(StackTest, CapacityTest) {
    stack<int> A;
    og_stack<int> B;
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
    A.push(1);
    A.push(1);
    A.push(1);
    B.push(1);
    B.push(1);
    B.push(1);
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
    A.pop();
    B.pop();
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.empty(), B.empty());
}

TEST(StackTest, Swap) {
    stack<int> A({1, 2, 3});
    stack<int> B({4, 5, 6, 7});
    A.swap(B);
    EXPECT_EQ(A.top(), 7);
    EXPECT_EQ(B.top(), 3);
}

TEST(StackTest, Emplace) {
    stack<int> A({1, 2, 3});
    A.emplace_front(4);
    A.emplace_front(5);
    A.emplace_front(6);

    og_stack<int> B({1, 2, 3});
    B.push(4);
    B.push(5);
    B.push(6);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(A.top(), B.top());
        A.pop();
        B.pop();
    }
}

TEST(StackTest, Other) {
    stack<int> A;
    og_stack<int> A_OG;
    for (int i = 0; i < 100; i++) {
        A.emplace_front(i);
        A_OG.emplace(i);
    }

    EXPECT_EQ(A.size(), A_OG.size());
    EXPECT_EQ(A.size(), 100);
    while (A.size() != 0) {
        A.pop();
    }
    EXPECT_EQ(A.size(), 0);
}