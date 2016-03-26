#include <boost/regex.hpp>
#include <locale>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    locale::global(locale("German"));
    string s = "Boris Schäling";
    boost::regex expr("\\w+\\s\\w+");
    cout << boost::regex_match(s, expr) << endl;
}