#include <iostream>
#include <stdio.h>
#include <string>

#include "cpputil/stringutil/stringutil.h"
#include "cpputil/jsonutil/jsonutil.h"
#include <boost/timer.hpp>

int main() {
    std::cout << concat("111111", "222222") << std::endl;
    std::cout << find("1112222", "12") << std::endl;

    deserializer("{\"a\": 1}");

    boost::timer tm;

    //输出程序运行的时间长度
    std::cout << tm.elapsed();

    return 0;
}
