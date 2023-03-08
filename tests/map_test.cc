#include "../map.h"

#include <string>
#include "gtest/gtest.h"
#include <map>

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

    AA.at(3.45678) = 'K';
    BB.at(3.45678) = 'K';
    EXPECT_EQ(AA.at(3.45678), BB.at(3.45678));
}

TEST(MapTest, Insert) {
    map<int, int> A ({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
    og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});

    auto j = B.begin();
  auto insert_pair = A.insert(std::pair(6, 666));
  auto og_insert_pair = B.insert(std::pair(6, 666));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  insert_pair = A.insert(std::pair(666, 6));
  og_insert_pair = B.insert(std::pair(666, 6));
  EXPECT_EQ((*(insert_pair.first)).first, (*(og_insert_pair.first)).first);
  EXPECT_EQ((*(insert_pair.first)).second, (*(og_insert_pair.first)).second);
  EXPECT_EQ(insert_pair.second, og_insert_pair.second);

  insert_pair = A.insert(std::pair(6, 666));
  og_insert_pair = B.insert(std::pair(6, 666));
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

TEST(MapTest, Insert2) {
    map<double, char> A ({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});
    og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});

    auto j = B.begin();
  A.insert(11.23456, 'M');
  B.insert(std::pair(11.23456, 'M'));

  A.insert(-456.45678, '!');
  B.insert(std::pair(-456.45678, '!'));

  A.insert(11.23456, 'M');
  B.insert(std::pair(11.23456, 'M'));

  A.insert(623849, '*');
  B.insert(std::pair(623849, '*'));
   j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, InsertOrAssign) {
  map<double, char> A ({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});
  og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});

  A.insert_or_assign(3.45678, 'e');
  B.insert_or_assign(3.45678, 'e');
  A.insert_or_assign(3.55678, 'e');
  B.insert_or_assign(3.55678, 'e');
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, Swap) {
    map<double, char> A ({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});
    map<double, char> AA;
    og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});
    og_map<double, char> BB;

    AA.swap(A);
    BB.swap(B);
    auto j = BB.begin();
    for (auto i : AA) {
        EXPECT_EQ((*j).first, i.first);
        EXPECT_EQ((*j).second, i.second);
        j++;
    }
    EXPECT_EQ(AA.size(), BB.size());
}

TEST(MapTest, Merge) {
    map<double, char> A ({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});
    map<double, char> AA ({pair(0.5, 'K'), pair(9.111, 'M'), pair(9.09, 'N'), pair(2.45678, 'O')});

    og_map<double, char> B({pair(0.234567, 'a'), pair(9.5678, 'b'), pair(9.5678, 'c'), pair(3.45678, 'd')});
    og_map<double, char> BB ({pair(0.5, 'K'), pair(9.111, 'M'), pair(9.09, 'N'), pair(2.45678, 'O')});

    A.merge(AA);
    B.merge(BB);
    auto j = B.begin();
    for (auto i : A) {
        EXPECT_EQ((*j).first, i.first);
        EXPECT_EQ((*j).second, i.second);
        j++;
    }
    EXPECT_EQ(A.size(), B.size());
}


