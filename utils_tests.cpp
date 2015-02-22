#include <gtest/gtest.h>
#include "utils.hpp"

using namespace std;

TEST(UtilsTest, Split)
{
    const vector<int> v = { 1, 2, 3 };
    const vector< pair< vector<int>, vector<int> > >& expected = { pair< vector<int>, vector<int> >({1}, {2, 3}),
                                                                   pair< vector<int>, vector<int> >({2}, {1, 3}),
                                                                   pair< vector<int>, vector<int> >({3}, {1, 2}) };
    ASSERT_EQ(expected, Utils::split(v));
}

TEST(UtilsTest, SplitMore)
{
    const vector<int> v = { 1, 2, 3, 4, 5 };
    const vector< pair< vector<int>, vector<int> > >& expected = { pair< vector<int>, vector<int> >({1},    {2, 3, 4, 5}),
                                                                   pair< vector<int>, vector<int> >({2},    {1, 3, 4, 5}),
                                                                   pair< vector<int>, vector<int> >({3},    {1, 2, 4, 5}),
                                                                   pair< vector<int>, vector<int> >({4},    {1, 2, 3, 5}),
                                                                   pair< vector<int>, vector<int> >({5},    {1, 2, 3, 4}),
                                                                   pair< vector<int>, vector<int> >({1, 2}, {3, 4, 5}),
                                                                   pair< vector<int>, vector<int> >({1, 3}, {2, 4, 5}),
                                                                   pair< vector<int>, vector<int> >({1, 4}, {2, 3, 5}),
                                                                   pair< vector<int>, vector<int> >({1, 5}, {2, 3, 4}),
                                                                   pair< vector<int>, vector<int> >({2, 3}, {1, 4, 5}),
                                                                   pair< vector<int>, vector<int> >({2, 4}, {1, 3, 5}),
                                                                   pair< vector<int>, vector<int> >({2, 5}, {1, 3, 4}),
                                                                   pair< vector<int>, vector<int> >({3, 4}, {1, 2, 5}),
                                                                   pair< vector<int>, vector<int> >({3, 5}, {1, 2, 4}),
                                                                   pair< vector<int>, vector<int> >({4, 5}, {1, 2, 3}) };
    ASSERT_EQ(expected, Utils::split(v));
}
