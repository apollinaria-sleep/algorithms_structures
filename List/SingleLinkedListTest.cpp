#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "list.h"
#include "doctest.h"
#include <iostream>


TEST_CASE("size") {
    lab618::CSingleLinkedList<int> list;
    CHECK(list.getSize() == 0);

}


TEST_CASE("push back") {
    lab618::CSingleLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }
    CHECK(list.getSize() == size);
}


TEST_CASE("pop front") {
    lab618::CSingleLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    for (int element = 0; element < size; ++element) {
        CHECK(element == list.popFront());
    }
    CHECK(list.getSize() == 0);
}


TEST_CASE("push front") {
    lab618::CSingleLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushFront(element);
    }
    CHECK(list.getSize() == size);
    for (int element = size - 1; element >= 0; --element) {
        CHECK(element == list.popFront());
    }
}


TEST_CASE("erase") {
    lab618::CSingleLinkedList<int> list;

    int size = rand() % 1000;
    size = size % 2 ? (size + 1) : size;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    lab618::CSingleLinkedList<int>::CIterator it = list.begin();
    for (int i = 0; i < size / 2; ++i) {
        ++it;
    }
    while (it.isValid()) {
        list.erase(it);
        ++it;
    }

    it = list.begin();
    for (int element = 0; element < size / 4; ++element) {
        CHECK(element == *it);
        list.erase(it);
        ++it;
    }

    for (int element = size / 4; element < size / 2; ++element) {
        CHECK(element == list.popFront());
    }
}


TEST_CASE("all_elements") {
    lab618::CSingleLinkedList<int> list;
    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    lab618::CSingleLinkedList<int>::CIterator it = list.begin();
    for (int element = 0; it.isValid(); ++it, ++element) {
        CHECK(element == *it);
        list.erase(it);
    }
}


TEST_CASE("clear") {
    lab618::CSingleLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushFront(element);
    }
    list.clear();
    CHECK(list.getSize() == 0);
}


