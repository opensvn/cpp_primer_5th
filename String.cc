#include <iostream>
#include <new>
#include <memory>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;

class String
{
    friend std::ostream &operator<<(std::operator &, const String &);
public:
    String(): elements(NULL), first_free(NULL), cap(NULL) {}
    String(const char *);
    String(const String&);
    String(String &&) noexcept;
    String &operator=(const String&);
    String &operator=(String &&) noexcept;
    ~String();

    void push_back(char);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }

    char *begin() const { return elements; }
    char *end() const { return first_free; }
    std::string str() { return std::string(elements, first_free); }
private:
    std::pair<char*, char*> alloc_n_copy(const char*,
                                         const char*);
    void chk_n_alloc()
    { if (size() == capacity()) reallocate(); }
    void free();
    void reallocate();

    std::allocator<char> alloc;
    char *elements;
    char *first_free;
    char *cap;
};

ostream &operator<<(ostream &out, const String &s)
{
    for (auto p = s.begin(); p != s.end(); ++p)
        out << *p;
}

pair<char*, char*> String::alloc_n_copy(const char *b,
                                        const char *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void String::free()
{
    if (elements) {
        while (--first_free != elements) {
            alloc.destroy(first_free);
        }
        alloc.deallocate(elements, capacity());
    }
}

void String::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);

    auto elem = elements;
    auto dest = newdata;

    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, *elem++);

    free();

    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

String::String(const char *s)
{
    cout << "String(const char*)" << endl;
    auto len = strlen(s);
    auto newdata = alloc_n_copy(s, s + len);
    elements = newdata.first;
    first_free = cap = newdata.second;
}

String::String(const String &str)
{
    cout << "String(const String&)" << endl;
    auto newdata = alloc_n_copy(str.begin(), str.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

String::String(String &&rhs) noexcept
    : elements(rhs.elements), first_free(rhs.first_free),
    cap(rhs.cap)
{
    cout << "String(String &&)" << endl;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
}

String &String::operator=(const String &rhs)
{
    cout << "operator=(const String&)" << endl;
    auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

String &String::operator=(String &&rhs) noexcept
{
    cout << "operator=(String &&)" << endl;
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
}

String::~String()
{
    cout << "~String()" << endl;
    free();
}

void String::push_back(char c)
{
    chk_n_alloc();
    alloc.construct(first_free++, c);
}

void print_stars(int num)
{
    for (auto i = 0; i != num; ++i)
    {
        cout << '*';
    }
    cout << endl;
}

int main()
{
    /*
    String s1 = "Hello, world";
    String s2 = s1;

    char *b = s2.begin();
    char *e = s2.end();
    while (--e >= b)
        s1.push_back(*e);

    cout << s2.str() << endl;
    cout << s1.str() << endl;*/

    vector<String> svec;
    print_stars(20); 
    svec.push_back("Hello");
    print_stars(20); 
    svec.push_back("world");
    print_stars(20); 
    svec.push_back("my name is");
    print_stars(20); 
    svec.push_back("jianzhangyu");

    print_stars(20); 
    String s = "Nice to mee you";
    svec.push_back(s);

    return 0;
}
