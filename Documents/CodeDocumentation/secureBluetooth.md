# Secure Bluetooth

## Issue

Bluetooth communication between the device and a smartphone is not totally secure. Although a password is required for connection, there is no verification during communication that the connected smartphone is still the same one.

## Analysis

To improve security, the device needs to know whether the connected device is still the same during communication, and reject requests from other devices.

## Solutions

### Possible Solutions
Several solutions can solve the problem:
- Use a generated token to chat with the smartphone
- Register an ID for the connected smartphone and only accept valid requests based on this ID. 

### Chosen Solution

The remaining solution is to register an ID for the connected smartphone and only accept valid requests based on this ID. This solution is selected because it is easier to implement and more secure.

To achieve this, once the connection and the password are valid, the device will save the Bluetooth MAC address of the connected smartphone and only accept requests from this MAC address by using this `if` statement:
```c++
if (isAuthenticate && (userDevice.address().compareTo(central.address()) == 0))
```
Which can compare the MAC address of the connected smartphone with the one saved in the device.

## Testing

All tests were carried out with the "LightBlue" application, dedicated to Bluetooth communication and testing. We tested all communication requests with and without authentication and found that even if a smartphone is connected, it cannot send a request without being registered as a co-interlocutor.

## Conclusion

In conclusion, it is important to improve the security of Bluetooth communications in order to preserve the usefulness of the project and avoid incidents.
