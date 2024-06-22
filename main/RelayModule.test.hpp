#include <unity.h>
#include <unity_fixture.h>

#include <RelayModule.hpp>

TEST_GROUP(RelayModule_test);

TEST_SETUP(RelayModule_test) {}

TEST_TEAR_DOWN(RelayModule_test) {}

////////////////////////////////---------TEST---------//////////////////////////////////////

TEST(RelayModule_test, constructor)
{
    RelayModule relay(GPIO_NUM_2, 1, 1);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 1);

    RelayModule relay2(GPIO_NUM_2, 1, 0);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 0);

    RelayModule relay3(GPIO_NUM_2, 0, 1);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 0);

    RelayModule relay4(GPIO_NUM_2, 0, 0);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 1);
}

TEST(RelayModule_test, setPower)
{
    RelayModule relay(GPIO_NUM_2, 1, 1);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);

    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 1);

    relay.setPower(false);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 0);
    relay.setPower(false);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 0);

    relay.setPower(true);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 1);
    relay.setPower(true);
    TEST_ASSERT_EQUAL(gpio_get_level(GPIO_NUM_2), 1);
}

TEST(RelayModule_test, isOn)
{
    RelayModule relay(GPIO_NUM_2, 1, 1);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_INPUT_OUTPUT);

    TEST_ASSERT_EQUAL(relay.isOn(), true);

    gpio_set_level(GPIO_NUM_2, 0);
    TEST_ASSERT_EQUAL(relay.isOn(), false);
}

///////////////////////////////////////////////////////////////////////////////////////////

TEST_GROUP_RUNNER(RelayModule_test)
{
    RUN_TEST_CASE(RelayModule_test, constructor);
    RUN_TEST_CASE(RelayModule_test, setPower);
    RUN_TEST_CASE(RelayModule_test, isOn);
}