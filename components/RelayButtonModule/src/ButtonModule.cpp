#include "ButtonModule.hpp"

#include <esp_log.h>

static const char * TAG = "ButtonModule";

ButtonModule::ButtonModule(int8_t buttonPin, uint8_t activeLevel, uint16_t longPressTimeMs, uint16_t shortPressTimeMs)
{
    ESP_LOGI(TAG, "Initializing ButtonModule with pin: %d, active level: %d, long press time: %d ms, short press time: %d ms",
             buttonPin, activeLevel, longPressTimeMs, shortPressTimeMs);

    if (buttonPin < 0)
    {
        ESP_LOGE(TAG, "Invalid button pin number: %d", buttonPin);
        return;
    }

    gpio_set_direction((gpio_num_t) buttonPin, GPIO_MODE_INPUT);

    button_config_t buttonConfig = { .type               = BUTTON_TYPE_GPIO,
                                     .long_press_time    = longPressTimeMs,
                                     .short_press_time   = shortPressTimeMs,
                                     .gpio_button_config = {
                                         .gpio_num     = buttonPin,
                                         .active_level = activeLevel,
                                     } };

    m_buttonHandle = iot_button_create(&buttonConfig);

    if (m_buttonHandle == nullptr)
    {
        ESP_LOGE(TAG, "Failed to create button handle");
    }
    else
    {
        ESP_LOGI(TAG, "Button handle created successfully");
    }
}

ButtonModule::~ButtonModule()
{
    ESP_LOGI(TAG, "Destroying ButtonModule");
    if (m_buttonHandle != nullptr)
    {
        iot_button_delete(m_buttonHandle);
        ESP_LOGI(TAG, "Button handle deleted");
    }
}

void ButtonModule::setSinglePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter)
{
    ESP_LOGI(TAG, "Setting single press callback");

    m_singlePressCallback          = callback;
    m_singlePressCallbackParameter = callbackParameter;

    iot_button_register_cb(
        m_buttonHandle, BUTTON_SINGLE_CLICK,
        [](void * buttonHandle, void * thisPtr) {
            ESP_LOGD(TAG, "Single press detected");
            ButtonModule * buttonModule = static_cast<ButtonModule *>(thisPtr);
            if (buttonModule->m_singlePressCallback)
            {
                buttonModule->m_singlePressCallback(buttonModule->m_singlePressCallbackParameter);
            }
        },
        this);
}

void ButtonModule::setDoublePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter)
{
    ESP_LOGI(TAG, "Setting double press callback");

    m_doublePressCallback          = callback;
    m_doublePressCallbackParameter = callbackParameter;

    iot_button_register_cb(
        m_buttonHandle, BUTTON_DOUBLE_CLICK,
        [](void * buttonHandle, void * thisPtr) {
            ESP_LOGD(TAG, "Double press detected");
            ButtonModule * buttonModule = static_cast<ButtonModule *>(thisPtr);
            if (buttonModule->m_doublePressCallback)
            {
                buttonModule->m_doublePressCallback(buttonModule->m_doublePressCallbackParameter);
            }
        },
        this);
}

void ButtonModule::setLongPressCallback(CallbackButtonFunction callback, AnyType * callbackParameter)
{
    ESP_LOGI(TAG, "Setting long press callback");

    m_longPressCallback          = callback;
    m_longPressCallbackParameter = callbackParameter;

    iot_button_register_cb(
        m_buttonHandle, BUTTON_LONG_PRESS_START,
        [](void * buttonHandle, void * thisPtr) {
            ESP_LOGD(TAG, "Long press detected");
            ButtonModule * buttonModule = static_cast<ButtonModule *>(thisPtr);
            if (buttonModule->m_longPressCallback)
            {
                buttonModule->m_longPressCallback(buttonModule->m_longPressCallbackParameter);
            }
        },
        this);
}
