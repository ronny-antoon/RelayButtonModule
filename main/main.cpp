extern "C" {
#include <driver/gpio.h>

#define UNITY_INCLUDE_EXEC_TIME
#include <unity.h>
#include <unity_fixture.h>

#include <ButtonModule.hpp>
#include <RelayModule.hpp>

TEST_CASE("RelayModule1", "[RelayModule5]")
{
    RelayModule relay(GPIO_NUM_2, 1, 0);
    relay.setPower(true);
    TEST_ASSERT(relay.isOn() == false);
}

void app_main()
{
    UNITY_BEGIN();

    unity_run_all_tests();

    UNITY_END();
}
} // extern "C"