TEST(MapTest, Merge2) {
    map<int, double> A;
    map<int, double> AA;

    og_map<int, double> B;
    og_map<int, double> BB;

    for (int i = 0; i < 10; i++) {
        A.insert(i, i * 1.0 / 0.12345);
        AA.insert(i * 5, i * 9.87654);
        B.insert(std::pair(i, i * 1.0 / 0.12345));
        BB.insert(std::pair(i * 5, i * 9.87654));
    }

    A.merge(AA);
    B.merge(BB);
    auto j = A.begin();
    for (auto i : B) {
        EXPECT_EQ((*j).first, i.first);
        EXPECT_EQ((*j).second, i.second);
        j++;
    }
    EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, Emplace) {
  map<char, char> A({pair('a', '1'), pair('b', '2'), pair('b', '3'), pair('c', '4'), pair('d', '5')});
  og_map<int, int> B(
          {pair('a', '1'), pair('b', '2'), pair('b', '3'), pair('c', '4'), pair('d', '5')});
  A.emplace(pair('e', '!'));
  B.emplace(pair('e', '!'));
  auto j = B.begin();
  for (auto i : A) {
    EXPECT_EQ((*j).first, i.first);
    EXPECT_EQ((*j).second, i.second);
    j++;
  }
  EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, EraseAndOthers) {
    map<double, char> A;
    og_map<double, char> B;
    for (int i = 0; i < 50; i++) {
        A.insert(i * 0.1234, char(i));
      B.insert(std::pair(i * 0.1234, char(i)));
    }
    EXPECT_EQ(A.at(5.0594), ')');
    EXPECT_EQ(A.at(5.0594), B.at(5.0594));
    EXPECT_EQ(A.at(4.4424), '$');
    EXPECT_EQ(A.at(4.4424), B.at(4.4424));
    EXPECT_EQ(A.at(5.9232), '0');
    EXPECT_EQ(A.at(5.9232), B.at(5.9232));
    EXPECT_EQ(A.size(), 50);
    EXPECT_EQ(A.size(), B.size());

    for (int i = 0; i < 10; i++) {
        A.erase(A.begin());
        B.erase(B.begin());
    }
    EXPECT_EQ(A.size(), 40);
    EXPECT_EQ(A.size(), B.size());

    A.insert(61 * 0.1234, char(61));
    B.insert(std::pair(61 * 0.1234, char(61)));
    A.insert(62 * 0.1234, char(62));
    B.insert(std::pair(62 * 0.1234, char(62)));
    A.insert(63 * 0.1234, char(63));
    B.insert(std::pair(63 * 0.1234, char(63)));
    EXPECT_EQ(A.size(), 43);
    EXPECT_EQ(A.size(), B.size());

    for (int i = 0; i < 40; i++) {
        A.erase(A.begin());
        B.erase(B.begin());
    }
    EXPECT_EQ(A.size(), 3);
    EXPECT_EQ(A.size(), B.size());
    A.clear();
    B.clear();
    EXPECT_EQ(A.size(), 0);
    EXPECT_EQ(A.size(), B.size());
}

TEST(MapTest, SizeAndOthers) {
    map<char, char> A({pair('a', '1'), pair('b', '2'), pair('b', '3'), pair('c', '4'), pair('d', '5'),
                            pair('e', '1'), pair('f', '2'), pair('g', '3'), pair('h', '4'), pair('k', '5'),
                            pair('l', '1'), pair('m', '2'), pair('n', '3'), pair('o', '4'), pair('p', '5')
                       });
    og_map<char, char> B(
            {pair('a', '1'), pair('b', '2'), pair('b', '3'), pair('c', '4'), pair('d', '5'),
                        pair('e', '1'), pair('f', '2'), pair('g', '3'), pair('h', '4'), pair('k', '5'),
                        pair('l', '1'), pair('m', '2'), pair('n', '3'), pair('o', '4'), pair('p', '5')});
    A.emplace(pair('e', '!'));
    B.emplace(pair('e', '!'));
    auto j = B.begin();
    for (auto i : A) {
        EXPECT_EQ((*j).first, i.first);
        EXPECT_EQ((*j).second, i.second);
        j++;
    }
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.size(), 14);
    EXPECT_EQ(B.size(), 14);
    A.erase(A.begin());
    EXPECT_EQ(A.size(), 13);
    EXPECT_EQ(A.max_size(), 230584300921369395);

    A.clear();
    B.clear();
    EXPECT_EQ(A.size(), B.size());
    EXPECT_EQ(A.size(), 0);
    EXPECT_EQ(B.size(), 0);
    EXPECT_TRUE(A.empty());
    EXPECT_TRUE(B.empty());
}

TEST(MapTest, FindTest) {
    map<int, int> A ({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});
    og_map<int, int> B({pair(1, 123), pair(2, 345), pair(2, 456), pair(3, 567)});

    EXPECT_EQ((*A.find(1)).second, 123);
    EXPECT_EQ((*B.find(1)).second, 123);
    EXPECT_EQ((*A.find(1)).second, (*B.find(1)).second);

    EXPECT_EQ((*A.find(2)).second, 345);
    EXPECT_EQ((*B.find(2)).second, 345);
    EXPECT_EQ((*A.find(2)).second, (*B.find(2)).second);

    EXPECT_EQ((*A.find(3)).second, 567);
    EXPECT_EQ((*B.find(3)).second, 567);
    EXPECT_EQ((*A.find(3)).second, (*B.find(3)).second);
}

 int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
 }
