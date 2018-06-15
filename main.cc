#include "stringutil.h"

using namespace std;

int main() {
    std::string a("111111");
    std::string b("222222");
    std::string c;
    c = stringutil::StringCat(a, b);
    std::cout << c << '\n';
    return 0;
}
