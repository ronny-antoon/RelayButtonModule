#include "ButtonModule.test.hpp"
// #include "RelayModule.test.hpp"

// #include <unity.h>
// #include <unity_fixture.h>

extern "C" void app_main()
{
    esp_log_level_set("ButtonModule", ESP_LOG_VERBOSE);
    UNITY_BEGIN();
    unity_run_all_tests();
    UNITY_END();
}
