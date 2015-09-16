#include <deque>
#include <list>
#include <functional>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void print_vs(const vector<string> &svec)
{
    for (const auto &s : svec)
    {
        cout << s << " ";
    }
    cout << endl;

    for_each(svec.cbegin(), svec.cend(), [](const string &s)
    {
        cout << s << " ";
    });
    cout << endl;
}

ostream &print(ostream &os, const string &s, char c)
{
    return os << s << c;
}

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

bool check_size(const string &s, string::size_type sz)
{
    return s.size() > sz;
}

void elimDups(vector<string> &words)
{
    sort(words.begin(), words.end());
    sort(words.begin(), words.end(), isShorter);
    print_vs(words);

    auto end_unique = unique(words.begin(), words.end());
    print_vs(words);

    words.erase(end_unique, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
    elimDups(words);
    /*    stable_sort(words.begin(), words.end(), [](const string & a, const string & b)
    {
        return a.size() < b.size();
    });
    auto wc = find_if(words.begin(), words.end(),
                      [sz](const string & a)
    {
        return a.size() > sz;
    });
    for_each(wc, words.end(),
             [](const string & a)
    {
        cout << a << " ";
    });
    cout << endl;
    auto wc = partition(words.begin(), words.end(),
                        [sz](const string & a)
    {
        return a.size() > sz;
    });
    for_each(words.begin(), wc,
             [](const string & a)
    {
        cout << a << " ";
    });
    cout << endl;*/
    auto wc = stable_partition(words.begin(), words.end(),
                               [sz](const string & a)
    {
        return a.size() > sz;
    });
    for_each(words.begin(), wc,
             [](const string & a)
    {
        cout << a << " ";
    });
    cout << endl;
}

int main()
{
    vector<int> ivec = {0, 1, 2, 3};
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    vector<string> svec = {"Hello", "world"};
    cout << accumulate(svec.cbegin(), svec.cend(), string("")) << endl;

    vector<double> dvec = {1.1, 2.1, 3.1, 4.1};
    cout << accumulate(dvec.cbegin(), dvec.cend(), 0) << endl;

    fill(ivec.begin(), ivec.end(), 0);
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    fill(ivec.begin(), ivec.begin() + ivec.size() / 2, 10);
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    fill_n(ivec.begin(), ivec.size(), 0);
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    auto it = back_inserter(ivec);
    for (double d : dvec)
    {
        *it = d;
    }
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    ivec.clear();
    fill_n(back_inserter(ivec), 10, 2);
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    ivec.clear();
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    copy(begin(a), end(a), back_inserter(ivec));
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    replace(ivec.begin(), ivec.end(), 0, 42);
    cout << accumulate(ivec.cbegin(), ivec.cend(), 0) << endl;

    dvec.clear();
    replace_copy(ivec.begin(), ivec.end(), back_inserter(dvec), 0, 42);
    cout << accumulate(dvec.cbegin(), dvec.cend(), 0) << endl;

    svec.clear();
    svec = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    print_vs(svec);

    list<string> slist;
    unique_copy(svec.begin(), svec.end(), slist.begin());
    for_each(slist.cbegin(), slist.cend(), [](const string & a)
    {
        cout << a << " ";
    });
    cout << endl;

    elimDups(svec);
    stable_sort(svec.begin(), svec.end(), isShorter);
    print_vs(svec);

    auto iter = partition(svec.begin(), svec.end(), bind(check_size, placeholders::_1, 4));
    for_each(svec.begin(), svec.end(), bind(print, ref(cout), placeholders::_1, ' '));
    cout << endl;
    for (auto it = svec.begin(); it != iter; ++it)
        cout << *it << " ";
    cout << endl;
    print_vs(svec);

    biggies(svec, 4);
    cout << count_if(svec.begin(), svec.end(), [](const string & a)
    {
        return a.size() > 4;
    }) << endl;

    auto f = [](int a, int b)
    {
        return a + b;
    };
    cout << f(3, 4) << endl;

    int c = 3;
    auto g = [c](int b)
    {
        return c + b;
    };
    cout << g(4) << endl;

    auto h = [c]() mutable ->bool { return --c ? true : false; };
    while (bool b = h())
        cout << b << endl;

    deque<int> dve;
    dve.clear();
    copy(begin(a), end(a), back_inserter(dve));
    for_each(dve.begin(), dve.end(), [](int i) { cout << i << ""; });
    cout << endl;

    dve.clear();
    copy(begin(a), end(a), front_inserter(dve));
    for_each(dve.begin(), dve.end(), [](int i) { cout << i << ""; });
    cout << endl;

    dve.clear();
    copy(begin(a), end(a), inserter(dve, dve.begin()));
    for_each(dve.begin(), dve.end(), [](int i) { cout << i << ""; });
    cout << endl;

    return 0;
}
