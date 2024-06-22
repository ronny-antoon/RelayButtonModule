#include "RelayModule.hpp"

#include <driver/gpio.h>
#include <esp_log.h>

static const char * TAG = "RelayModule";

RelayModule::RelayModule(int8_t relayPin, int8_t activeLevel, int8_t initialState) :
    m_relayPin(static_cast<gpio_num_t>(relayPin)), m_activeLevel(activeLevel)
{
    ESP_LOGI(TAG, "Initializing RelayModule with pin: %d, active level: %d, initial state: %d", relayPin, activeLevel,
             initialState);

    if (relayPin < 0)
    {
        ESP_LOGE(TAG, "Invalid relay pin number: %d", relayPin);
        return;
    }

    gpio_set_direction(m_relayPin, GPIO_MODE_INPUT_OUTPUT);

    if (initialState == 0)
    {
        gpio_set_level(m_relayPin, !m_activeLevel);
        ESP_LOGD(TAG, "Relay initialized to OFF state.");
    }
    else if (initialState == 1)
    {
        gpio_set_level(m_relayPin, m_activeLevel);
        ESP_LOGD(TAG, "Relay initialized to ON state.");
    }
    else
    {
        ESP_LOGW(TAG, "Initial state not set: %d", initialState);
    }
}

RelayModule::~RelayModule()
{
    ESP_LOGI(TAG, "Deinitializing RelayModule with pin: %d", m_relayPin);
}

void RelayModule::setPower(bool newState)
{
    ESP_LOGD(TAG, "Setting relay power state to: %s", newState ? "ON" : "OFF");

    if (gpio_set_level(m_relayPin, newState ? m_activeLevel : !m_activeLevel) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to set relay state to: %s", newState ? "ON" : "OFF");
        return;
    }
}

bool RelayModule::isOn()
{
    bool currState = (gpio_get_level(m_relayPin) == m_activeLevel);
    ESP_LOGI(TAG, "Checking if relay is on: %s", currState ? "YES" : "NO");
    return currState;
}
