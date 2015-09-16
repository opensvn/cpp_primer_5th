#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;

void print_result(const vector<string> &v, const map<string, set<int>> &r, 
        const string &search_word)
{
    cout << search_word << " found at: " << endl;
    for (auto i : r[search_word])
    {
        cout << "line(" << i + 1 << "): " << v[i] << endl;
    }
}

void search(const vector<string> &v, const string &search_word)
{
    map<string, set<int>> result;
    result.insert(make_pair(search_word, set<int>()));

    for (decltype(v.size()) i = 0; i != v.size(); ++i)
    {
        istringstream stream(v[i]);
        string word;
        while (stream >> word)
        {
            if (word == search_word)
            {
                result[search_word].insert(i);
            }
        }
    }

    print_result(v, result, search_word);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " file" << endl;
        return -1;
    }

    ifstream infile(argv[1]);
    if (!infile)
    {
        cerr << "Can not open " << argv[1] << endl;
        return -1;
    }

    vector<string> file;
    string line;
    while (getline(infile, line))
        file.push_back(line);

    while (!cin)
    {
        string search_word;
        cin >> search_word;

        search(file, search_word);
    }

    return 0;
}
