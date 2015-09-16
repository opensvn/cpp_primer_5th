#include <iterator>
#include <iostream>
#include <iterator>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <cctype>
#include <utility>
#include <vector>
using namespace std;

void my_lower(string &s)
{
    for (auto &c : s)
        c = tolower(c);
}

void del_punct(string &s)
{
    string t(s);
    s.clear();
    for (const auto &c : t)
    {
        if (!ispunct(c))
            s += c;
    }
}

pair<string, int> process(vector<string> &v)
{
    if (!v.empty())
        return {v.back(), v.back().size()};
    else
        return pair<string, int>();
}

int main()
{
    ifstream in("Journey_to_West.txt");
    istream_iterator<string> it_in(in), it_eof;

    map<string, size_t> word_cnt;
    /*  set<string> exclude = {"The", "But", "And", "Or", "An", "A",
        "the", "but", "and", "or", "an", "a"};*/
    while (it_in != it_eof)
    {
        string word = *it_in;
        my_lower(word);
        del_punct(word);
        //    if (exclude.find(*it_in) == exclude.end())
        //++word_cnt[word];
        auto ret = word_cnt.insert({word, 1});
        if (!ret.second)
        {
            ++ret.first->second;
        }
        ++it_in;
    }

    /*  for (const auto &word : word_cnt) {
      cout << word.first << " occurs " << word.second
           << ((word.second > 1) ? " times" : " time") << endl;
           }*/
    auto map_it = word_cnt.begin();
    while (map_it != word_cnt.end())
    {
        cout << map_it->first << "\t" << map_it->second << endl;
        ++map_it;
    }

    in.close();

    multiset<string> c;
    vector<string> v = {"Hello", "world", "my"};
    copy(v.begin(), v.end(), inserter(c, c.end()));
    //  copy(v.begin(), v.end(), back_inserter(c));
    for (const auto &s : c)
    {
        cout << s << " ";
    }
    cout << endl;

    copy(c.begin(), c.end(), inserter(v, v.end()));
    copy(c.begin(), c.end(), back_inserter(v));

    for (const auto &s : v)
    {
        cout << s << " ";
    }
    cout << endl;

    map<string, vector<int>> m_v_i;
    string word;
    //    auto r_i = m_v_i.find(word);
    map<string, vector<int>>::iterator r_it = m_v_i.find(word);

    return 0;
}
