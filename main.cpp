#include <iostream>
#include <stdio.h>
#include <string>

#include "cpputil/stringutil/stringutil.h"
#include "cpputil/jsonutil/jsonutil.h"

int main() {
    std::cout << concat("111111", "222222") << std::endl;
    std::cout << find("1112222", "12") << std::endl;

    deserializer("{\"a\": 1}");

    return 0;
}
