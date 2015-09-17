#include <iostream>
#include <string>
#include <new>
#include <memory>
#include <utility>
#include <stdexcept>
using namespace std;

class StrVec
{
public:
    StrVec(): elements(nullptr), first_free(nullptr),
              cap(nullptr) {}
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec&);
    StrVec(StrVec&&) noexcept;
    StrVec &operator=(const StrVec&);
    StrVec &operator=(StrVec &&rhs) noexcept;
    ~StrVec();

    void push_back(const std::string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

    void reserve(size_t n);
    void resize(size_t n);
private:
    std::allocator<std::string> alloc;
    void chk_n_alloc()
    { if (size() == capacity()) reallocate(); }
    std::pair<std::string*, std::string*> alloc_n_copy
    (const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

StrVec::StrVec(initializer_list<string> il)
{
}

void StrVec::push_back(const string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

pair<string*, string*>
StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements) 
    {
        for (auto p = first_free; p != elements;)
            alloc.destroy(--p);
        alloc.deallocate(elements, capacity());
    }
}

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&s) noexcept
: elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec::~StrVec()
{
    free();
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    if (this != &rhs)
    {
        free(); // free existing elements
        // take over resources from rhs
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        // leave rhs in a destructible state
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

// void StrVec::reallocate()
// {
//     auto newcapacity = size() ? 2 * size() : 1;
//     auto newdata = alloc.allocate(newcapacity);
//     auto dest = newdata;
//     auto elem = elements;
//     for (size_t i = 0; i != size(); ++i)
//         alloc.construct(dest++, std::move(*elem++));
//     free();
//     elements = newdata;
//     first_free = dest;
//     cap = elements + newcapacity;
// }

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = uninitialized_copy(make_move_iterator(begin()),
        make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}

void StrVec::reserve(size_t n)
{
    if (n <= size())
        return;
    auto newdata = alloc.allocate(n);
    auto dest = newdata;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + n;
}

void StrVec::resize(size_t n)
{
    if (n > size()) {
        reserve(n);
        return;
    }
    else if (n < size()) {
        auto p = first_free;
        auto num = size() - n;
        while (num-- != 0)
            alloc.destroy(--first_free);
    }
}

int main()
{
    StrVec sv;
    sv.push_back("hello");
    sv.push_back("world");

    string *beg = sv.begin();
    while (beg != sv.end())
        cout << *beg++ << endl;

    return 0;
}
