#include <iostream>
using namespace std;

template <typename T, typename U>
void PerfectForward(T&& t, U& Func) {
    cout << t << "\tforwarded..." << endl;
    Func(forward<T>(t));
}

void RunCode(double&& m) {}
void RunHome(double&& h) {}
void RunComp(double&& c) {}

int main() {
    PerfectForward(1.5, RunComp);
    PerfectForward(8, RunCode);
    PerfectForward(1.5, RunHome);

    return 0;
}