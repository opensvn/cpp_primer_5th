#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef unsigned long long U64;
typedef int S32;
typedef unsigned int U32;

typedef struct tag_things
{
    U64  nCode;                       // 编码

    S32  nLongitude;                  // 经度
    S32  nLatitude;                   // 纬度

    U32 nType:8;
    U32 nGender: 2;                    // 性别，1男2女
    U32 nSub:8;
    U32 nFish:7;                      //投放的鱼克数(最大100g）
    U32 nGears:3;                         //投放档位
        #define _Gear_L0 0  // 无限制
        #define _Gear_L1 1  // 1公里
        #define _Gear_L2 2  // 4公里
        #define _Gear_L3 3  // 8公里
        #define _Gear_L4 4  // 20公里
    U32 nRe:4;                            // 保留
    U32 nRe2;

} Record_Things;

bool operator<(const tag_things &lhs, const tag_things &rhs)
{
    if (lhs.nCode != rhs.nCode)
    {
        return lhs.nCode < rhs.nCode;
    }

    if (lhs.nLatitude != rhs.nLatitude)
    {
        return lhs.nLatitude < rhs.nLatitude;
    }

    if (lhs.nLongitude != rhs.nLongitude)
    {
        return lhs.nLongitude < rhs.nLongitude;
    }

    return false;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "No input file!" << endl;
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");

    int num = 0;
    int cnt = 0;
    fread(&num, sizeof(int), 1, fp);
    printf("num: %d\n", num);

    Record_Things thing;
    set<Record_Things> rec_set;
    while (!feof(fp) && cnt < num)
    {
        fread(&thing, sizeof(Record_Things), 1, fp);
        rec_set.insert(thing);
        // printf("%lld, %d, %d, %d\n", thing.nCode, thing.nLongitude,
        //         thing.nLatitude, thing.nRe2);
        ++cnt;
    }

    fclose(fp);

    // ofstream out_file("1.dat");
    // out_file << num;

    // ostream_iterator<Record_Things> out_it(out_file, "");
    // copy(rec_set.begin(), rec_set.end(), out_it);
    // out.close();

    fp = fopen("1.dat", "wb");
    fwrite(&num, sizeof(int), 1, fp);
    cout << sizeof(Record_Things) << endl;
    for (auto it = rec_set.begin(); it != rec_set.end(); ++it)
    {
        // cout << it->nCode << ", " << it->nLongitude << ", " << it->nLatitude
        //     << ", " << it->nRe2 << endl;
        // out_file << *it;
        fwrite(&*it, sizeof(Record_Things), 1, fp);
        cout << sizeof(*it) << endl;
    }

    // out_file.close();

    return 0;
}