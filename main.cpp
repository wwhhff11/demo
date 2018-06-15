#include <iostream>
#include <stdio.h>
#include <string>
#include "cpputil/stringutil/stringutil.h"

using namespace std;

int main() {
    std::cout << concat("111111", "222222") << '\n';
    std::cout << find("1112222", "12") << '\n';
    return 0;
}
