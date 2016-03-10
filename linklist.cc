#include <iostream>
using namespace std;

typedef struct
{
    int cur;
} SElem;

class SLinkList
{
public:
    SLinkList(int nElem=4096);
    ~SLinkList();

    int malloc();
    void free(int nUsed);
private:
    SElem *pData;
};

SLinkList::SLinkList(int nElem)
{
    if (nElem <= 0)
        nElem = 4096;

    pData = new SElem[nElem];

    for (int i = 0; i != nElem - 1; ++i)
    {
        pData[i].cur = i + 1;
    }

    pData[nElem - 1].cur = 0; // 最后一个元素指示空间已满
}

SLinkList::~SLinkList()
{
    if (pData != NULL)
    {
        delete [] pData;
    }
}

//---------------------------------------------------------------------------
// 分配空闲结点
//---------------------------------------------------------------------------
int SLinkList::malloc()
{
    int i = pData[0].cur; // 头结点指向第一个空闲结点
    if (i != 0)
    {
        pData[0].cur = pData[i].cur; // 修正空闲结点
    }
    return i;
}

//---------------------------------------------------------------------------
// 回收已使用的结点
//---------------------------------------------------------------------------
void SLinkList::free(int nUsed)
{
    pData[nUsed].cur = pData[0].cur;
    pData[0].cur = nUsed;
}

int main()
{
    SLinkList list;

    for (int i = 0; i < 10; ++i)
    {
        cout << list.malloc() << " ";
    }
    cout << endl;

    // for (int i = 10; i != 0; --i)
    // {
    //     list.free(i);
    // }

    for (int i = 1; i < 11; ++i)
    {
        list.free(i);
    }

    for (int i = 0; i < 10; ++i)
    {
        cout << list.malloc() << " ";
    }
    cout << endl;

    cout << list.malloc() << endl;
}