#pragma once

#include <RelayModule.hpp>
#include <esp_heap_trace.h>
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

TEST_CASE("RelayModule Constructor Test", "[RelayModule] [Constructor]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {
        RelayModule relayModule(GPIO_NUM_0);
        TEST_ASSERT_EQUAL(GPIO_NUM_0, relayModule.getGpio());
        TEST_ASSERT_EQUAL(0, relayModule.getLevel());
    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("RelayModule Constructor Test on heap", "[RelayModule] [Constructor] [Heap]")
{
}

TEST_CASE("RelayModule setPower Test", "[RelayModule] [setPower]")
{
}

TEST_CASE("RelayModule setPower Test on heap", "[RelayModule] [setPower] [Heap]")
{
}

TEST_CASE("RelayModule isOn Test", "[RelayModule] [isOn]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {
        RelayModule relayModule(GPIO_NUM_0);
        TEST_ASSERT_FALSE(relayModule.isOn());
        relayModule.setPower(true);
        TEST_ASSERT_TRUE(relayModule.isOn());
        relayModule.setPower(false);
        TEST_ASSERT_FALSE(relayModule.isOn());
    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("RelayModule isOn Test on heap", "[RelayModule] [isOn] [Heap]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {
        RelayModule * relayModule = new RelayModule(GPIO_NUM_0);
        TEST_ASSERT_FALSE(relayModule->isOn());
        relayModule->setPower(true);
        TEST_ASSERT_TRUE(relayModule->isOn());
        relayModule->setPower(false);
        TEST_ASSERT_FALSE(relayModule->isOn());
        delete relayModule;
    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("RelayModule setPower Test on heap", "[RelayModule] [setPower] [isOn] [Heap]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);
    do
    {
        RelayModule * relayModule = new RelayModule(GPIO_NUM_0);
        TEST_ASSERT_FALSE(relayModule->isOn());
        relayModule->setPower(true);
        TEST_ASSERT_TRUE(relayModule->isOn());
        relayModule->setPower(false);
        TEST_ASSERT_FALSE(relayModule->isOn());
        delete relayModule;
    } while (0);
    END_MEMORY_LEAK_TEST(trace_record);
}