#include <memory.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <unistd.h>

#include "drive_poker.h"
#include "anyfish_poker.h"

using std::random_shuffle;
using std::vector;
using std::map;
using std::sort;
using std::stringstream;
using std::cout;
using std::endl;
using std::cerr;

static int gaSpecial_Score[14] = {0, 4, 4, 4, 4, 0, 0, 4, 0, 0, 8, 0, 13, 26};

AFPokerCode::AFPokerCode(U8 nData)
{
    m_nData = nData;
}

AFPokerCode::~AFPokerCode()
{

}

AFPokerCode::operator U8()
{
    return m_nData;
}

void AFPokerCode::SetClass(U8 nClass)
{
    AnyfishPoker mPoker;
    memcpy(&mPoker, &m_nData, sizeof(U8));
    mPoker.nClass = nClass;
    memcpy(&m_nData, &mPoker, sizeof(U8));
}

void AFPokerCode::SetValue(U8 nValue)
{
    AnyfishPoker mPoker;
    memcpy(&mPoker, &m_nData, sizeof(U8));
    mPoker.nValue = nValue;
    memcpy(&m_nData, &mPoker, sizeof(U8));
}

U8 AFPokerCode::GetClass()
{
    AnyfishPoker mPoker;
    memcpy(&mPoker, &m_nData, sizeof(U8));
    return mPoker.nClass;
}

U8 AFPokerCode::GetValue()
{
    AnyfishPoker mPoker;
    memcpy(&mPoker, &m_nData, sizeof(U8));
    return mPoker.nValue;
}

AFPoker::AFPoker()
{

}

AFPoker::~AFPoker()
{

}

//---------------------------------------------------------------------------
// 洗牌
//---------------------------------------------------------------------------
void AFPoker::Shuffle(U8 *pCard)
{
    if (pCard == NULL) return;

    int nFlag = 0;
    for (int i = 0; i < NCARDS; ++i)
    {
        nFlag |= pCard[i];
    }

    if (nFlag == 0) // 新记录
    {
        for (int i = 0; i < NCARDS; ++i)
        {
            pCard[i] = i;
        }
    }

    srand(time(NULL));
    random_shuffle(pCard, pCard + NCARDS);

    sort(pCard, pCard + 13, cmp_value);
    sort(pCard + 13, pCard + 26, cmp_value);
    sort(pCard + 26, pCard + 39, cmp_value);
    sort(pCard + 39, pCard + 52, cmp_value);
}

//---------------------------------------------------------------------------
// 检查是否有相公牌
//---------------------------------------------------------------------------
bool AFPoker::Check_Array(U8 *pCard, int nLen)
{
    if (nLen != 14 || pCard == NULL)
    {
        return false;
    }

    if (pCard[nLen - 1] != 0)
    {
        if (Calc_Special(pCard)) return true;
    }

    U32 nP[3];

    nP[2] = Calc_Card(pCard + 8, 5);
    nP[1] = Calc_Card(pCard + 3, 5);
    nP[0] = Calc_Card(pCard, 3);

#ifndef NDEBUG
    printf("Three frusta points: %d, %d, %d\n", nP[0], nP[1], nP[2]);
#endif

    if (nP[0] > nP[1] || nP[1] > nP[2])
    {
        return false; // 倒水
    }

    return true;
}

//---------------------------------------------------------------------------
// 十三水计算结果
//---------------------------------------------------------------------------
void AFPoker::Calc_Result(U8 *pCard, U8 *pCardType)
{
    memset(m_nSpecial, 0, sizeof(m_nSpecial));
    memset(m_nFrusta, 0, sizeof(m_nFrusta));
    memset(m_nResults, 0, sizeof(m_nResults));

    U8 aCards[52]; // 玩家的牌
    memcpy(aCards, pCard, sizeof(aCards));

    for (int i = 0; i < 4; ++i)
    {
        m_nPoints[i][2] = Calc_Card(aCards + i * NCARDS_PER_PLAYER + 8, 5);
        m_nPoints[i][1] = Calc_Card(aCards + i * NCARDS_PER_PLAYER + 3, 5);
        m_nPoints[i][0] = Calc_Card(aCards + i * NCARDS_PER_PLAYER, 3);

        if (pCardType[i] != 0)
        {
            m_nSpecial[i] = Calc_Special(aCards + i * NCARDS_PER_PLAYER);
            Place_Special(pCard + i * NCARDS_PER_PLAYER, m_nSpecial[i]);
            pCardType[i] = m_nSpecial[i];
        }
    }

    U8 nSpecial[4] = {0}; // 按特殊牌型出牌的玩家
    U8 nNormal[4] = {0}; // 普通出牌的玩家
    int s = 0, n = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (pCardType[i] != 0 && m_nSpecial[i] > 0)
            nSpecial[s++] = i;
        else
            nNormal[n++] = i;
    }

    for (int i = 0; i < s; ++i) // 特殊牌型计分
    {
        int k = nSpecial[i];
        for (int j = 0; j < 4; ++j)
        {
            if (k != j)
            {
                if (m_nSpecial[k] == EPoker_A_Dragon
                        || m_nSpecial[k] == EPoker_Flush_Dragon)
                {
                    if (m_nSpecial[k] > m_nSpecial[j])
                    {
                        m_nResults[j] -= gaSpecial_Score[m_nSpecial[k]];
                        m_nResults[k] += gaSpecial_Score[m_nSpecial[k]];
                    }
                }
                else if (m_nSpecial[j] == 0)
                {
                    m_nResults[j] -= gaSpecial_Score[m_nSpecial[k]];
                    m_nResults[k] += gaSpecial_Score[m_nSpecial[k]];
                }
            }
        }
    }
