#pragma once

/**
 * @brief Interface for a relay module.
 *
 * This interface defines the basic operations for controlling a relay module.
 */
class RelayModuleInterface
{
public:
    /**
     * @brief Virtual destructor for the interface.
     */
    virtual ~RelayModuleInterface() = default;

    /**
     * @brief Set the relay power state.
     *
     * @param newState True to turn the relay on, false to turn it off.
     */
    virtual void setPower(bool newState) = 0;

    /**
     * @brief Check if the relay is currently on.
     *
     * @return True if the relay is on, false otherwise.
     */
    virtual bool isOn() = 0;
};
