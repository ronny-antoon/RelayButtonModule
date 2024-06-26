#pragma once

#include "ButtonModuleInterface.hpp"
#include <iot_button.h>

/**
 * @brief Implementation of a button module.
 *
 * This class provides the implementation for handling button events using a GPIO pin.
 */
class ButtonModule : public ButtonModuleInterface
{
public:
    /**
     * @brief Construct a new Button Module object.
     *
     * @param pin The GPIO pin number connected to the button.
     * @param isActiveHigh The active level of the button (1 for active high, 0 for active low).
     * @param longPressDurationMs The time in milliseconds to consider a press as a long press.
     * @param debounceTimeMs The time in milliseconds to consider a press as a short press.
     */
    ButtonModule(int8_t pin = -1, uint8_t isActiveHigh = CONFIG_R_B_M_ACTIVE_HIGH,
                 uint16_t longPressDurationMs = CONFIG_R_B_M_LONG_PRESS_TIME, uint16_t debounceTimeMs = CONFIG_R_B_M_DEBOUNCE_TIME);

    /**
     * @brief Destroy the Button Module object.
     */
    virtual ~ButtonModule();

    /**
     * @brief Set the callback function for single press events.
     *
     * @param callback The callback function to be called on single press.
     * @param callbackParameter Optional parameter to be passed to the callback function.
     */
    void setSinglePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter = nullptr) override;

    /**
     * @brief Set the callback function for double press events.
     *
     * @param callback The callback function to be called on double press.
     * @param callbackParameter Optional parameter to be passed to the callback function.
     */
    void setDoublePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter = nullptr) override;

    /**
     * @brief Set the callback function for long press events.
     *
     * @param callback The callback function to be called on long press.
     * @param callbackParameter Optional parameter to be passed to the callback function.
     */
    void setLongPressCallback(CallbackButtonFunction callback, AnyType * callbackParameter = nullptr) override;

private:
    CallbackButtonFunction m_singlePressCallback; ///< Callback for single press.
    CallbackButtonFunction m_doublePressCallback; ///< Callback for double press.
    CallbackButtonFunction m_longPressCallback;   ///< Callback for long press.
    AnyType * m_singlePressCallbackParam;         ///< Parameter for single press callback.
    AnyType * m_doublePressCallbackParam;         ///< Parameter for double press callback.
    AnyType * m_longPressCallbackParam;           ///< Parameter for long press callback.
    button_handle_t m_buttonHandle;               ///< Handle for the button.

    // delete the copy constructor and the assignment operator
    ButtonModule(const ButtonModule &)             = delete;
    ButtonModule & operator=(const ButtonModule &) = delete;

    // Helper methods for callback registration
    void registerSinglePressCallback();
    void registerDoublePressCallback();
    void registerLongPressCallback();
};
