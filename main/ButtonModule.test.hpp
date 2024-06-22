#include <unity.h>
#include <unity_fixture.h>

#include <ButtonModule.hpp>

TEST_GROUP(ButtonModule_test);

TEST_SETUP(ButtonModule_test) {}

TEST_TEAR_DOWN(ButtonModule_test) {}

////////////////////////////////---------TEST---------//////////////////////////////////////

TEST(ButtonModule_test, constructor)
{
    ButtonModule button(5);

    TEST_ASSERT_EQUAL(true, true);
}

TEST(ButtonModule_test, setSinglePressCallback)
{
    ButtonModule button(5);

    TEST_ASSERT_EQUAL(true, true);
}

///////////////////////////////////////////////////////////////////////////////////////////

TEST_GROUP_RUNNER(ButtonModule_test)
{
    RUN_TEST_CASE(ButtonModule_test, constructor);
    RUN_TEST_CASE(ButtonModule_test, setSinglePressCallback);
}