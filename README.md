# **RelayButtonModule**

## Overview
The RelayButtonModule component provides a comprehensive interface for controlling relays and handling button events on the ESP32 platform. It includes functionalities to manage relay power states and register callbacks for button presses, supporting single, double, and long press events. This component is ideal for applications requiring reliable relay control and responsive button input.

## APIs and Usage

### RelayModule

#### Methods:
- `RelayModule(int8_t relayPin, int8_t activeLevel, int8_t initialState)`: Initializes a new RelayModule.
- `void setPower(bool newState)`: Sets the power state of the relay.
- `bool isOn()`: Checks if the relay is currently on.

#### Example:
```cpp
#include "RelayModule.hpp"

RelayModule relay(5, 1, 0);
relay.setPower(true);
bool state = relay.isOn();
```

### ButtonModule

#### Methods:
- `ButtonModule(int8_t buttonPin, uint8_t activeLevel, uint16_t longPressTimeMs, uint16_t shortPressTimeMs)`: Initializes a new ButtonModule.
- `void setSinglePressCallback(CallbackButtonFunction callback, AnyType* callbackParameter)`: Sets the callback for single press events.
- `void setDoublePressCallback(CallbackButtonFunction callback, AnyType* callbackParameter)`: Sets the callback for double press events.
- `void setLongPressCallback(CallbackButtonFunction callback, AnyType* callbackParameter)`: Sets the callback for long press events.

#### Example:
```cpp
#include "ButtonModule.hpp"

ButtonModule button(4, 1, 2000, 100);
button.setSinglePressCallback(singlePressCallback);
button.setDoublePressCallback(doublePressCallback);
button.setLongPressCallback(longPressCallback);
```

## Installation

To install this component, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/username/RelayButtonModule.git
   ```
2. Navigate to the project directory:
   ```sh
   cd RelayButtonModule
   ```
3. Install the dependencies:
   ```sh
   make install
   ```   

## Dependencies

This component depends on the following libraries:
* ESP_IDF
* iot_button

## License
This component is licensed under the MIT License. See the LICENSE file for more details.

## Author
Ronny Antoon - MetaHouse company