#include <memory>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() const
    {
        return data->size();
    }
    bool empty() const
    {
        return data->empty();
    }
    void push_back(const string &t)
    {
        data->push_back(t);
    }
    void push_back(string &&t)
    {
        data->push_back(std::move(t));
    }
    void pop_back();
    string &front();
    const string &front() const;
    string &back();
    const string &back() const;

    StrBlobPtr begin();
    StrBlobPtr end();
private:
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};

class StrBlobPtr
{
public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0):
        wptr(a.data), curr(sz) {}
    std::string& deref() const;
    StrBlobPtr& incr();

    bool operator!=(const StrBlobPtr &rhs);
private:
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

StrBlob::StrBlob()
    : data(make_shared<vector<string>>())
{
}

StrBlob::StrBlob(initializer_list<string> il)
    : data(make_shared<vector<string>>(il))
{
}

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw out_of_range(msg);
}

string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

const string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string &StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

const string &StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret;
}

string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

bool StrBlobPtr::operator!=(const StrBlobPtr &rhs)
{
    if (this == &rhs)
        return false;
    if (curr != rhs.curr)
        return true;
    else
        return false;
}

int main()
{
    ifstream in("blobstr.cc");
    if (!in)
        cerr << "can not open file" << endl;

    StrBlob sb;

    string line;
    while (getline(in, line))
    {
        sb.push_back(line);
    }

    for (StrBlobPtr p = sb.begin(); p != sb.end(); p.incr())
    {
        cout << p.deref() << endl;
    }

    return 0;
}
