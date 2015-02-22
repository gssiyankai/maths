#include <gtest/gtest.h>
#include "utils.hpp"

using namespace std;

TEST(UtilsTest, Combination2)
{
    const vector<int>& v = { 1, 2, 3 };
    const vector< pair<int,int> >& r = Utils::combination2(v);
    ASSERT_EQ(3, r.size());
    ASSERT_EQ(make_pair(1,2), r[0]);
    ASSERT_EQ(make_pair(1,3), r[1]);
    ASSERT_EQ(make_pair(2,3), r[2]);
}
