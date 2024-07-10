#pragma once

#include <ButtonModule.hpp>
#include <esp_heap_trace.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <unity.h>
#include <unity_fixture.h>

#ifndef BEGIN_MEMORY_LEAK_TEST
#define BEGIN_MEMORY_LEAK_TEST(trace_record)                                                                                       \
    do                                                                                                                             \
    {                                                                                                                              \
        heap_trace_stop();                                                                                                         \
        ESP_ERROR_CHECK(heap_trace_init_standalone(trace_record, sizeof(trace_record) / sizeof(trace_record[0])));                 \
        ESP_ERROR_CHECK(heap_trace_start(HEAP_TRACE_LEAKS));                                                                       \
    } while (0)
#endif

#ifndef END_MEMORY_LEAK_TEST
#define END_MEMORY_LEAK_TEST(trace_record)                                                                                         \
    do                                                                                                                             \
    {                                                                                                                              \
        ESP_ERROR_CHECK(heap_trace_stop());                                                                                        \
        if (trace_record[0].size != 0)                                                                                             \
        {                                                                                                                          \
            heap_trace_dump();                                                                                                     \
            TEST_FAIL_MESSAGE("Memory leak detected!");                                                                            \
        }                                                                                                                          \
    } while (0)
#endif

void singlePressCallback(void * param)
{
    bool * flag = static_cast<bool *>(param);
    *flag       = true;
}

void doublePressCallback(void * param)
{
    bool * flag = static_cast<bool *>(param);
    *flag       = true;
}

void longPressCallback(void * param)
{
    bool * flag = static_cast<bool *>(param);
    *flag       = true;
}

TEST_CASE("Constructor Test1", "[ButtonModule] [Constructor]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {

        ButtonModule button1(27, 1, 2000, 50);
        ButtonModule button2(14, 0, 3000, 60);
        ButtonModule * buttonPtr = new ButtonModule(27, 1, 2000, 50);
        delete buttonPtr;
        TEST_ASSERT_EQUAL(true, true);

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("Single Press Callback Test", "[ButtonModule] [SinglePress]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {

        ButtonModule button(5, 1, 2000, 50);
        bool singlePressDetected = false;

        button.setSinglePressCallback(singlePressCallback, &singlePressDetected);
        // Simulate single press event (needs appropriate mocking or hardware simulation)
        gpio_set_direction((gpio_num_t) 5, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(singlePressDetected);

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("Double Press Callback Test", "[ButtonModule] [DoublePress]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {

        ButtonModule button(5, 1, 2000, 50);
        bool doublePressDetected = false;

        button.setDoublePressCallback(doublePressCallback, &doublePressDetected);
        // Simulate double press event (needs appropriate mocking or hardware simulation)
        gpio_set_direction((gpio_num_t) 5, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(20 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(doublePressDetected);

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
    ESP_LOGI("Test", "------------------------------------------------------------------------");
}

TEST_CASE("Long Press Callback Test", "[ButtonModule] [LongPress]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {
        ButtonModule button(5, 1, 2000, 50);
        bool longPressDetected = false;

        button.setLongPressCallback(longPressCallback, &longPressDetected);
        // Simulate long press event (needs appropriate mocking or hardware simulation)
        gpio_set_direction((gpio_num_t) 5, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(2100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(longPressDetected);

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("Single Press Callback Test onHeap", "[ButtonModule] [SinglePress] [Heap]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {

        ButtonModule * button    = new ButtonModule(5, 1, 2000, 50);
        bool singlePressDetected = false;

        button->setSinglePressCallback(singlePressCallback, &singlePressDetected);
        // Simulate single press event (needs appropriate mocking or hardware simulation)
        gpio_set_direction((gpio_num_t) 5, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(singlePressDetected);
        delete button;

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("Double Press Callback Test onHeap", "[ButtonModule] [DoublePress] [Heap]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {

        ButtonModule * button    = new ButtonModule(5, 1, 2000, 50);
        bool doublePressDetected = false;

        button->setDoublePressCallback(doublePressCallback, &doublePressDetected);
        // Simulate double press event (needs appropriate mocking or hardware simulation)
        gpio_set_direction((gpio_num_t) 5, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(20 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(doublePressDetected);
        delete button;

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("Long Press Callback Test onHeap", "[ButtonModule] [LongPress] [Heap]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {
        ButtonModule * button  = new ButtonModule(5, 1, 2000, 50);
        bool longPressDetected = false;

        button->setLongPressCallback(longPressCallback, &longPressDetected);
        // Simulate long press event (needs appropriate mocking or hardware simulation)
        gpio_set_direction((gpio_num_t) 5, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(2100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(longPressDetected);
        delete button;

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("All press event type", "[ButtonModule] [SinglePress] [DoublePress] [LongPress] [Heap]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {
        ButtonModule * button    = new ButtonModule(5, 1, 2000, 50);
        bool singlePressDetected = false;
        bool doublePressDetected = false;
        bool longPressDetected   = false;

        button->setSinglePressCallback(singlePressCallback, &singlePressDetected);
        button->setDoublePressCallback(doublePressCallback, &doublePressDetected);
        button->setLongPressCallback(longPressCallback, &longPressDetected);

        // Simulate single press event (needs appropriate mocking or hardware simulation)
        gpio_set_direction((gpio_num_t) 5, GPIO_MODE_INPUT_OUTPUT);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(200 / portTICK_PERIOD_MS);

        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(singlePressDetected);

        // Simulate double press event (needs appropriate mocking or hardware simulation)
        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);
        vTaskDelay(20 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(doublePressDetected);

        // Simulate long press event (needs appropriate mocking or hardware simulation)
        gpio_set_level((gpio_num_t) 5, 1);
        vTaskDelay(2100 / portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 5, 0);

        vTaskDelay(200 / portTICK_PERIOD_MS);
        TEST_ASSERT_TRUE(longPressDetected);

        delete button;

    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}