//    int nResults[4][4] = {0}; // 玩家相对比分结果
    for (int i = 0; i < n - 1; ++i) // 普通出牌计分
    {
        int first = nNormal[i];
        for (int j = i + 1; j < n; ++j)
        {
            int second = nNormal[j];
            int nA1 = 0, nA2 = 0;

            for (int k = 0; k < 3; ++k) // 比较前中后墩分数
            {
                if (m_nPoints[first][k] > m_nPoints[second][k])
                {
                    nA1++;
                    m_nFrusta[first]++;
                    int nPoint = Get_Point(m_nPoints[first][k], k);
                    m_nResults[first] += nPoint;
                    m_nResults[second] -= nPoint;
                }
                else if (m_nPoints[first][k] < m_nPoints[second][k])
                {
                    nA2++;
                    m_nFrusta[second]++;
                    int nPoint = Get_Point(m_nPoints[second][k], k);
                    m_nResults[first] -= nPoint;
                    m_nResults[second] += nPoint;
                }
                else // 和了
                {
//                    ++nA1;
//                    ++nA2;
//                    ++m_nFrusta[first];
//                    ++m_nFrusta[second];
                }
            }

            if (nA1 == 3) // 打枪
            {
                m_nResults[first] += 1;
                m_nResults[second] -= 1;
            }
            else if (nA2 == 3) // 打枪
            {
                m_nResults[first] -= 1;
                m_nResults[second] += 1;
            }
        }
    }

    // 处理全垒打
    for (int i = 0; i < 4; ++i)
    {
        if (m_nFrusta[i] == 9)
        {
            m_nResults[i] += 3;
            for (int j = 0; j < 4; ++j)
            {
                if (i != j)
                {
                    m_nResults[j] -= 1;
                }
            }
            break;
        }
    }
}

//---------------------------------------------------------------------------
// 计算特殊牌型
//---------------------------------------------------------------------------
int AFPoker::Calc_Special(U8 *pCard)
{
    map<int, int> valueMap; // 不同牌各有多少张
    map<int, int> classMap; // 不同花色各有多少张
    map<int, int> colorMap; // 红色牌和黑色牌各有多少张

    int nCount_Max = 0; // 最多张的牌
    int nClass_Max = 0; // 最多张的花色

    for (int i = 0; i < 13; ++i)
    {
        int nValue = (pCard[i] >> 2) & 0x0F; // 0=2,1=3,2=4...10=Q,11=K,12=A
        int nClass = pCard[i] & 0x03;

        ++valueMap[nValue];
        ++classMap[nClass];

        if (valueMap[nValue] > nCount_Max)
            nCount_Max = valueMap[nValue];
        if (classMap[nClass] > nClass_Max)
            nClass_Max = classMap[nClass];

        if (nClass < 2) ++colorMap[0]; // 红色牌
        else ++colorMap[1]; // 黑色牌
    }

    if (nCount_Max == 1 && nClass_Max == 13) return EPoker_Flush_Dragon; // 至尊清龙
    if (nCount_Max == 1) return EPoker_A_Dragon; // 一条龙

    bool isFlush = false; // 三同花的标志
    int nTwelve_Royal = 0; // J, Q, K, A的个数
    int nAll_Small = 0; // <=8牌的个数
    int nAll_Big = 0; // 8以上牌的个数
    int nFour = 0; // 炸的个数
    int nThree = 0; // 3张的个数
    int nTwo = 0; // 对子的个数

    for (map_cit it = valueMap.begin(); it != valueMap.end(); ++it)
    {
        if (it->first >= 9) nTwelve_Royal += it->second;
        if (it->first < 7) nAll_Small += it->second;
        else if (it->first >= 8) nAll_Big += it->second;

        if (it->second == 4) ++nFour;
        else if (it->second == 3) ++nThree;
        else if (it->second == 2) ++nTwo;
    }

//    if (nTwelve_Royal == 13) return EPoker_Twelve_Royal; // 12皇族

    if (nClass_Max == 5 && classMap.size() == 3)
    {
        isFlush = Check_Flush(classMap);
        if (isFlush && Check_Straight_Flush(pCard, 13))
        {
            return EPoker_Three_Straight_Flush; // 三同花顺
        }
    }

//    if (nCount_Max == 4 && nFour == 3) return EPoker_Three_Kingdom; // 三分天下
//    if (nAll_Small == 0) return EPoker_All_Big; // 全大
    if (nAll_Big == 0) return EPoker_All_Small; // 全小(2-8)
//    if (colorMap[0] == 0) return EPoker_Same_Color; // 全黑
//    if (colorMap[1] == 0) return EPoker_Same_Color; // 全红
//    if (nCount_Max == 3 && nThree == 4) return EPoker_Four_Three; // 四套三条
    if (nCount_Max == 3 && nTwo == 5) return EPoker_Five_Three; // 五对三条
    if (nCount_Max == 2 && nTwo == 6) return EPoker_Six_Half; // 6对半
    if (Check_Three_Serial(valueMap, pCard)) return EPoker_Three_Straight; // 三顺子
    if (isFlush) return EPoker_Three_Flush; // 三同花

    return EPoker_Not_Special; // 非特殊牌型
}

