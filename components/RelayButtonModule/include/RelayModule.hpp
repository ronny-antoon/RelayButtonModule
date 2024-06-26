#pragma once

#include "RelayModuleInterface.hpp"
#include <driver/gpio.h>

/**
 * @brief Implementation of a relay module.
 *
 * This class provides the implementation for controlling a relay module using a GPIO pin.
 */
class RelayModule : public RelayModuleInterface
{
public:
    /**
     * @brief Construct a new Relay Module object.
     *
     * @param pin The GPIO pin number connected to the relay.
     * @param isActiveHigh The active level of the relay (1 for active high, 0 for active low).
     * @param initialRelayState The initial state of the relay (1 for on, 0 for off, -1 for no change).
     */
    RelayModule(int8_t pin = -1, int8_t isActiveHigh = CONFIG_R_B_M_ACTIVE_HIGH, int8_t initialRelayState = -1);

    /**
     * @brief Destroy the Relay Module object.
     */
    virtual ~RelayModule();

    /**
     * @brief Set the relay power state.
     *
     * @param newState True to turn the relay on, false to turn it off.
     */
    void setPower(bool newState) override;

    /**
     * @brief Check if the relay is currently on.
     *
     * @return True if the relay is on, false otherwise.
     */
    bool isOn() override;

private:
    gpio_num_t m_pin;      ///< The GPIO pin number connected to the relay.
    int8_t m_isActiveHigh; ///< The active level of the relay (1 for active high, 0 for active low).

    // delete the copy constructor and the assignment operator
    RelayModule(const RelayModule &)             = delete;
    RelayModule & operator=(const RelayModule &) = delete;

    // Helper method for initialization
    void initializeRelay(int8_t initialRelayState);
};
