#include "mmwdeque.h"
#include "UnitTest++/UnitTest++.h"

SUITE(MmwDequeTest)
{
    TEST(BackQueue)
    {
        mmw::Deque<int> d;

        CHECK(d.is_empty());

        for(int i=0; i<400; i++)
        {
            d.push_back(i);
        }

        CHECK(!d.is_empty());

        CHECK_EQUAL(399, d.back());
        CHECK_EQUAL(0, d.front());
        CHECK_EQUAL(100, d.at(100));
        CHECK_EQUAL(200, d.at(200));
        CHECK_EQUAL(300, d.at(300));
        CHECK_EQUAL(400, d.size());

        d.clear();

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }

    TEST(FrontQueue)
    {
        mmw::Deque<int> d;

        CHECK(d.is_empty());

        for(int i=0; i<400; i++)
        {
            d.push_front(i);
        }

        CHECK(!d.is_empty());

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

        CHECK(d.is_empty());

        for(int i=0; i<300; i++)
        {
            d.push_front(i);
        }

        for(int i=300; i<600; i++)
        {
            d.push_back(i);
        }

        CHECK(!d.is_empty());

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

        CHECK(d.is_empty());

        for(int i=0; i<600; i++)
        {
            d.push_back(i);
        }

        CHECK(!d.is_empty());

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

        for(int i=0; i<597; i++)
        {
            d.pop_back();
        }

        CHECK_EQUAL(0, d.size());
        CHECK(d.is_empty());
    }
}

int main(int argc, char** argv)
{
    return UnitTest::RunAllTests();
}