//---------------------------------------------------------------------------
// 特殊牌型摆放
//---------------------------------------------------------------------------
void AFPoker::Place_Special(U8 *pCard, U8 nType)
{
    if (pCard == NULL) return;
    if (nType == 0) return; // 非特殊牌型

    switch (nType)
    {
        case EPoker_Three_Flush:
        case EPoker_Three_Straight_Flush:
            Place_ThreeFlush(pCard, NCARDS_PER_PLAYER);
            break;
        case EPoker_Three_Straight:
            // 已经在判断特殊牌型里面处理
            break;
        case EPoker_Five_Three:
            Place_FiveThree(pCard, NCARDS_PER_PLAYER);
            break;
        default:
            sort(pCard, pCard + NCARDS_PER_PLAYER, cmp_value);
            break;
    }
}

//---------------------------------------------------------------------------
// 升序排列(根据牌值)
//---------------------------------------------------------------------------
bool AFPoker::cmp_value(int a, int b)
{
    return (a >> 2) < (b >> 2);
}

//---------------------------------------------------------------------------
// 降序排列
//---------------------------------------------------------------------------
bool AFPoker::cmp(int a, int b)
{
    return a > b;
}

//---------------------------------------------------------------------------
// 加类别修饰符
//---------------------------------------------------------------------------
void AFPoker::Pack_Card(U8 *pCard, int nLen, int nValue, int nClass)
{
    for (int i = 0; i < nLen; ++i)
    {
        U8 nCard = (pCard[i] >> 2) & 0x0F;
        if (nCard == nValue)
        {
            pCard[i] |= (nClass << 6); // 加上类别修饰符
        }
    }
}

//---------------------------------------------------------------------------
// 检查顺子序列
//---------------------------------------------------------------------------
int AFPoker::Check_Serial(U8 *pCard, int nLen)
{
    if (pCard == NULL || (nLen != 3 && nLen != 5))
    {
        return false;
    }

    sort(pCard, pCard + nLen, cmp_value);

    cout << "------------------------" << endl;
    for (int i = 0; i < nLen; ++i)
    {
        cout << int(pCard[i]) << " ";
    }
    cout << endl;

    for (int i = 0; i < nLen; ++i)
    {
        cout << int(pCard[i] >> 2) << " ";
    }
    cout << endl;

    if (!Unique_Array(pCard, nLen))
    {
        return 0;
    }

    U8 nMax = pCard[nLen - 1] >> 2;
    U8 nMin = pCard[0] >> 2;

    cout << "------------------------" << endl;
    if (nMax == 12 && (nMax - nMin != nLen - 1)) // A
    {
        if ((pCard[nLen - 2] >> 2) - nMin == nLen - 2) return 12; // 序列A, 2, 3, 4, 5
    }


    if (nMax - nMin == nLen - 1)
    {
        return nMax == 12 ? 13 : nMax;
    }

    return 0;
}

//---------------------------------------------------------------------------
// 检查顺子序列
//---------------------------------------------------------------------------
bool AFPoker::Check_Serial(vector<int> &v)
{
    if (v.empty())
    {
        return false;
    }

    sort(v.begin(), v.end());
    vector<int>::iterator uniq = unique(v.begin(), v.end());
    if (uniq != v.end())
    {
        return false;
    }

    int nSize = v.size();
    int nMax = v[nSize - 1];
    int nMin = v[0];

    if (nMax == 12 && (nMax - nMin != nSize - 1)) // A
    {
        return v[nSize - 2] - nMin == nSize - 2; // 序列A, 2, 3, 4, 5
    }

    return nMax - nMin == nSize - 1;
}

//---------------------------------------------------------------------------
// 检查数组元素是否唯一(基于已排序的事实)
//---------------------------------------------------------------------------
bool AFPoker::Unique_Array(U8 *pCard, int nLen)
{
    for (int i = 0; i < nLen - 1; ++i)
    {
        if ((pCard[i] >> 2) == (pCard[i + 1] >> 2))
            return false;
    }
    return true;
}

//---------------------------------------------------------------------------
// 检查是否为同花
//---------------------------------------------------------------------------
bool AFPoker::Check_Flush(const map<int, int> &classMap)
{
    if (classMap.empty())
    {
        return false;
    }

    map_cit it = classMap.begin();
    while (it != classMap.end())
    {
        if (it->second != 3 && it->second != 5)
            break;
        ++it;
    }

    return it == classMap.end();
}

