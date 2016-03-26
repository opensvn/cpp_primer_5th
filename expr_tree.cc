#include <iostream>
#include <string>
using namespace std;

class Expr_node;

class Expr {
    friend class Expr_node;
    friend ostream& operator<<(ostream&, const Expr&);
    Expr_node* p;
public:
    Expr(int);
    Expr(const string&, Expr);
    Expr(const string&, Expr, Expr);
    Expr(const Expr& t);
    Expr& operator=(const Expr&);
    ~Expr();
    int eval() const;
};

class Expr_node {
    friend ostream& operator<<(ostream&, const Expr&);
    friend class Expr;

    int use;
protected:
    Expr_node(): use(1) {}
    virtual void print(ostream&) const = 0;
    virtual ~Expr_node() {}
    virtual int eval() const = 0;
};

Expr::Expr(const Expr& t) {
    p = t.p;
    ++p->use;
}

Expr::~Expr() {
    if (--p->use == 0)
        delete p;
}

int Expr::eval() const {
    return p->eval();
}

class Int_node: public Expr_node {
    friend class Expr;
    int n;
    Int_node(int k): n(k) {}
    void print(ostream& o) const { o << n; }
    int eval() const { return n; }
};

class Unary_node: public Expr_node {
    friend class Expr;
    string op;
    Expr opnd;
    Unary_node(const string& a, Expr b): op(a), opnd(b) {}
    void print(ostream& o) const {
        o << "(" << op << opnd << ")";
    }
    int eval() const;
};

int Unary_node::eval() const {
    if (op == "-")
        return -opnd.eval();
    throw "error, bad op " + op + " in UnaryNode.";
}

class Binary_node: public Expr_node {
    friend class Expr;
    string op;
    Expr left;
    Expr right;
    Binary_node(const string& a, Expr b, Expr c):
        op(a), left(b), right(c) {}
    void print(ostream& o) const {
        o << "(" << left << op << right << ")";
    }
    int eval() const;
};

int Binary_node::eval() const {
    int op1 = left.eval();
    int op2 = right.eval();

    if (op == "-") return op1 - op2;
    if (op == "+") return op1 + op2;
    if (op == "*") return op1 * op2;
    if (op == "/" && op2 != 0) return op1 / op2;

    throw "error, bad op " + op + " in BinaryNode.";
}

Expr::Expr(int n) {
    p = new Int_node(n);
}

Expr::Expr(const string& op, Expr t) {
    p = new Unary_node(op, t);
}

Expr::Expr(const string& op, Expr left, Expr right) {
    p = new Binary_node(op, left, right);
}

Expr& Expr::operator=(const Expr& rhs) {
    ++rhs.p->use;
    if (--p->use == 0)
        delete p;
    p = rhs.p;
    return *this;
}

ostream& operator<<(ostream& o, const Expr& t) {
    t.p->print(o);
    return o;
}

int main() {
    Expr t = Expr("*", Expr("-", 5), Expr("+", 3, 4));
    cout << t << " = " << t.eval() << endl;

    t = Expr("*", t, t);
    cout << t << " = " << t.eval() << endl;

    return 0;
}