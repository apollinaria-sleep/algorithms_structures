#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "list.h"
#include "doctest.h"
#include <iostream>


TEST_CASE("size") {
    lab618::CDualLinkedList<int> list;
    CHECK(list.getSize() == 0);

}


TEST_CASE("push back") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }
    CHECK(list.getSize() == size);
}


TEST_CASE("pop back") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    for (int element = size - 1; element >= 0; --element) {
        CHECK(element == list.popBack());
    }
    CHECK(list.getSize() == 0);
}


TEST_CASE("push front") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushFront(element);
    }
    CHECK(list.getSize() == size);
    for (int element = 0; element < size; ++element) {
        CHECK(element == list.popBack());
    }
}


TEST_CASE("pop front") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    for (int element = 0; element < size; ++element) {
        CHECK(element == list.popFront());
    }
    CHECK(list.getSize() == 0);
}


TEST_CASE("erase") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;
    size = size % 2 ? (size + 1) : size;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    lab618::CDualLinkedList<int>::CIterator it = list.begin();
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


TEST_CASE("eraseAndNext") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;
    size = size % 2 ? (size + 1) : size;
    for (int element = 0; element < size; ++element) {
        list.pushFront(element);
    }

    lab618::CDualLinkedList<int>::CIterator it = list.end();
    for (int i = 0; i < size / 2; ++i) {
        --it;
    }
    while (it.isValid()) {
        list.eraseAndNext(it);
        --it;
    }

    it = list.end();
    for (int element = 0; element < size / 4; ++element) {
        CHECK(element == *it);
        list.eraseAndNext(it);
        --it;
    }

    for (int element = size / 4; element < size / 2; ++element) {
        CHECK(element == list.popBack());
    }
}


TEST_CASE("all_elements") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;;
    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    lab618::CDualLinkedList<int>::CIterator it_b = list.begin();
    for (int element = 0; it_b.isValid(); ++it_b, ++element) {
        CHECK(element == *it_b);
        list.erase(it_b);
    }

    for (int element = 0; element < size; ++element) {
        list.pushBack(element);
    }

    lab618::CDualLinkedList<int>::CIterator it_e = list.end();
    for (int element = size - 1; it_e.isValid(); --it_e, --element) {
        CHECK(element == *it_e);
        list.eraseAndNext(it_e);
    }
}


TEST_CASE("clear") {
    lab618::CDualLinkedList<int> list;

    int size = rand() % 1000;
    for (int element = 0; element < size; ++element) {
        list.pushFront(element);
    }
    list.clear();
    CHECK(list.getSize() == 0);
}

