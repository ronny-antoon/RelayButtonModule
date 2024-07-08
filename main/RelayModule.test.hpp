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

TEST_CASE("Constructor Test", "[RelayModule] [Constructor]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);

    RelayModule relay1(27, 1, 1);
    RelayModule relay2(14, 0, 1);
    RelayModule relay3(23, 1, 0);
    RelayModule relay4(33, 0, 0);
    RelayModule * relayPtr = new RelayModule(27, 1, 1);
    delete relayPtr;

    TEST_ASSERT_EQUAL(true, true);

    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("setPower Test", "[RelayModule] [setPower]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);

    RelayModule relay(27, 1, 0);

    relay.setPower(true);
    TEST_ASSERT_TRUE(relay.isOn());

    relay.setPower(false);
    TEST_ASSERT_FALSE(relay.isOn());

    RelayModule * relayPtr = new RelayModule(5, 1, 1);
    relayPtr->setPower(true);
    relayPtr->setPower(false);
    delete relayPtr;

    END_MEMORY_LEAK_TEST(trace_record);
}

TEST_CASE("isOn Test", "[RelayModule] [isOn]")
{
    heap_trace_record_t trace_record[10];
    BEGIN_MEMORY_LEAK_TEST(trace_record);

    RelayModule relay(27, 1, 0);

    relay.setPower(true);
    TEST_ASSERT_TRUE(relay.isOn());

    relay.setPower(false);
    TEST_ASSERT_FALSE(relay.isOn());

    RelayModule * relayPtr = new RelayModule(5, 1, 1);
    relayPtr->setPower(true);
    TEST_ASSERT_TRUE(relayPtr->isOn());
    relayPtr->setPower(false);
    TEST_ASSERT_FALSE(relayPtr->isOn());
    delete relayPtr;

    END_MEMORY_LEAK_TEST(trace_record);
}
