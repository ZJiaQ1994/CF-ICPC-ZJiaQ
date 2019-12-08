#include <vector>
#include <list>
#include <iterator>
#include <iostream>

namespace data_struct
{

template <typename Value>
struct SegmentTreeNode
{
    Value value;
    Value lazyValue;
    bool lazyTag;
    int l;
    int r;
    int Len()
    {
        return r - l;
    }
    void Update(const Value &addValue)
    {
        value = value + addValue * Len();
        if (lazyTag)
        {
            lazyValue = lazyValue + addValue;
        }
        else
        {
            lazyValue = addValue;
            lazyTag = true;
        }

        return ;
    }

    bool InRange(int lBound, int rBound)
    {
        if (lBound <= l && rBound >= r)
        {
            return true;
        }
        return false;
    }

    bool HasRange(int lBound, int rBound)
    {
        if (lBound >= l && rBound <= r && rBound > lBound)
            return true;
        return false;
    }

    bool HasInsection(int lBound, int rBound)
    {
        if (lBound < r && rBound > l)
        {
            return true;
        }
        return false;
    }

    bool IsLeaf()
    {
        return l + 1 == r;
    }
    SegmentTreeNode<Value>* pLSon;
    SegmentTreeNode<Value>* pRSon;
};

template <typename Value>
class SegmentTree
{
    // typedef std::const_iterator<std::input_iterator_tag, Value, Value, Value*, Value> iterator;
    typedef typename std::vector<Value>::const_iterator iterator;
public:
    void Build(int l, int r, const std::vector<Value> &initArray)
    {
        SegmentTreeNode<Value> *pNode = nodeRoot = GetNewNode(l, r);
        if (r - l != initArray.size())
        {
            std::cout << "##SB, build out of range le" << std::endl;
            ::abort();
        }
        Build(pNode, initArray.begin(), initArray.end());
    }

    Value Query(int l, int r)
    {
        SegmentTreeNode<Value> *pNode = GetRoot();
        if (!pNode->HasRange(l, r))
        {
            std::cout << "##SB, query out of range le. query range: (" << l << ", " << r<< "). tree range: (" 
                << pNode->l << ", " << pNode->r << ")" << std::endl;
            ::abort();
        }
        return Query(pNode, l, r);
    }
    void Update(int l, int r, const Value &value)
    {
        SegmentTreeNode<Value> *pNode = GetRoot();
        if (!pNode->HasRange(l, r))
        {
            std::cout << "##SB, update out of range le. query range: (" << l << ", " << r<< "). tree range: (" 
                << pNode->l << ", " << pNode->r << ")" << std::endl;
            ::abort();;
        }
        return Update(pNode, l, r, value);
    }
private:
    void Build(SegmentTreeNode<Value> *pNode, iterator itBegin, iterator itEnd)
    {
        // std::cout << "##DEBUG l: " << pNode->l << ", r: " << pNode->r << ", init dis: " << std::distance(itBegin, itEnd)<< std::endl;

        if (pNode->IsLeaf())
        {
            pNode->value = *itBegin;
            return ;
        }
        int mid = ((pNode->l + pNode->r) >> 1);
        pNode->pLSon = GetNewNode(pNode->l, mid);
        pNode->pRSon = GetNewNode(mid, pNode->r);
        Build(pNode->pLSon, itBegin, itBegin + mid - pNode->l);
        Build(pNode->pRSon, itBegin + mid - pNode->l, itEnd);
        PushUp(pNode);
        return ;
    }
    void PushUp(SegmentTreeNode<Value> *pNode)
    {
        if ((pNode->pLSon != NULL) && (pNode->pRSon != NULL))
        {
            pNode->value = pNode->pLSon->value + pNode->pRSon->value;
        }
        return ;
    }
    void PushDown(SegmentTreeNode<Value> *pNode)
    {
        if (!pNode->lazyTag)
            return;

        auto pLSon = pNode->pLSon;
        if (pLSon != NULL)
        {
            pLSon->Update(pNode->lazyValue);
        }

        auto pRSon = pNode->pRSon;
        if (pRSon != NULL)
        {
            pRSon->Update(pNode->lazyValue);
        }

        pNode->lazyTag = false;
    }
    void Update(SegmentTreeNode<Value>* pNode, int l, int r, const Value &value)
    {

        // std::cout << "update node: (" << pNode->l << ", " << pNode->r << ")" << ", update range: (" << l << ", " << r << ")" << std::endl;
        if (pNode->InRange(l, r))
        {
            pNode->Update(value);
            return ;
        }

        PushDown(pNode);

        if (pNode->pLSon->HasInsection(l, r))
        {
            Update(pNode->pLSon, l, r, value);
        }

        if (pNode->pRSon->HasInsection(l, r))
        {
            Update(pNode->pRSon, l, r, value);
        }

        PushUp(pNode);
        return ;
    }

    Value Query(SegmentTreeNode<Value>* pNode, int l, int r)
    {
        // std::cout << "update node: (" << pNode->l << ", " << pNode->r << ")" << ", update range: (" << l << ", " << r << ")" << std::endl;
        if (pNode->InRange(l, r))
        {
            return pNode->value;
        }

        PushDown(pNode);

        Value value;
        if (pNode->pLSon->HasInsection(l, r))
        {
            value = value + Query(pNode->pLSon, l, r);
        }

        if (pNode->pRSon->HasInsection(l, r))
        {
            value = value + Query(pNode->pRSon, l, r);
        }

        return value;
    }


    SegmentTreeNode<Value>* GetRoot()
    {
        return nodeRoot;
    }

    SegmentTreeNode<Value>* GetNewNode(int l, int r)
    {
        SegmentTreeNode<Value> *pNode;
        pNode = new SegmentTreeNode<Value>();
        pNode->l = l;
        pNode->r = r;
        pNode->lazyTag = false;
        // pNode->value = value;
        pNode->pLSon = NULL;
        pNode->pRSon = NULL;
        nodePool.push_back(pNode);
        return pNode;
    }
    std::vector<SegmentTreeNode<Value>*> nodePool;
    SegmentTreeNode<Value>* nodeRoot;
};



}
