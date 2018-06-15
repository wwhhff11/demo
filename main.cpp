#include <iostream>
#include <stdio.h>
#include "stringutil/stringutil.h"
#include <string>

using namespace std;

int main() {
    std::string a("111111");
    std::string b("222222");
    std::string c;
    c = StringCat(a, b);
    std::cout << c << '\n';

    Box box(1.0, 2.0, 3.0);
    std::cout << box.getVolume() << endl;

    return 0;
}
