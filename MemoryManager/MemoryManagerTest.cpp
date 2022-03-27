#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "mm.h"
#include "doctest.h"

struct TwoInt {
    int first = 0;
    int second = 1;
    TwoInt() = default;
    TwoInt(int f, int s) : first(f), second(s) {}
};


TEST_CASE("one_block") {
    lab618::CMemoryManager<TwoInt> mm(10, false);
    TwoInt* obj = mm.newObject();
    CHECK(mm.deleteObject(obj) == true);
}


TEST_CASE("two_blocks") {
    lab618::CMemoryManager<TwoInt> mm(3, false);
    TwoInt* obj1 = mm.newObject();
    TwoInt* obj2 = mm.newObject();
    CHECK(obj1 != obj2);
    TwoInt* obj3 = mm.newObject();
    CHECK(obj2 != obj3);
    TwoInt* obj4 = mm.newObject();
    CHECK(obj3 != obj4);
    mm.deleteObject(obj1);
    mm.deleteObject(obj2);
    mm.deleteObject(obj3);
    CHECK(mm.deleteObject(obj4) == true);
}