//---------------------------------------------------------------------------
// 判断是否为三同花顺(基于三同花)
//---------------------------------------------------------------------------
bool AFPoker::Check_Straight_Flush(U8 *pCard, int nLen)
{
    map<int, vector<int> > Class_Value_Map;
    for (int i = 0; i < nLen; ++i)
    {
        U8 nColor = pCard[i] & 0x03;
        U8 nValue = pCard[i] >> 2;

        Class_Value_Map[nColor].push_back(nValue);
    }

    for (map<int, vector<int> >::iterator it = Class_Value_Map.begin();
            it != Class_Value_Map.end(); ++it)
    {
        if (!Check_Serial(it->second))
        {
            return false;
        }
    }

    return true;
}

//---------------------------------------------------------------------------
// 计算牌墩
//---------------------------------------------------------------------------
int AFPoker::Calc_Card(U8 *pCard, int nLen)
{
    U8 aValueMap[13] = {0};
    U8 aClassMap[4] = {0};

    bool isFlush = 0; // 同花标志
    U8 nC4 = 0; // 炸弹的牌值
    U8 nC3 = 0; // 三张的牌值
    U8 nC22 = 0; // 两对的牌值
    U8 nC21 = 0; // 一对的牌值

    U8 nValue;
    U8 nClass;

    for (int i = 0; i < nLen; ++i)
    {
        nValue = (pCard[i] >> 2) & 0x0F;
        nClass = pCard[i] & 0x3;

        aValueMap[nValue]++;
        aClassMap[nClass]++;
    }

    if (aClassMap[nClass] == 5) // 同花
    {
        isFlush = true;
    }

    for (int i = 0; i < 13; ++i)
    {
        if (aValueMap[i] == 4) nC4 = i + 1;
        if (aValueMap[i] == 3) nC3 = i + 1;
        if (aValueMap[i] == 2)
        {
            if (nC21 == 0)
                nC21 = i + 1;
            else
                nC22 = i + 1;

            if (nC21 < nC22)
            {
                U8 nSwap = nC21;
                nC21 = nC22;
                nC22 = nSwap;
            }
        }
    }

    int nSerial = Check_Serial(pCard, nLen);

    if (nC4) Pack_Card(pCard, nLen, nC4 - 1, 0x3);
    if (nC3) Pack_Card(pCard, nLen, nC3 - 1, 0x2);
    if (nC21) Pack_Card(pCard, nLen, nC21 - 1, 0x1);
    if (nC22) Pack_Card(pCard, nLen, nC22 - 1, 0x1);

    sort(pCard, pCard + nLen, cmp);

    int nSum = Get_Sum(pCard, nLen);

    if (nSerial && nLen == 5)
    {
        return isFlush ? 0x800000 + nSerial : 0x400000 + nSerial; // 同花顺或顺子
    }
    if (nC4) return 0x700000 + nSum; // 铁支
    if (nC3 && nC21) return 0x600000 + nSum; // 葫芦
    if (isFlush) return 0x500000 + nSum; // 同花
    if (nC3) return 0x300000 + nSum; // 三条
    if (nC22) return 0x200000 + nSum;// 两对
    if (nC21) return 0x100000 + nSum;// 一对
    return nSum; // 乌龙
}

//---------------------------------------------------------------------------
// 判断三顺子
//---------------------------------------------------------------------------
bool AFPoker::Check_Three_Serial(const map<int, int> &valueMap, U8 *pCard)
{
    if (valueMap.empty() || pCard == NULL) return false;

    int nMax = 0;
    U8 innerMap[14] = {0}; // innerMap[0]在A与2,3,4,5组成顺子时保存A

    for (map_cit it = valueMap.begin(); it != valueMap.end(); ++it)
    {
        innerMap[it->first + 1] = it->second;
        if (it->second > nMax)
            nMax = it->second;
    }

    if (nMax == 1) return true;
    if (nMax > 3) return false;

    if (Check_Normal(innerMap, 14, pCard)) return true;

    if (innerMap[13] > 0) // 带A
    {
        if (Check_Ace(innerMap, 14, pCard)) return true;
    }

    return false;
}

//---------------------------------------------------------------------------
// 判断带A的牌是否为三顺子
//---------------------------------------------------------------------------
bool AFPoker::Check_Ace(U8 *valueMap, int nLen, U8 *pCard)
{
    if (valueMap == NULL || pCard == NULL || nLen != 14) return false;

    U8 innerMap[14] = {0}; // innerMap[0]在A与2,3,4,5组成顺子时保存A，innerMap[14]存放标志0

    for (int i = 0; i < valueMap[13]; ++i)
    {
        // 尝试将A和2,3,4,5组成顺子，重新组合map
        innerMap[0] = valueMap[13] - i;
        for (int j = 1; j < 13; ++j)
        {
            innerMap[j] = valueMap[j];
        }

        innerMap[13] = i;

        if (Check_Normal(innerMap, nLen, pCard))
        {
            return true;
        }
    }

    return false;
}

