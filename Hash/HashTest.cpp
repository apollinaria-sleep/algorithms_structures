#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "hash.h"
#include "doctest.h"

void GenerateString(std::string* str, const int& quantity, const int& size) {
    char symbols[27]  = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < size; j++) {
            str[i].push_back(symbols[rand() % 26]);
        }
    }
}

int Compare(const std::string* str1, const std::string* str2) {
    return str1->compare(*str2);
}

unsigned int HashFunc(const std::string* str) {
    const int p = 31;
    unsigned int hash = 0, p_pow = 1;
    for (int i = 0; i < str->length(); ++i) {
        hash += (str->at(i) - 'a' + 1) * p_pow;
        p_pow *= p;
    }

    return hash;
}

TEST_CASE("hash") {
    lab618::CHash<std::string, &HashFunc, &Compare> hash(100, 10);

    std::string* strs = new std::string[100];
    GenerateString(strs, 100, 10);

    CHECK(hash.add(strs) == true);
    CHECK(hash.add(strs) == false);
    CHECK(hash.update(strs) == true);
    CHECK(hash.update(strs + 1) == false);
    CHECK(hash.find(strs[0]) != nullptr);
    CHECK(hash.find(strs[2]) == nullptr);
    CHECK(hash.remove(strs[0]) == true);
    CHECK(hash.remove(strs[2]) == false);
    CHECK(hash.find(strs[0]) == nullptr);
    hash.clear();
    CHECK(hash.find(strs[1]) == nullptr);
}
