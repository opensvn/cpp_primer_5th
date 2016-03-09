class Poly;
typedef Poly P;

class LiLei {
    friend class Poly;
};

class Jim {
    friend Poly;
};

class HanMeiMei {
    friend P;
};

class A;

template <typename T>
class People {
    friend T;
};

int main()
{
    People<A> PP;
    People<int> Pi;

    return 0;
}