#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#include "fun.hpp"


int main() {
    MathFunction F({1, -5});
    MathFunction G({1, -1});
    MathFunction Q({7, 6});
    cout << (F * G + Q)(0) << endl;
    return 0;
}

// (x - 1) * (x - 5) = x^2 - 6x + 5
