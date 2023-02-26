#include "../map.h"

#include <string>
#include "gtest/gtest.h"

template <class T, class K>
using map = s21::map<T, K>;

template <class T, class K>
using og_map = std::map<T, K>;

using std::pair;

class MapTest : public ::testing::Test {};

TEST(MapTest, DefaultConstructor) {
  map<int, char> A;
  map<char, char> B;
  const map<double, char> C;
  const map<char, int> D;
  EXPECT_EQ(A.size(), 0);
  EXPECT_EQ(B.size(), 0);
  EXPECT_EQ(C.size(), 0);
  EXPECT_EQ(D.size(), 0);
}
TEST(MapTest, InitConstructor) {

  map<int, int> A ({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
  og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});

  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ(i.second, (*j).second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, At) {
    map<int, int> A ({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
    og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});


  EXPECT_EQ(A.at(1), B.at(1));
  EXPECT_EQ(A.at(2), B.at(2));
  EXPECT_EQ(A.at(3), B.at(3));
  A.at(3) = 200;
  B.at(3) = 200;
  EXPECT_EQ(A.at(3), B.at(3));

    map<double, char> AA ({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});
    og_map<double, char> BB({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});

  EXPECT_EQ(AA.at(0.234567), BB.at(0.234567));
  EXPECT_EQ(AA.at(9.5678), BB.at(9.5678));
  EXPECT_EQ(AA.at(3.45678), BB.at(3.45678));
}

//TEST(S21MapTest, Brackets) {
//  map<int, int> A({pair(1, 10)});
//  og_map<int, int> B({pair(1, 10)});
//  EXPECT_EQ(A[1], B[1]);
//  A[2] = 20;
//  B[2] = 20;
//  B[4] = 999;
//  A[4] = 999;
//  EXPECT_EQ(A[4], B[4]);
//  EXPECT_EQ(A[2], B[2]);
//}

TEST(MapTest, Insert) {
    map<int, int> A({pair(1, 10), pair(2, 20), pair(3, 30)});
    og_map<int, int> B(
            {pair(1, 10), pair(2, 20), pair(3, 30)});
    auto j = B.begin();
  auto insert_pair = A.insert(std::pair(4, 40));
  auto og_insert_pair = B.insert(std::pair(4, 40));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);
    insert_pair = A.insert(std::pair(4, 40));
  og_insert_pair = B.insert(std::pair(4, 40));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);
  insert_pair = A.insert(std::pair(5, 50));
    og_insert_pair = B.insert(std::pair(5, 50));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);
  insert_pair = A.insert(std::pair(5, 50));
    og_insert_pair = B.insert(std::pair(5, 50));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);
  insert_pair = A.insert(std::pair(6, 60));
    og_insert_pair = B.insert(std::pair(6, 60));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);
  insert_pair = A.insert(std::pair(6, 60));
    og_insert_pair = B.insert(std::pair(6, 60));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);
   j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, InsertSecond) {
    map<int, int> A({pair(1, 10), pair(2, 20), pair(3, 30)});
    og_map<int, int> B(
            {pair(1, 10), pair(2, 20), pair(3, 30)});
    auto j = B.begin();
  A.insert(4, 40);
  B.insert(std::pair(4, 40));
  A.insert(4, 40);
  B.insert(std::pair(4, 40));
  A.insert(5, 50);
  B.insert(std::pair(5, 50));
  A.insert(5, 50);
  B.insert(std::pair(5, 50));

  A.insert(6, 60);
  B.insert(std::pair(6, 60));
  A.insert(6, 60);
  B.insert(std::pair(6, 60));
   j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, InsertOrAssign) {
  map<int, int> A({pair(1, 10), pair(2, 20), pair(2, 20), pair(3, 30)});
  og_map<int, int> B(
      {pair(1, 10), pair(2, 20), pair(2, 20), pair(3, 30)});
  A.insert_or_assign(3, 60);
  B.insert_or_assign(3, 60);
  A.insert_or_assign(4, 60);
  B.insert_or_assign(4, 60);
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}
TEST(MapTest, Emplace) {
  map<int, int> A({pair(1, 10), pair(2, 20), pair(2, 20), pair(3, 30)});
  og_map<int, int> B(
      {pair(1, 10), pair(2, 20), pair(2, 20), pair(3, 30)});
  A.emplace(pair(4, 60));
  B.emplace(4, 60);
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

 int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
 }
