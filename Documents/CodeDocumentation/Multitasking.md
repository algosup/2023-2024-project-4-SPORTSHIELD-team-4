# Multi-tasking documentation

## Issue

There were two main issues with the SPORTSHIELD project:

1. The project was not able to handle multiple tasks at the same time, such as sending notifications while the device is ringing.
2. The project was not able to stop the alarm during the ringing cycle.

## Solution

We have only implemented the second issue, because everything was already in place to handle multiple tasks at the same time.

### Stopping the alarm

Thanks to the new Bluetooth code, we succeeded in implementing a way to stop the alarm during the ringing cycle.
To do so, we added some characteristics to the Bluetooth service, which allows the user to see the status of the alarm and to stop it.
Secondly, we created a small function named 'onWriteStopAlarm' that is called when the user sends a "command" to stop the alarm.
This function works with another function named 'stopAlarm' that stops the alarm and sends a notification to the user.
Finally, we modified the 'PulseBuzzer' function to stop the alarm when the user sends the "command" to stop it.

## Testing

We tested the new feature with the "LightBlue" application, dedicated to Bluetooth communication and testing. We made lots of tests to ensure that the alarm could be stopped during the ringing cycle and it worked perfectly.
The only default is that than a big shock is deficient to stop the alarm, but it's a hardware issue because both shocks are written in the same way.

## Conclusion

In conclusion, we have successfully implemented a way to stop the alarm during the ringing cycle and we also put in place the changes needed to handle multiple tasks at the same time.
