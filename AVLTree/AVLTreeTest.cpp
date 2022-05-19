#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "avltree.h"
#include "doctest.h"

int Compare(const int* first, const int* second) {
    return first - second;
}

void GenerateInts(int* ints, const int& quantity, const int& size) {
    for (int i = 0; i < quantity; i++) {
        ints[i] = rand() % size;
    }
}

TEST_CASE("tree") {
    lab618::CAVLTree<int, &Compare> tree_{};

    int* ints = new int[100];

    // маленький тест на паре значений(в основном для проверки remove)
    for (int i = 0; i < 3; i++) {
        ints[i] = i;
        CHECK(tree_.add(ints + i) == true);
        CHECK(tree_.add(ints + i) == false);
    }
    CHECK(tree_.remove(ints[0]) == true);
    CHECK(tree_.find(ints[1]) != nullptr);
    CHECK(tree_.find(ints[2]) != nullptr);
    CHECK(tree_.remove(ints[1]) == true);
    CHECK(tree_.find(ints[2]) != nullptr);
    CHECK(tree_.remove(ints[2]) == true);
    CHECK(tree_.remove(ints[2]) == false);
    // другой порядок удаления вершин
    for (int i = 0; i < 3; i++) {
        ints[i] = i;
        CHECK(tree_.add(ints + i) == true);
        CHECK(tree_.add(ints + i) == false);
    }
    CHECK(tree_.remove(ints[1]) == true);
    CHECK(tree_.find(ints[0]) != nullptr);
    CHECK(tree_.find(ints[2]) != nullptr);
    CHECK(tree_.remove(ints[0]) == true);
    CHECK(tree_.find(ints[2]) != nullptr);
    CHECK(tree_.remove(ints[2]) == true);
    CHECK(tree_.remove(ints[2]) == false);
    // проверка малого левого вращения
    for (int i = 0; i < 6; i++) {
        ints[i] = i;
        CHECK(tree_.add(ints + i) == true);
        CHECK(tree_.add(ints + i) == false);
    }
    tree_.clear();
    // проверка большого левого вращения
    CHECK(tree_.add(ints) == true);
    CHECK(tree_.add(ints + 1) == true);
    CHECK(tree_.add(ints + 4) == true);
    CHECK(tree_.add(ints + 3) == true);
    CHECK(tree_.add(ints + 5) == true);
    CHECK(tree_.add(ints + 2) == true);
    tree_.clear();
    // проверка малого правого вращения
    CHECK(tree_.add(ints + 4) == true);
    CHECK(tree_.add(ints + 5) == true);
    CHECK(tree_.add(ints + 2) == true);
    CHECK(tree_.add(ints + 3) == true);
    CHECK(tree_.add(ints + 1) == true);
    CHECK(tree_.add(ints + 0) == true);
    tree_.clear();
    // проверка большого правого вращения
    CHECK(tree_.add(ints + 4) == true);
    CHECK(tree_.add(ints + 5) == true);
    CHECK(tree_.add(ints + 1) == true);
    CHECK(tree_.add(ints + 0) == true);
    CHECK(tree_.add(ints + 3) == true);
    CHECK(tree_.add(ints + 2) == true);
    tree_.clear();
    // средний тест на весь функционал
    for (int i = 0; i < 15; i++) {
        ints[i] = i;
        CHECK(tree_.add(ints + i) == true);  // создаем дерево
        CHECK(tree_.add(ints + i) == false); // проверяем, что элементы действительно добавляются
    }
    ints[15] = 15;
    // проверка update
    CHECK(tree_.update(ints) == true);
    CHECK(tree_.update(ints + 15) == false);
    // проверка find
    ints[16] = 16;
    CHECK(tree_.find(ints[0]) != nullptr);
    CHECK(tree_.find(ints[16]) == nullptr);
    // проверка remove
    CHECK(tree_.remove(ints[15]) == true);
    CHECK(tree_.find(ints[15]) == nullptr);
    for (int i = 0; i < 15; i++) {
        CHECK(tree_.find(ints[i]) != nullptr);
    }
    CHECK(tree_.remove(ints[7]) == true); // удаляю корень
    CHECK(tree_.find(ints[7]) == nullptr);
    for (int i = 0; i != 7 && i < 15; i++) {
        CHECK(tree_.find(ints[i]) != nullptr);
    }
    tree_.clear();
    CHECK(tree_.find(ints[1]) == nullptr);

    // рандомный тест
    GenerateInts(ints, 98, 1000);
    for (int i = 0; i < 98; i++) {
        ints[i] = i;
        CHECK(tree_.add(ints + i) == true);  // создаем дерево
        CHECK(tree_.add(ints + i) == false); // проверяем, что элементы действительно добавляются
    }
    ints[98] = rand() % 1000;
    // проверка update
    CHECK(tree_.update(ints) == true);
    CHECK(tree_.update(ints + 98) == false);
    // проверка find
    ints[99] = rand() % 1000;
    CHECK(tree_.find(ints[0]) != nullptr);
    CHECK(tree_.find(ints[99]) == nullptr);
    CHECK(tree_.add(ints + 99) == true);
    CHECK(tree_.add(ints + 99) == false);
    // проверка remove
    CHECK(tree_.remove(ints[50]) == true);
    CHECK(tree_.find(ints[50]) == nullptr);
    for (int i = 0; i != 50 && i < 100; i++) {
        CHECK(tree_.find(ints[i]) != nullptr);
    }
    tree_.clear();
    CHECK(tree_.find(ints[1]) == nullptr);
}
