// #include <unity.h>
// #include <unity_fixture.h>
#include "ButtonModule.test.hpp"
#include "RelayModule.test.hpp"
#include <esp_log.h>

extern "C" void app_main()
{
    // UNITY_BEGIN();

    // RUN_TEST_GROUP(ButtonModule_test);
    // RUN_TEST_GROUP(RelayModule_test);

    // UNITY_END();

    ButtonModule * button = new ButtonModule(5,1,1000,200);
    button->setSinglePressCallback([](void * param) { ESP_LOGI("Button", "Single press callback"); }, nullptr);

    button->setDoublePressCallback([](void * param) { ESP_LOGI("Button", "Double press callback"); }, nullptr);

    button->setLongPressCallback([](void * param) { ESP_LOGI("Button", "Long press callback"); }, nullptr);
}
