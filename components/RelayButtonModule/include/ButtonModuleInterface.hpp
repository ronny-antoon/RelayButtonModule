#pragma once

/**
 * @brief Interface for a button module.
 *
 * This interface defines the basic operations for handling button events.
 */
class ButtonModuleInterface
{
public:
    /**
     * @brief Type definition for a button callback function.
     */
    using CallbackButtonFunction = void (*)(void *);

    /**
     * @brief Type definition for any type parameter.
     */
    using AnyType = void;

    /**
     * @brief Virtual destructor for the interface.
     */
    virtual ~ButtonModuleInterface() = default;

    /**
     * @brief Set the callback function for single press events.
     *
     * @param callback The callback function to be called on single press.
     * @param callbackParameter Optional parameter to be passed to the callback function.
     */
    virtual void setSinglePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter = nullptr) = 0;

    /**
     * @brief Set the callback function for double press events.
     *
     * @param callback The callback function to be called on double press.
     * @param callbackParameter Optional parameter to be passed to the callback function.
     */
    virtual void setDoublePressCallback(CallbackButtonFunction callback, AnyType * callbackParameter = nullptr) = 0;

    /**
     * @brief Set the callback function for long press events.
     *
     * @param callback The callback function to be called on long press.
     * @param callbackParameter Optional parameter to be passed to the callback function.
     */
    virtual void setLongPressCallback(CallbackButtonFunction callback, AnyType * callbackParameter = nullptr) = 0;
};
