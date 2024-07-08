#include "ButtonModule.hpp"

#include <esp_log.h>

static const char * TAG = "ButtonModule";

ButtonModule::ButtonModule(int8_t pin, uint8_t isActiveHigh, uint16_t longPressDurationMs, uint16_t debounceTimeMs):
    m_singlePressCallback(nullptr),
    m_doublePressCallback(nullptr),
    m_longPressCallback(nullptr),
    m_singlePressCallbackParam(nullptr),
    m_doublePressCallbackParam(nullptr),
    m_longPressCallbackParam(nullptr),
    m_buttonHandle(nullptr)
{
    ESP_LOGI(TAG, "Initializing ButtonModule with pin: %d, active level: %d, long press duration: %d ms, debounce time: %d ms", pin,
             isActiveHigh, longPressDurationMs, debounceTimeMs);

    if (pin <= 0)
    {
        ESP_LOGE(TAG, "Invalid button pin number: %d", pin);
        return;
    }

    gpio_reset_pin(static_cast<gpio_num_t>(pin));

    gpio_set_direction(static_cast<gpio_num_t>(pin), GPIO_MODE_INPUT);

    button_config_t buttonConfig = { .type               = BUTTON_TYPE_GPIO,
                                     .long_press_time    = longPressDurationMs,
                                     .short_press_time   = debounceTimeMs,
                                     .gpio_button_config = {
                                         .gpio_num     = pin,
                                         .active_level = isActiveHigh,
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
    ESP_LOGI(TAG, "Deinitializing ButtonModule");
    if (m_buttonHandle != nullptr)
    {
        iot_button_delete(m_buttonHandle);
        ESP_LOGI(TAG, "Button handle deleted");
    }
}

void ButtonModule::setSinglePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter)
{
    ESP_LOGI(TAG, "Setting single press callback");

    m_singlePressCallback      = callback;
    m_singlePressCallbackParam = callbackParameter;

    registerSinglePressCallback();
}

void ButtonModule::setDoublePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter)
{
    ESP_LOGI(TAG, "Setting double press callback");

    m_doublePressCallback      = callback;
    m_doublePressCallbackParam = callbackParameter;

    registerDoublePressCallback();
}

void ButtonModule::setLongPressCallback(CallbackButtonFunction callback, AnyType * callbackParameter)
{
    ESP_LOGI(TAG, "Setting long press callback");

    m_longPressCallback      = callback;
    m_longPressCallbackParam = callbackParameter;

    registerLongPressCallback();
}

void ButtonModule::registerSinglePressCallback()
{
    if(m_buttonHandle == nullptr)
    {
        ESP_LOGE(TAG, "Button handle is null");
        return;
    }
    
    iot_button_register_cb(
        m_buttonHandle, BUTTON_SINGLE_CLICK,
        [](void * buttonHandle, void * thisPtr) {
            ESP_LOGD(TAG, "Single press detected");
            ButtonModule * buttonModule = static_cast<ButtonModule *>(thisPtr);
            if (buttonModule && buttonModule->m_singlePressCallback)
            {
                buttonModule->m_singlePressCallback(buttonModule->m_singlePressCallbackParam);
            }
        },
        this);
}

void ButtonModule::registerDoublePressCallback()
{
    if(m_buttonHandle == nullptr)
    {
        ESP_LOGE(TAG, "Button handle is null");
        return;
    }

    iot_button_register_cb(
        m_buttonHandle, BUTTON_DOUBLE_CLICK,
        [](void * buttonHandle, void * thisPtr) {
            ESP_LOGD(TAG, "Double press detected");
            ButtonModule * buttonModule = static_cast<ButtonModule *>(thisPtr);
            if (buttonModule && buttonModule->m_doublePressCallback)
            {
                buttonModule->m_doublePressCallback(buttonModule->m_doublePressCallbackParam);
            }
        },
        this);
}

void ButtonModule::registerLongPressCallback()
{
    if(m_buttonHandle == nullptr)
    {
        ESP_LOGE(TAG, "Button handle is null");
        return;
    }

    iot_button_register_cb(
        m_buttonHandle, BUTTON_LONG_PRESS_START,
        [](void * buttonHandle, void * thisPtr) {
            ESP_LOGD(TAG, "Long press detected");
            ButtonModule * buttonModule = static_cast<ButtonModule *>(thisPtr);
            if (buttonModule && buttonModule->m_longPressCallback)
            {
                buttonModule->m_longPressCallback(buttonModule->m_longPressCallbackParam);
            }
        },
        this);
}
