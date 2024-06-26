#include "RelayModule.hpp"
#include <driver/gpio.h>
#include <esp_log.h>

static const char * TAG = "RelayModule";

RelayModule::RelayModule(int8_t pin, int8_t isActiveHigh, int8_t initialRelayState) :
    m_pin(static_cast<gpio_num_t>(pin)), m_isActiveHigh(isActiveHigh)
{
    ESP_LOGI(TAG, "Initializing RelayModule with pin: %d, active level: %d, initial state: %d", pin, isActiveHigh,
             initialRelayState);

    if (pin < 0)
    {
        ESP_LOGE(TAG, "Invalid relay pin number: %d", pin);
        return;
    }

    gpio_set_direction(m_pin, GPIO_MODE_INPUT_OUTPUT);

    initializeRelay(initialRelayState);
}

RelayModule::~RelayModule()
{
    ESP_LOGI(TAG, "Deinitializing RelayModule with pin: %d", m_pin);
}

void RelayModule::setPower(bool newState)
{
    ESP_LOGD(TAG, "Setting relay power state to: %s", newState ? "ON" : "OFF");

    if (gpio_set_level(m_pin, newState ? m_isActiveHigh : !m_isActiveHigh) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set relay state to: %s", newState ? "ON" : "OFF");
    }
}

bool RelayModule::isOn()
{
    bool currState = (gpio_get_level(m_pin) == m_isActiveHigh);
    ESP_LOGI(TAG, "Checking if relay is on: %s", currState ? "YES" : "NO");
    return currState;
}

void RelayModule::initializeRelay(int8_t initialRelayState)
{
    if (initialRelayState == 0)
    {
        gpio_set_level(m_pin, !m_isActiveHigh);
        ESP_LOGD(TAG, "Relay initialized to OFF state.");
    }
    else if (initialRelayState == 1)
    {
        gpio_set_level(m_pin, m_isActiveHigh);
        ESP_LOGD(TAG, "Relay initialized to ON state.");
    }
    else
    {
        ESP_LOGW(TAG, "Initial state not set: %d", initialRelayState);
    }
}
