#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "sort.h"
#include "doctest.h"
#include <iostream>


struct Test {
    std::string str;
    int number;
    Test() {
        number = 0;
        str = "Test Sort";
    }

    Test(const std::string str, const int number): number(number), str(str) {}
};
bool operator==(const Test& left, const Test& right) {
    return left.str == right.str && left.number == right.number;
}

void GenerateString(std::string* str, const int& quantity, const int& size) {
    char symbols[27]  = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < size; j++) {
            str[i].push_back(symbols[rand() % 26]);
        }
    }
}

int Compare(const Test* first, const Test* second) {
    if (!first->str.compare(second->str)) {
        return first->number - second->number;
    }
    return first->str.compare(second->str);
}

TEST_CASE("easy test") {
    const int size = 1;
    std::string* strs = new std::string[size];
    int ints[] = {1};
    GenerateString(strs, 1, 10);

    Test** array = new Test*[size];
    for (int i = 0; i < size; i++) {
        array[i] = new Test(strs[i], ints[i]);
    }

    templates::mergeSort(array, size, Compare);
    Test true_value = Test(strs[0], ints[0]);
    CHECK(Compare(array[0], &true_value) == 0);

    for (int i = 0; i < size; ++i) {
        delete array[i];
    }
    delete array;
}

TEST_CASE("hard test") {
    const int size = 10;
    std::string* strs = new std::string[size];
    int ints[] = {10, 5, 1, 9, 6, 2, 7, 4, 3, 8};
    GenerateString(strs, 10, 10);

    Test** array = new Test*[size];
    for (int i = 0; i < size; i++) {
        array[i] = new Test(strs[i], ints[i]);
    }

    templates::mergeSort(array, size, Compare);
    for (int i = 0; i < size - 1; ++i) {
        CHECK(Compare(array[i], array[i + 1]));
    }

    for (int i = 0; i < size; ++i) {
        delete array[i];
    }
    delete array;
}

TEST_CASE("sort test") {
    const int size = 5;
    std::string strs[] = {"a", "aa", "aaa", "aaaa", "aaaaa"};
    int ints[] = {5, 1, 2, 4, 3};

    Test** array = new Test*[size];
    for (int i = 0; i < size; i++) {
        array[i] = new Test(strs[i], ints[i]);
    }

    templates::mergeSort(array, size, Compare);
    for (int i = 0; i < size ; ++i) {
        CHECK(*array[i] == Test(strs[i], ints[i]));
    }

    for (int i = 0; i < size; ++i) {
        delete array[i];
    }
    delete array;
}

TEST_CASE("reverse test") {
    const int size = 5;
    std::string strs[] = {"aaaaa", "aaaa", "aaa", "aa", "a"};
    int ints[] = {5, 1, 2, 4, 3};

    Test** array = new Test*[size];
    for (int i = 0; i < size; i++) {
        array[i] = new Test(strs[i], ints[i]);
    }

    templates::mergeSort(array, size, Compare);
    for (int i = 0; i < size ; ++i) {
        CHECK(*array[size - i - 1] == Test(strs[i], ints[i]));
    }

    for (int i = 0; i < size; ++i) {
        delete array[i];
    }
    delete array;
}

TEST_CASE("very big test") {
    const int size = 1000;
    std::string* strs = new std::string[size];
    GenerateString(strs, 1000, 10);

    Test** array = new Test*[size];
    for (int i = 0; i < size; i++) {
        array[i] = new Test(strs[i], std::rand() % size);
    }

    templates::mergeSort(array, size, Compare);
    for (int i = 0; i < size - 1; ++i) {
        CHECK(Compare(array[i], array[i + 1]));
    }

    for (int i = 0; i < size; ++i) {
        delete array[i];
    }
    delete array;
}
