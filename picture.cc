#include <iostream>
#include <cstring>
using namespace std;

class P_Node;
class Picture {
    friend ostream& operator<<(ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture reframe(const Picture&, char, char, char);
    friend Picture operator&(const Picture&, const Picture&);
    friend Picture operator|(const Picture&, const Picture&);

    friend class String_Pic;
    friend class Frame_Pic;
    friend class VCat_Pic;
    friend class HCat_Pic;
public:
    Picture();
    Picture(const char* const*, int);
    Picture(const Picture&);
    ~Picture();
    Picture& operator=(const Picture&);
private:
    Picture(P_Node*);
    P_Node* p;
    int height() const;
    int width() const;
    void display(ostream&, int, int) const;
};

Picture reframe(const Picture&, char, char, char);

class P_Node {
    friend class Picture;
    friend Picture reframe(const Picture&, char, char, char);
protected:
    P_Node();
    virtual ~P_Node();
    virtual int height() const = 0;
    virtual int width() const = 0;
    virtual void display(ostream&, int, int) const = 0;
    virtual Picture reframe(char, char, char) = 0;
    static int max(int, int);
    int use;
};

class String_Pic: public P_Node {
    friend class Picture;
    String_Pic(const char* const*, int);
    ~String_Pic();
    int height() const;
    int width() const;
    void display(ostream&, int, int) const;
    Picture reframe(char, char, char);
    char** data;
    int size;
};

class Frame_Pic: public P_Node {
    friend Picture frame(const Picture&);
    Frame_Pic(const Picture&, char='+', char='|', char='-');
    int height() const;
    int width() const;
    void display(ostream&, int, int) const;
    Picture reframe(char, char, char);
    Picture p;
    char corner;
    char sideborder;
    char topborder;
};

class VCat_Pic: public P_Node {
    friend Picture operator&(const Picture&, const Picture&);
    VCat_Pic(const Picture&, const Picture&);
    int height() const;
    int width() const;
    void display(ostream&, int, int) const;
    Picture reframe(char, char, char);
    Picture top, bottom;
};

class HCat_Pic: public P_Node {
    friend Picture operator|(const Picture&, const Picture&);
    HCat_Pic(const Picture&, const Picture&);
    int height() const;
    int width() const;
    void display(ostream&, int, int) const;
    Picture reframe(char, char, char);
    Picture left, right;
};

Picture::Picture(const char* const* str, int n):
    p(new String_Pic(str, n)) {}

Picture::Picture(const Picture& orig): p(orig.p) {
    ++orig.p->use;
}

Picture::~Picture() {
    if (--p->use == 0)
        delete p;
}

Picture::Picture(P_Node* p_node): p(p_node) {}

Picture& Picture::operator=(const Picture& orig) {
    ++orig.p->use;
    if (--p->use == 0)
        delete p;
    p = orig.p;
    return *this;
}

int Picture::height() const {
    return p->height();
}

int Picture::width() const {
    return p->width();
}

void Picture::display(ostream& o, int x, int y) const {
    p->display(o, x, y);
}

P_Node::~P_Node() {}
P_Node::P_Node(): use(1) {}

int P_Node::max(int m, int n) {
    return m > n ? m : n;
}

String_Pic::String_Pic(const char* const* p, int n):
    data(new char*[n]), size(n) {
    for (int i = 0; i < n; ++i) {
        data[i] = new char[strlen(p[i]) + 1];
        strcpy(data[i], p[i]);
    }
}

String_Pic::~String_Pic() {
    for (int i = 0; i < size; ++i)
        delete[] data[i];
    delete[] data;
}

int String_Pic::height() const {
    return size;
}

int String_Pic::width() const {
    int w = 0;
    for (int i = 0; i < size; ++i)
        w = max(w, strlen(data[i]));
    return w;
}

static void pad(ostream& os, int x, int y) {
    for (int i = x; i < y; ++i)
        os << " ";
}

void String_Pic::display(ostream& os, int row, int width) const {
    int start = 0;
    if (row >= 0 && row < height()) {
        os << data[row];
        start = strlen(data[row]);
    }
    pad(os, start, width);
}

Picture String_Pic::reframe(char c, char s, char t) {
    ++use;
    return this;
}

Frame_Pic::Frame_Pic(const Picture& pic, char c, char s, char t)
    : p(pic), corner(c), sideborder(s), topborder(t) {}

int Frame_Pic::height() const {
    return p.height() + 2;
}

int Frame_Pic::width() const {
    return p.width() + 2;
}

void Frame_Pic::display(ostream& os, int row, int wd) const {
    if (row < 0 || row >= height()) {
        pad(os, 0, wd);
    }
    else {
        if (row == 0 || row == height() - 1) {
            os << corner;
            int i = p.width();
            while (--i >= 0)
                os << topborder;
            os << corner;
        }
        else {
            os << sideborder;
            p.display(os, row - 1, p.width());
            os << sideborder;
        }
        pad(os, width(), wd);
    }
}

Picture Frame_Pic::reframe(char c, char s, char t) {
    return new Frame_Pic(::reframe(p, c, s, t), c, s, t);
}

VCat_Pic::VCat_Pic(const Picture& t, const Picture& b):
    top(t), bottom(b) {}

int VCat_Pic::height() const {
    return top.height() + bottom.height();
}

int VCat_Pic::width() const {
    return max(top.width(), bottom.width());
}

void VCat_Pic::display(ostream& os, int row, int wd) const {
    if (row >= 0 && row < top.height())
        top.display(os, row, wd);
    else if (row < top.height() + bottom.height())
        bottom.display(os, row - top.height(), wd);
    else
        pad(os, 0, wd);
}

Picture VCat_Pic::reframe(char c, char s, char t) {
    return new VCat_Pic(
        ::reframe(top, c, s, t),
        ::reframe(bottom, c, s, t));
}

HCat_Pic::HCat_Pic(const Picture& l, const Picture& r):
    left(l), right(r) {}

int HCat_Pic::height() const {
    return max(left.height(), right.height());
}

int HCat_Pic::width() const {
    return left.width() + right.width();
}

void HCat_Pic::display(ostream& os, int row, int wd) const {
    left.display(os, row, left.width());
    right.display(os, row, right.width());
    pad(os, width(), wd);
}

Picture HCat_Pic::reframe(char c, char s, char t) {
    return new HCat_Pic(
        ::reframe(left, c, s, t),
        ::reframe(right, c, s, t));
}

ostream& operator<<(ostream& os, const Picture& pic) {
    int ht = pic.height();
    for (int i = 0; i < ht; ++i) {
        pic.display(os, i, 0);
        os << endl;
    }
    return os;
}

Picture frame(const Picture& pic) {
    return new Frame_Pic(pic);
}

Picture reframe(const Picture& pic, char c, char s, char t) {
    return pic.p->reframe(c, s, t);
}

Picture operator&(const Picture& t, const Picture& b) {
    return new VCat_Pic(t, b);
}

Picture operator|(const Picture& l, const Picture& r) {
    return new HCat_Pic(l, r);
}

int main()
{
    const char *a[] = {"Paris", "in the", "spring", "is", "Beautiful"};

    Picture p(a, 5);
    Picture pic = frame(frame(p) & (p | frame(p)));
    // cout << pic << endl;

    cout << reframe(pic, '+', '|', '-') << endl;

    return 0;
}