#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "mm.h"
#include "doctest.h"

struct Test {
    std::string str;
    int number;
    Test() {
        number = 0;
        str = "Test Memory Manager";
    }
};


TEST_CASE("one_block") {
    lab618::CMemoryManager<Test> mm(10, true);
    Test* obj = mm.newObject();
    std::string str = "Test Memory Manager";
    CHECK((obj->str).compare(str) == 0);
    CHECK(mm.deleteObject(obj) == true);
}


TEST_CASE("two_blocks") {
    lab618::CMemoryManager<Test> mm(3, false);
    Test* obj1 = mm.newObject();
    Test* obj2 = mm.newObject();
    CHECK(obj1 != obj2);
    Test* obj3 = mm.newObject();
    CHECK(obj2 != obj3);
    Test* obj4 = mm.newObject();
    CHECK(obj3 != obj4);
    mm.deleteObject(obj1);
    mm.deleteObject(obj2);
    mm.deleteObject(obj3);
    CHECK(mm.deleteObject(obj4) == true);
}
