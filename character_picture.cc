#include <iostream>
#include <cstring>
using namespace std;

class Picture {
    friend ostream& operator<<(ostream& o, const Picture& p);
    friend Picture frame(const Picture&);
    friend Picture operator&(const Picture&, const Picture&);
    friend Picture operator|(const Picture&, const Picture&);
public:
    Picture(): height(0), width(0), data(0) {}
    Picture(const char* const*, int);
    Picture(const Picture&);
    ~Picture();
    Picture& operator=(const Picture&);

    static int destruct_count;
private:
    int height, width;
    char *data;
    char& position(int row, int col) {
        return data[row * width + col];
    }
    char position(int row, int col) const {
        return data[row * width + col];
    }

    void init(int h, int w);
    void copy_block(int, int, const Picture&);
    void clear(int, int, int, int);
    static int max(int m, int n);
};

int Picture::destruct_count = 0;

int Picture::max(int m, int n) {
    return m > n ? m : n;
}

void Picture::init(int h, int w) {
    height = h;
    width = w;
    data = new char[height * width];
}

Picture::Picture(const char* const* array, int n) {
    int w = 0;

    for (int i = 0; i < n; ++i)
        w = Picture::max(w, strlen(array[i]));

    init(n, w);

    for (int i = 0; i < n; ++i) {
        const char* src = array[i];
        int len = strlen(src);
        int j = 0;

        while (j < len) {
            position(i, j) = src[j];
            ++j;
        }
        while (j < width) {
            position(i, j) = ' ';
            ++j;
        }
    }
}

Picture::Picture(const Picture& p):
    height(p.height), width(p.width),
    data(new char[height * width]) {
    copy_block(0, 0, p);
}

Picture::~Picture() {
    delete[] data;
    ++destruct_count;
    cout << "destruct count: " << destruct_count << endl;
}

Picture& Picture::operator=(const Picture& p) {
    if (this != &p) {
        delete[] data;
        init(p.height, p.width);
        copy_block(0, 0, p);
    }
    return *this;
}

void Picture::copy_block(int row, int col, const Picture& p) {
    for (int i = 0; i < p.height; ++i) {
        for (int j = 0; j < p.width; ++j)
            position(row + i, col + j) = p.position(i, j);
    }
}

void Picture::clear(int r1, int c1, int r2, int c2) {
    for (int r = r1; r < r2; ++r) {
        for (int c = c1; c < c2; ++c)
            position(r, c) = ' ';
    }
}

ostream& operator<<(ostream& o, const Picture& p) {
    for (int i = 0; i < p.height; ++i) {
        for (int j = 0; j < p.width; ++j)
            o << p.position(i, j);
        o << endl;
    }
    return o;
}

Picture frame(const Picture& p) {
    Picture r;
    r.init(p.height + 2, p.width + 2);

    for (int i = 1; i < r.height - 1; ++i) {
        r.position(i, 0) = '|';
        r.position(i, r.width - 1) = '|';
    }
    for (int i = 1; i < r.width - 1; ++i) {
        r.position(0, i) = '-';
        r.position(r.height - 1, i) = '-';
    }

    r.position(0, 0) = '+';
    r.position(0, r.width - 1) = '+';
    r.position(r.height - 1, 0) = '+';
    r.position(r.height - 1, r.width - 1) = '+';

    r.copy_block(1, 1, p);

    return r;
}

Picture operator&(const Picture& p, const Picture& q) {
    Picture r;
    r.init(p.height + q.height, Picture::max(p.width, q.width));

    r.clear(0, p.width, p.height, r.width);
    r.clear(p.height, q.width, r.height, r.width);

    r.copy_block(0, 0, p);
    r.copy_block(p.height, 0, q);

    return r;
}

Picture operator|(const Picture& p, const Picture& q) {
    Picture r;
    r.init(Picture::max(p.height, q.height), p.width + q.width);

    r.clear(p.height, 0, r.height, p.width);
    r.clear(q.height, p.width, r.height, r.width);

    r.copy_block(0, 0, p);
    r.copy_block(0, p.width, q);

    return r;
}

int main() {
    const char *a[] = {"Paris", "in the", "spring", "is", "Beautiful"};

    Picture p(a, 5);
    cout << frame(frame(frame(frame(frame(p))))) << endl;
    // cout << p << endl;

    // Picture q = frame(p);
    // cout << q << endl;

    // Picture r = p | q;
    // cout << r << endl;

    // Picture s = q & r;
    // cout << s << endl << frame(s) << endl;

    return 0;
}