//---------------------------------------------------------------------------
// 由2-A顺序检测牌是否为顺子
//---------------------------------------------------------------------------
bool AFPoker::Check_Normal(U8 *valueMap, int nLen, U8 *pCard)
{
    if (valueMap == NULL || pCard == NULL || nLen != 14) return false;

    U8 innerMap[14] = {0}; // innerMap[0]在A与2,3,4,5组成顺子时保存A
    U8 pickValue[13] = {0};

    for (int i = 0; i < 12; ++i)
    {
        if (valueMap[i] == 0) continue;

        memcpy(innerMap, valueMap, sizeof(innerMap));

        if (!Set_PickValue(innerMap, 14, i, pickValue, 3, 0)) continue;
        if (!Set_PickValue(innerMap, 14, 0, pickValue, 5, 3)) continue;
        if (!Set_PickValue(innerMap, 14, 0, pickValue, 5, 8)) continue;

        Set_PickedCards(pCard, pickValue);
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
// 挑选顺子放入数组
//---------------------------------------------------------------------------
bool AFPoker::Set_PickValue(U8 *valueMap, int nLen, int nStart1,
                                     U8 *pickValue, int nPick, int nStart2)
{
    for (int i = nStart1; i < nLen; ++i)
    {
        if (valueMap[i] == 0) continue;

        for (int j = 0; j < nPick; ++j)
        {
            if (valueMap[i + j] == 0) return false;

            pickValue[nStart2 + j] = i + j;
            --valueMap[i + j];
        }

        break;
    }

    return true;
}

//---------------------------------------------------------------------------
// 按选好的三顺子顺序调整玩家的牌
//---------------------------------------------------------------------------
void AFPoker::Set_PickedCards(U8 *pCard, U8 *pickValue)
{
    for (int i = 0; i < 13; ++i)
    {
        if (pickValue[i] == 0)
        {
            pickValue[i] = 13;
            break;
        }
    }

    for (int i = 0; i < 12; ++i)
    {
        for (int j = i; j < 13; ++j)
        {
            if ((pCard[j] >> 2) == pickValue[i] - 1)
            {
                U8 nTmp = pCard[i];
                pCard[i] = pCard[j];
                pCard[j] = nTmp;
                break;
            }
        }
    }
}

//---------------------------------------------------------------------------
// 计算特殊牌型所在位置附加值
//---------------------------------------------------------------------------
int AFPoker::Get_Point(int nPoint, int nMode)
{
    int nType = nPoint >> 20;
    int nValue = 1;

    if (nMode == 0) // 前墩
    {
        if (nType == 3) nValue = 3; // 三条
    }
    else if (nMode == 1) // 中墩
    {
        if (nType == 6) nValue = 2; // 葫芦
        if (nType == 7) nValue = 8;//5; // 炸弹
        if (nType == 8) nValue = 10;//6; // 同花顺
    }
    else if (nMode == 2) // 后墩
    {
        if (nType == 7) nValue = 4; // 炸弹
        if (nType == 8) nValue = 5; // 同花顺
    }

    return nValue;
}

//---------------------------------------------------------------------------
// 计算牌墩分数
//---------------------------------------------------------------------------
int AFPoker::Get_Sum(U8 *pCard, int nLen)
{
    int nSum = 0;

    for (int i = 0; i < nLen; ++i)
    {
        U8 nCard = (pCard[i] >> 2) & 0x0F;
        nSum <<= 4;
        nSum += nCard;
    }

    if (nLen == 3) nSum <<= 8;

    return nSum;
}

//---------------------------------------------------------------------------
// 三同花摆放
//---------------------------------------------------------------------------
void AFPoker::Place_ThreeFlush(U8 *pCard, int nLen)
{
    map<int, vector<int> > Class_Value_Map;
    for (int i = 0; i < nLen; ++i)
    {
        U8 nColor = pCard[i] & 0x03;
        U8 nValue = pCard[i] >> 2;

        Class_Value_Map[nColor].push_back(nValue);
    }

    U8 nCards[13] = {0};
    int k = 3;

    for (map<int, vector<int> >::iterator it = Class_Value_Map.begin();
            it != Class_Value_Map.end(); ++it)
    {
        if (it->second.size() == 3)
        {
            for (vector<int>::size_type i = 0; i != it->second.size();
                    ++i)
            {
                nCards[i] = it->second[i] << 2 | it->first;
            }
        }
        else
        {
            for (vector<int>::size_type i = 0; i != it->second.size();
                    ++i)
            {
                nCards[k++] = it->second[i] << 2 | it->first;
            }
        }
    }

    sort(nCards, nCards + 3, cmp_value);
    sort(nCards + 3, nCards + 8, cmp_value);
    sort(nCards + 8, nCards + 13, cmp_value);

    memcpy(pCard, nCards, nLen);
}

//---------------------------------------------------------------------------
// 五对三条摆放
//---------------------------------------------------------------------------
void AFPoker::Place_FiveThree(U8 *pCard, int nLen)
{
    map<int, vector<int> > Value_Number_Map;
    for (int i = 0; i < nLen; ++i)
    {
        int nValue = pCard[i] >> 2;
        Value_Number_Map[nValue].push_back(pCard[i]);
    }

    U8 nCards[13] = {0};
    int k = 3;

    for (map<int, vector<int> >::iterator it = Value_Number_Map.begin();
            it != Value_Number_Map.end(); ++it)
    {
        if (it->second.size() == 3)
        {
            for (vector<int>::size_type i = 0; i != it->second.size();
                    ++i)
            {
                nCards[i] = it->second[i];
            }
        }
        else
        {
            for (vector<int>::size_type i = 0; i != it->second.size();
                    ++i)
            {
                nCards[k++] = it->second[i];
            }
        }
    }

    memcpy(pCard, nCards, nLen);
}

int AFPoker::Get_SpecialCard(U8 *pCard)
{
    int nType = Random_SpecialType();

    switch (nType)
    {
        case EPoker_Not_Special: break;
        case EPoker_Three_Flush: Get_Three_Flush(pCard); break;
        case EPoker_Three_Straight: Get_Three_Straight(pCard); break;
        case EPoker_Six_Half: Get_Six_Half(pCard); break;
        case EPoker_Five_Three: Get_Five_Three(pCard); break;
        case EPoker_Four_Three: Get_Four_Three(pCard); break;
        case EPoker_Same_Color: Get_Same_Color(pCard); break;
        case EPoker_All_Small: Get_All_Small(pCard); break;
        case EPoker_All_Big: Get_All_Big(pCard); break;
        case EPoker_Three_Kingdom: Get_Three_Kingdom(pCard); break;
        case EPoker_Three_Straight_Flush: Get_Three_Straight_Flush(pCard); break;
        case EPoker_Twelve_Royal: Get_Twelve_Royal(pCard); break;
        case EPoker_A_Dragon: Get_A_Dragon(pCard); break;
        case EPoker_Flush_Dragon: Get_Flush_Dragon(pCard); break;
        default: break;
    }

    return nType;
}

//---------------------------------------------------------------------------
// 测试用，获取三同花
//---------------------------------------------------------------------------
void AFPoker::Get_Three_Flush(U8 *pCard)
{
    U8 nCards[13] = {0};
    U8 nValues[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    int i = 0;
    // 生成前墩同花
    nColor = Random_Choice(nColors, 4);
    for (int j = 13; i < 3; ++i, --j)
    {
        nValue = Random_Choice(nValues, j);
        nCards[i] = nValue << 2 | nColor;
    }

    // 生成中墩同花
    nColor = Random_Choice(nColors, 3);
    for (int j = 13; i < 8; ++i, --j)
    {
        nValue = Random_Choice(nValues, j);
        nCards[i] = nValue << 2 | nColor;
    }

    // 生成后墩同花
    nColor = Random_Choice(nColors, 2);
    for (int j = 13; i < 13; ++i, --j)
    {
        nValue = Random_Choice(nValues, j);
        nCards[i] = nValue << 2 | nColor;
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取三顺子
//---------------------------------------------------------------------------
void AFPoker::Get_Three_Straight(U8 *pCard)
{
    U8 nCards[13] = {0};
    U8 nNumber_Map[13] = {0};
    U8 nValues[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    // 取值
    Random_Straight(nValues, 3);
    Random_Straight(nValues + 3, 5);
    Random_Straight(nValues + 8, 5);

    for (int i = 0; i < 13; ++i)
    {
        ++nNumber_Map[nValues[i]];
    }

    for (int i = 0; i < 13; ++i) // 上色
    {
        U8 nNumber = nNumber_Map[nValues[i]];
        nValue = nValues[i];

        for (int j = i, nCount = 0; j < 13 && nCount < nNumber; ++j)
        {
            if (nValues[j] == nValue)
            {
                nColor = Random_Choice(nColors, 4 - nCount);
                nCards[j] = nValue << 2 | nColor;
                ++nCount;
                --nNumber_Map[nValue];
            }
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取六对半
//---------------------------------------------------------------------------
void AFPoker::Get_Six_Half(U8 *pCard)
{
    U8 nCards[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 nNumber_Map[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    for (int i = 0, j = 13; i < 7; ++i, --j) // 取值
    {
        nValue = Random_Choice(nCards, j);
        if (i < 6)
            nNumber_Map[nValue] = 2;
        else
            nNumber_Map[nValue] = 1;
    }

    for (int i = 0, k = 0; i < 13; ++i) // 上色
    {
        for (int j = 0, l = 4; j < nNumber_Map[i]; ++j, --l)
        {
            nColor = Random_Choice(nColors, l);
            nCards[k++] = i << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取五对三条
//---------------------------------------------------------------------------
void AFPoker::Get_Five_Three(U8 *pCard)
{
    U8 nCards[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 nNumber_Map[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    for (int i = 0, j = 13; i < 6; ++i, --j) // 取值
    {
        nValue = Random_Choice(nCards, j);
        if (i < 5)
            nNumber_Map[nValue] = 2;
        else
            nNumber_Map[nValue] = 3;
    }

    for (int i = 0, k = 0; i < 13; ++i) // 上色
    {
        for (int j = 0, l = 4; j < nNumber_Map[i]; ++j, --l)
        {
            nColor = Random_Choice(nColors, l);
            nCards[k++] = i << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取四套三条
//---------------------------------------------------------------------------
void AFPoker::Get_Four_Three(U8 *pCard)
{
    U8 nCards[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 nNumber_Map[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    for (int i = 0, j = 13; i < 5; ++i, --j) // 取值
    {
        nValue = Random_Choice(nCards, j);
        if (i < 4)
            nNumber_Map[nValue] = 3;
        else
            nNumber_Map[nValue] = 1;
    }

    for (int i = 0, k = 0; i < 13; ++i) // 上色
    {
        for (int j = 0, l = 4; j < nNumber_Map[i]; ++j, --l)
        {
            nColor = Random_Choice(nColors, l);
            nCards[k++] = i << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取凑一色
//---------------------------------------------------------------------------
void AFPoker::Get_Same_Color(U8 *pCard)
{
    U8 nCards[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 nNumber_Map[13] = {0};
    U8 nColors[2][2] = {{0, 1}, {2, 3}};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    int i = 0;
    while (i < 13) // 取值
    {
        nValue = Random_Value();
        if (nNumber_Map[nValue] < 2)
        {
            ++nNumber_Map[nValue];
            ++i;
        }
    }

    nValue = Random_Value() % 2;
    for (int i = 0, k = 0; i < 13; ++i) // 上色
    {
        for (int j = 0, l = 2; j < nNumber_Map[i]; ++j, --l)
        {
            nColor = Random_Choice(nColors[nValue], l);
            nCards[k++] = i << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取全小
//---------------------------------------------------------------------------
void AFPoker::Get_All_Small(U8 *pCard)
{
    U8 nCards[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 nNumber_Map[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    int i = 0;
    while (i < 13) // 取值
    {
        nValue = Random_Value() % 7; // 牌值为2, 3, 4, 5, 6, 7, 8
        if (nNumber_Map[nValue] < 4)
        {
            ++nNumber_Map[nValue];
            ++i;
        }
    }

    for (int i = 0, k = 0; i < 13; ++i) // 上色
    {
        for (int j = 0, l = 4; j < nNumber_Map[i]; ++j, --l)
        {
            nColor = Random_Choice(nColors, l);
            nCards[k++] = i << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取全大
//---------------------------------------------------------------------------
void AFPoker::Get_All_Big(U8 *pCard)
{
    U8 nCards[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 nNumber_Map[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    int i = 0;
    while (i < 13) // 取值
    {
        nValue = Random_Value() % 7 + 6; // 牌值为8, 9, 10, J, Q, K, A
        if (nNumber_Map[nValue] < 4)
        {
            ++nNumber_Map[nValue];
            ++i;
        }
    }

    for (int i = 0, k = 0; i < 13; ++i) // 上色
    {
        for (int j = 0, l = 4; j < nNumber_Map[i]; ++j, --l)
        {
            nColor = Random_Choice(nColors, l);
            nCards[k++] = i << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取三分天下
//---------------------------------------------------------------------------
void AFPoker::Get_Three_Kingdom(U8 *pCard)
{
    U8 nCards[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    U8 Four_Value[4] = {0};
    U8 nColors[] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    for (int i = 0, j = 13; i < 4; ++i, --j) // 取值
    {
        nValue = Random_Choice(nCards, j);
        Four_Value[i] = nValue;
    }

    for (int i = 0, j = 0; j < 4 && i < 13; ++j) // 上色
    {
        for (int k = 0, l = 4; k < 4 && i < 13; ++k, --l)
        {
            nColor = Random_Choice(nColors, l);
            nCards[i++] = Four_Value[j] << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取三同花顺
//---------------------------------------------------------------------------
void AFPoker::Get_Three_Straight_Flush(U8 *pCard)
{
    U8 nCards[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nValues[13] = {0};
    U8 nColor = 0;

    srand(time(NULL));

    // 取值
    Random_Straight(nValues, 3);
    Random_Straight(nValues + 3, 5);
    Random_Straight(nValues + 8, 5);

    // 上色
    nColor = Random_Choice(nColors, 4);
    for (int i = 0; i < 3; ++i)
    {
        nCards[i] = nValues[i] << 2 | nColor;
    }

    nColor = Random_Choice(nColors, 3);
    for (int i = 3; i < 8; ++i)
    {
        nCards[i] = nValues[i] << 2 | nColor;
    }

    nColor = Random_Choice(nColors, 2);
    for (int i = 8; i < 13; ++i)
    {
        nCards[i] = nValues[i] << 2 | nColor;
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取十二皇族
//---------------------------------------------------------------------------
void AFPoker::Get_Twelve_Royal(U8 *pCard)
{
    U8 nCards[13] = {0};
    U8 nNumber_Map[13] = {0};
    U8 nColors[4] = {0, 1, 2, 3};
    U8 nColor = 0;
    U8 nValue = 0;

    srand(time(NULL));

    int i = 0;
    while (i < 13) // 取值
    {
        nValue = Random_Value() % 4 + 9; // 牌值为J, Q, K, A
        if (nNumber_Map[nValue] < 4)
        {
            ++nNumber_Map[nValue];
            ++i;
        }
    }

    for (int i = 0, k = 0; i < 13; ++i) // 上色
    {
        for (int j = 0, l = 4; j < nNumber_Map[i]; ++j, --l)
        {
            nColor = Random_Choice(nColors, l);
            nCards[k++] = i << 2 | nColor;
        }
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取一条龙
//---------------------------------------------------------------------------
void AFPoker::Get_A_Dragon(U8 *pCard)
{
    U8 nCards[13] = {0};
    U8 nColor = 0;

    srand(time(NULL));

    for (int i = 0; i < 13; ++i)
    {
        nColor = Random_Color();
        nCards[i] = i << 2 | nColor;
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 测试用，获取至尊清龙
//---------------------------------------------------------------------------
void AFPoker::Get_Flush_Dragon(U8 *pCard)
{
    U8 nCards[13] = {0};

    srand(time(NULL));
    U8 nColor = Random_Color();

    for (int i = 0; i < 13; ++i)
    {
        nCards[i] = i << 2 | nColor;
    }

    memcpy(pCard, nCards, 13);
}

//---------------------------------------------------------------------------
// 随机颜色 0红桃 1方块 2黑桃 3梅花
//---------------------------------------------------------------------------
U8 AFPoker::Random_Color(void)
{
    return rand() % 4;
}

//---------------------------------------------------------------------------
// 随机牌值 0-12
//---------------------------------------------------------------------------
U8 AFPoker::Random_Value(void)
{
    return rand() % 13;
}

//---------------------------------------------------------------------------
// 从指定数组随机取一个数
//---------------------------------------------------------------------------
U8 AFPoker::Random_Choice(U8 *pCard, int nRange)
{
    int i = rand() % nRange;

    U8 nPick = pCard[i];
    pCard[i] = pCard[nRange - 1];
    pCard[nRange - 1] = nPick;

    return nPick;
}

//---------------------------------------------------------------------------
// 随机生成顺子
//---------------------------------------------------------------------------
void AFPoker::Random_Straight(U8 *pCard, int nCount)
{
    U8 nValue = Random_Value();
    while (nValue > 13 - nCount && nValue < 12)
    {
        nValue = Random_Value();
    }

    if (nValue == 12)
    {
        pCard[0] = nValue;
        for (int i = 1; i < nCount; ++i)
        {
            pCard[i] = i - 1;
        }
    }
    else
    {
        for (int i = 0; i < nCount; ++i)
        {
            pCard[i] = nValue + i;
        }
    }
}

int AFPoker::Random_SpecialType(void)
{
    U8 aSpecial[] = {1, 2, 3, 4, 7, 10, 12, 13};
    return Random_Choice(aSpecial, sizeof(aSpecial));
}

void AFPoker::display(U8 *pCard, int nLen)
{
    for (int i = 0; i != nLen; ++i)
        cout << int(pCard[i]) << " ";
    cout << endl;
}

void AFPoker::Test()
{
    AFPoker thirteen_water;

//    U8 aPoker[52] = {0};
//    thirteen_water.Shuffle(aPoker);

//    U8 aCardType[4] = {1, 1, 1, 1};
//    thirteen_water.Calc_Result(aPoker, aCardType);

    srand(time(NULL));
    U8 aCard[13] = {0};
//    U8 aCard[13] = {48, 3, 7, 49, 2, 5, 11, 14, 13, 19, 22, 27, 31};
//    if (thirteen_water.Calc_Special(aCard))
//        cout << "right" << endl;
//    else
//        cout << "wrong" << endl;
#if 1
    for (int i = 0; i != 100; ++i)
    {
        int nType = thirteen_water.Get_SpecialCard(aCard);
        int nRet = thirteen_water.Calc_Special(aCard);

        switch (nType)
        {
            case EPoker_Three_Flush:
                cout << "EPoker_Three_Flush: ";
                break;
            case EPoker_Three_Straight:
                cout << "EPoker_Three_Straight: ";
                break;
            case EPoker_Six_Half:
                cout << "EPoker_Six_Half: ";
                break;
            case EPoker_Five_Three:
                cout << "EPoker_Five_Three: ";
                break;
            case EPoker_All_Small:
                cout << "EPoker_All_Small: ";
                break;
            case EPoker_Three_Straight_Flush:
                cout << "EPoker_Three_Straight_Flush: ";
                break;
            case EPoker_A_Dragon:
                cout << "EPoker_A_Dragon: ";
                break;
            case EPoker_Flush_Dragon:
                cout << "EPoker_Flush_Dragon: ";
                break;
        }
        thirteen_water.display(aCard, 13);

        if (nType != nRet)
        {
            cerr << "Calc_Special error: " << nType << " " << nRet << endl;
        }
        sleep(1);
    }
#endif
}
