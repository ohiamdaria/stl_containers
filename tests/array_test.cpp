#include "../array.h"

#include <array>
#include <iostream>
#include "gtest/gtest.h"

template <class T, int N = 0>
using array = s21::array<T, N>;

template <class T, int N>
using original_array = std::array<T, N>;

using std::cout;
using std::endl;
using std::pair;

class ArrayTest : public ::testing::Test {};

TEST(ArrayTest, InitializerListConstructor) {
    array<int, 10> K;
    array<int, 10> A({1, 2, 3, 4, 5});
    original_array<int, 10> B({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(A[i], B[i]);
    }
    const array<int, 10> AA({1, 2, 3, 4, 5});
    const original_array<int, 10> BB({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(AA[i], BB[i]);
    }
}

TEST(ArrayTest, CopyConstructor) {
    array<int, 10> A({1, 2, 3, 4, 5});
    const array<int, 10> B(A);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(A[i], B[i]);
    }
}

TEST(ArrayTest, MoveConstructor) {
    array<int, 10> A({1, 2, 3, 4, 5});
    const array<int, 10> B(std::move(A));
    auto j = B.begin();
    for (int i = 1; i <= 5; i++) {
        EXPECT_EQ(i, *j);
        j++;
    }
}
TEST(ArrayTest, CopyAssignment) {
    array<int, 10> A({1, 2, 3, 4, 5});
    array<int, 10> B = A;
    auto j = B.begin();
    for (int i = 1; i <= 5; i++) {
        EXPECT_EQ(i, *j);
        j++;
    }
}
TEST(S21ArrayTest, MoveAssignment) {
    array<int, 10> A({1, 2, 3, 4, 5});
    array<int, 10> B = std::move(A);
    auto j = B.begin();
    for (int i = 1; i <= 5; i++) {
        EXPECT_EQ(i, *j);
        j++;
    }
}

TEST(ArrayTest, SquareBrackets) {
    array<int, 1000> A({1, 2, 3, 4, 5});
    original_array<int, 1000> B({1, 2, 3, 4, 5});
    for (int i = 0; i < 1000; i++) {
        A[i] = i + 2;
        B[i] = i + 2;
        EXPECT_EQ(A[i], B[i]);
    }
    const array<int, 10> AA({1, 2, 3, 4, 5});
    const original_array<int, 10> BB({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(A[i], B[i]);
    }
}

TEST(ArrayTest, FrontBack) {
    array<int, 5> A({1, 2, 3, 4, 5});
    const array<int, 5> B({1, 2, 3, 4, 5});
    EXPECT_EQ(A.front(), 1);
    EXPECT_EQ(B.front(), 1);
    EXPECT_EQ(A.back(), 5);
    EXPECT_EQ(B.back(), 5);
}

TEST(ArrayTest, At) {
    array<int, 1000> A;
    original_array<int, 1000> B;
    for (int i = 0; i < 1000; i++) {
        A.at(i) = i + 2;
        B.at(i) = i + 2;
        EXPECT_EQ(A.at(i), B.at(i));
    }
    const array<int, 5> AA({1, 2, 3, 4, 5});
    const original_array<int, 5> BB({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(AA.at(i), BB.at(i));
    }
}
TEST(ArrayTest, Data) {
    array<int, 1000> A;
    original_array<int, 1000> B;
    for (int i = 0; i < 1000; i++) {
        A.at(i) = i;
        B.at(i) = i;
        EXPECT_EQ(A.data()[i], B.data()[i]);
    }
    const array<int, 5> AA({1, 2, 3, 4, 5});
    const original_array<int, 5> BB({1, 2, 3, 4, 5});
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(AA.data()[i], BB.data()[i]);
    }
}

TEST(ArrayTest, Iterators) {
    array<int, 1000> A;
    original_array<int, 1000> B;
    for (int i = 0; i < 1000; i++) {
        A.at(i) = i;
        B.at(i) = i;
    }
    auto j = B.begin();
    for (auto i : A) {
        EXPECT_EQ(i, *j);
        j++;
    }
    j = B.end();
    auto i = A.end();
    EXPECT_EQ(*(--i), *(--j));
    const array<int, 5> AA({1, 2, 3, 4, 5});
    const original_array<int, 5> BB({1, 2, 3, 4, 5});
    auto ii = AA.begin();
    auto jj = BB.begin();
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(*ii, *jj);
        ii++;
        jj++;
    }
}

TEST(ArrayTest, Empty) {
    array<int, 10> A;
    EXPECT_EQ(A.empty(), false);
}

TEST(ArrayTest, Size) {
    const array<int, 10> A({1, 2, 3});
    const original_array<int, 10> B({1, 2, 3});
    EXPECT_EQ(B.max_size(), A.max_size());
    EXPECT_EQ(B.size(), 10);
    EXPECT_EQ(A.size(), B.size());
}

TEST(ArrayTest, Swap) {
    array<int, 5> A({1, 4, 5, 6, 7});
    array<int, 5> B({10, 14, 15, 16, 17});
    A.swap(B);
    EXPECT_EQ(A[1], 14);
    EXPECT_EQ(B[1], 4);
}

TEST(ArrayTest, Swap2) {
    array<int, 3> A;
    array<int, 3> B;
    array<int> a = {1, 2, 3, 4, 5};
    array<int> b = {11, 12, 13, 14, 15};
    A[0] = a[0];
    A[1] = a[1];
    A[2] = a[2];
    B[0] = b[0];
    B[1] = b[1];
    B[2] = b[2];
    A.swap(B);
    EXPECT_EQ(*A.begin(), 11);
    EXPECT_EQ(*(1 + A.begin()), 12);
}

TEST(ArrayTest, Fill) {
    array<int, 3> a = {1456, 265, 9873};
    array<int, 2> A;
    A.fill(a[0]);
    array<int, 2> B;
    B.fill(a[0]);
    EXPECT_EQ(*A.begin(), *B.begin());
    *(A.begin()) = 100;
    EXPECT_NE(*A.begin(), *B.begin());

    EXPECT_EQ(*(A.begin() + 1), *(B.begin() + 1));
    *(A.begin() + 1) = 100;
    EXPECT_NE(*(A.begin() + 1), *(B.begin() + 1));
}
