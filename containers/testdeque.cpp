#include "mmwdeque.h"
#include "UnitTest++/UnitTest++.h"

SUITE(MmwDequeTest)
{
    TEST(BackQueue)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        for(int i=0; i<400; i++)
        {
            d.push_back(i);
        }

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(400, d.size());

        CHECK_EQUAL(399, d.back());
        CHECK_EQUAL(0, d.front());
        CHECK_EQUAL(0, d.at(0));
        CHECK_EQUAL(100, d.at(100));
        CHECK_EQUAL(200, d.at(200));
        CHECK_EQUAL(300, d.at(300));
        CHECK_EQUAL(399, d.at(399));
        CHECK_EQUAL(400, d.size());

        d.clear();

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(FrontQueue)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        for(int i=0; i<400; i++)
        {
            d.push_front(i);
        }

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(0, d.back());
        CHECK_EQUAL(399, d.front());
        CHECK_EQUAL(299, d.at(100));
        CHECK_EQUAL(199, d.at(200));
        CHECK_EQUAL(99, d.at(300));
        CHECK_EQUAL(400, d.size());

        d.clear();

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(FrontAndBackQueues)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        for(int i=0; i<300; i++)
        {
            d.push_front(i);
        }

        for(int i=300; i<600; i++)
        {
            d.push_back(i);
        }

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(599, d.back());
        CHECK_EQUAL(299, d.front());
        CHECK_EQUAL(199, d.at(100));
        CHECK_EQUAL(99, d.at(200));
        CHECK_EQUAL(300, d.at(300));
        CHECK_EQUAL(400, d.at(400));
        CHECK_EQUAL(500, d.at(500));
        CHECK_EQUAL(600, d.size());

        d.clear();

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(PopBackQueue)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        for(int i=0; i<600; i++)
        {
            d.push_back(i);
        }

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(599, d.back());
        CHECK_EQUAL(0, d.front());

        d.pop_back();
        CHECK_EQUAL(598, d.back());

        d.pop_back();
        CHECK_EQUAL(597, d.back());

        d.pop_back();
        CHECK_EQUAL(596, d.back());

        d.pop_front();
        CHECK_EQUAL(1, d.front());

        for(int i=0; i<596; i++)
        {
            d.pop_back();
        }

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(PopFrontQueue)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        for(int i=0; i<130; i++)
        {
            d.push_front(i);
        }

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(129, d.front());
        CHECK_EQUAL(0, d.back());

        d.pop_front();
        CHECK_EQUAL(128, d.front());

        d.pop_back();
        CHECK_EQUAL(1, d.back());

        for(int i=0; i<128; i++)
        {
            d.pop_back();
        }

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(SingleFrontElement)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        d.push_front(1);

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(1, d.front());
        CHECK_EQUAL(1, d.back());
        CHECK_EQUAL(1, d.at(0));

        d.pop_front();

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(SingleBackElement)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        d.push_back(1);

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(1, d.front());
        CHECK_EQUAL(1, d.back());
        CHECK_EQUAL(1, d.at(0));

        d.pop_front();

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(RegressTailTowardsHead)
    {
        mmw::Deque<int> d;

        REQUIRE CHECK(d.is_empty());

        for(int i=9; i>=0; i--)
        {
            d.push_front(i);
        }

        for(int i=10; i<20; i++)
        {
            d.push_back(i);
        }

        REQUIRE CHECK(!d.is_empty());

        CHECK_EQUAL(20, d.size());

        CHECK_EQUAL(0, d.front());
        CHECK_EQUAL(19, d.back());

        for(int i=0; i<15; i++)
        {
            d.pop_back();
        }

        CHECK_EQUAL(4, d.back());
    }
}

int main(int argc, char** argv)
{
    return UnitTest::RunAllTests();
}
