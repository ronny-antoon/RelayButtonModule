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
     * @param buttonPin The GPIO pin number connected to the button.
     * @param activeLevel The active level of the button (1 for active high, 0 for active low).
     * @param longPressTimeMs The time in milliseconds to consider a press as a long press.
     * @param shortPressTimeMs The time in milliseconds to consider a press as a short press.
     */
    ButtonModule(int8_t buttonPin = -1, uint8_t activeLevel = 1, uint16_t longPressTimeMs = 2000, uint16_t shortPressTimeMs = 100);

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
    AnyType * m_singlePressCallbackParameter;     ///< Parameter for single press callback.
    AnyType * m_doublePressCallbackParameter;     ///< Parameter for double press callback.
    AnyType * m_longPressCallbackParameter;       ///< Parameter for long press callback.
    button_handle_t m_buttonHandle;               ///< Handle for the button.
};
