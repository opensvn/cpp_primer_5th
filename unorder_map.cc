#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;

int main()
{
    unordered_map<string, size_t> word_count;

    ifstream in("Journey_to_West.txt");
    string word;

    while (in >> word)
    {
        ++word_count[word];
    }

    /*    for (const auto &w : word_count)
    {
        cout << w.first << " " << w.second << endl;
    }*/

    cout << "bucket_count: " << word_count.bucket_count() << endl;
    cout << "max_bucket_count: " << word_count.max_bucket_count() << endl;
    for (int i = 0; i < 1; ++i)
        cout << "bucket_size(n): " << word_count.bucket_size(0) << endl;
    cout << "bucket(k): " << word_count.bucket("the") << endl;
    cout << "load_factor: " << word_count.load_factor() << endl;
    cout << "max_load_factor: " << word_count.max_load_factor() << endl;
    
    in.close();

    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    unordered_map<int, int> i_u_map;
    for (int i = 0; i != 10; ++i)
    {
        i_u_map.insert({i, i});
    }

    for (auto i : i_u_map)
    {
        cout << i.first << " " << i.second << endl;
    }

    return 0;
}
