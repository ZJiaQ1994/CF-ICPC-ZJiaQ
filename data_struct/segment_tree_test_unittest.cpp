#include "segment_tree.h"

struct SegValue
{
    SegValue(int s)
    {
        sum = s;
    }
    SegValue()
    {
        sum = 0;
    }
    SegValue operator+(const SegValue &segValue)const
    {
        SegValue ret;
        ret.sum = segValue.sum + sum;
        return ret;
    }
    SegValue operator*(const int &len)const
    {
        SegValue ret;
        ret.sum = sum * len;
        return ret;
    }
    int sum;
};

int Case1()
{
    data_struct::SegmentTree<SegValue> tree;
    int l, r;
    l = 1;
    r = 11;
    std::vector<SegValue> initArray(r - l, 1);
    tree.Build(l, r, initArray);
    std::cout << " sum of range(1, 11): " << tree.Query(1, 11).sum << std::endl;
    tree.Update(1, 11, SegValue(1));
    std::cout << " sum of range(1, 11): " << tree.Query(1, 11).sum << std::endl;
    tree.Update(1, 6, SegValue(1));
    std::cout << " sum of range(1, 11): " << tree.Query(1, 11).sum << std::endl;
    std::cout << " sum of range(6, 11): " << tree.Query(6, 11).sum << std::endl;
    std::cout << " sum of range(5, 6): " << tree.Query(5, 6).sum << std::endl;
    std::cout << " sum of range(5, 7): " << tree.Query(5, 7).sum << std::endl;
}

int main()
{
    Case1();
}

