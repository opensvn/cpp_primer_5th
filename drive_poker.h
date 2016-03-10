#ifndef AFPOKER_H
#define AFPOKER_H

#include <map>
#include <vector>
#include "anyfish_type.h"

class AFPokerCode
{
private:
    U8 m_nData;

public:
    AFPokerCode(U8 nData=0);
    ~AFPokerCode();

    operator U8();

public:
    void SetClass(U8 nClass);
    void SetValue(U8 nValue);

    U8 GetClass(void);
    U8 GetValue(void);
};

class AFPoker
{
public:
    typedef std::map<int, int>::const_iterator map_cit;
    S32 m_nPoints[4][3]; // 三墩牌各自的分数
    S32 m_nResults[4]; // 总结果
    U8 m_nSpecial[4]; // 特殊牌
    U8 m_nFrusta[4]; // 总赢的墩数

    AFPoker();
    ~AFPoker();

    void Shuffle(U8 *pCard);
    bool Check_Array(U8 *pCard, int nLen);
    void Calc_Result(U8 *pCard, U8 *pCardType);
    int Calc_Special(U8 *pCard);
    void Place_Special(U8 *pCard, U8 nType);

    int Get_SpecialCard(U8 *pCard);
    static void Test();

private:
    static inline bool cmp_value(int a, int b);
    static inline bool cmp(int a, int b);
    void Pack_Card(U8 *pCard, int nLen, int nValue, int nClass);
    int Check_Serial(U8 *pCard, int nLen);
    bool Check_Serial(std::vector<int> &v);
    bool Unique_Array(U8 *pCard, int nLen);
    bool Check_Flush(const std::map<int, int> &classMap);
    bool Check_Straight_Flush(U8 *pCard, int nLen);
    bool Check_Three_Serial(const std::map<int, int> &valueMap, U8 *pCard);
    bool Check_Ace(U8 *valueMap, int nLen, U8 *pCard);
    bool Check_Normal(U8 *valueMap, int nLen, U8 *pCard);
    bool Set_PickValue(U8 *valueMap, int nLen, int nStart1,
                       U8 *pickValue, int nPick, int nStart2);
    void Set_PickedCards(U8 *pCard, U8 *pickValue);

    int Calc_Card(U8 *pCard, int nLen);
    int Get_Point(int nPoint, int nMode);
    int Get_Sum(U8 *pCard, int nLen);

    void Place_ThreeFlush(U8 *pCard, int nLen);
    void Place_FiveThree(U8 *pCard, int nLen);

    // 以下为测试用
    inline U8 Random_Color(void);
    inline U8 Random_Value(void);
    U8 Random_Choice(U8 *pCard, int nRange);
    void Random_Straight(U8 *pCard, int nCount);
    int Random_SpecialType(void);
    void display(U8 *pCard, int nLen);

    void Get_Three_Flush(U8 *pCard);
    void Get_Three_Straight(U8 *pCard);
    void Get_Six_Half(U8 *pCard);
    void Get_Five_Three(U8 *pCard);
    void Get_Four_Three(U8 *pCard);
    void Get_Same_Color(U8 *pCard);
    void Get_All_Small(U8 *pCard);
    void Get_All_Big(U8 *pCard);
    void Get_Three_Kingdom(U8 *pCard);
    void Get_Three_Straight_Flush(U8 *pCard);
    void Get_Twelve_Royal(U8 *pCard);
    void Get_A_Dragon(U8 *pCard);
    void Get_Flush_Dragon(U8 *pCard);
};

#endif // AFPOKER_H
