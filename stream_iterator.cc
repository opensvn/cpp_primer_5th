#include <iostream>
#include <iterator>
#include <fstream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
  /*  istream_iterator<int> int_it(cin);
  istream_iterator<int> int_eof;
  ostream_iterator<int> int_out(cout, " ");
  vector<int> ivec(int_it, int_eof);
  sort(ivec.begin(), ivec.end());
  copy(ivec.cbegin(), ivec.cend(), int_out);

  ifstream in("stream_iterator.cc");
  istream_iterator<string> str_it(in);
  istream_iterator<string> str_eof;

  vector<string> svec(str_it, str_eof);
  ostream_iterator<string> str_out(cout, " ");
  copy(svec.cbegin(), svec.cend(), str_out);*/
  /*  for (const auto &s : svec)
    //    *str_out++ = s;
    str_out = s;*/
  /*
  for (const string &s : svec) {
    cout << s << " ";
    }*/
  cout << endl;

  /*while (str_it != str_eof) {
    cout << *str_it << " ";
    ++str_it;
  }
  cout << endl;*/
  /*
  ifstream number("number.txt");
  istream_iterator<int> number_in(number), number_eof;
  ofstream odd("odd.txt");
  ofstream even("even.txt");
  ostream_iterator<int> odd_out(odd, " ");
  ostream_iterator<int> even_out(even, " ");

  while (number_in != number_eof) {
    int n = *number_in;
    if (n % 2 == 0)
      even_out = n;
    else
      odd_out = n;
    ++number_in;
  }
  //  copy_if(number_in, number_eof, odd_out, [](int i){ return i % 2; });
  //  copy_if(number_in, number_eof, even_out, [](int i){ return !(i % 2); });

  number.close();
  odd.close();
  even.close();*/
  /*
  vector<int> ivec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for_each(ivec.crbegin(), ivec.crend(), [](int i){ cout << i << " ";});
  cout << endl;

  for (auto it = ivec.cend() - 1; it >= ivec.cbegin(); --it)
    cout << *it << " ";
  cout << endl;

  auto it = find_if(ivec.crbegin(), ivec.crend(), [](int i){ return i == 0; });
  if (it != ivec.crend())
  cout << *it << endl;*/

  list<string> slist = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
  slist.sort();
  slist.unique();
  for_each(slist.cbegin(), slist.cend(), [](const string &s){ cout << s << " "; });
  cout << endl;

  return 0;
}
