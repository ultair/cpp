#include "hashmap.h"
#include "UnitTest++/UnitTest++.h"

SUITE(MmwHashMapTest)
{
    TEST(Sanity)
    {
        mmw::HashMap<std::string, int> hashMap;

        hashMap.insert("hundred", 100);

        int* val = hashMap.find("hundred");

        REQUIRE CHECK(val);

        CHECK_EQUAL(100, *val);

        hashMap.erase("hundred");

        val = hashMap.find("hundred");

        REQUIRE CHECK(!val);
    }
}

int main(int argc, char** argv)
{
    return UnitTest::RunAllTests();
}
