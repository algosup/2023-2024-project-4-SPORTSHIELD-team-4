**Implementation :**

The modifications have been implemented at the GPS level. The goal was to ensure that when a GPS position is retrieved and then sent via SMS, IF within 15 minutes when sending the next notification, the retrieved position is equal to the previously sent position, then the SIM module should not be activated to send the notification, and the GPS should be put back into energy-saving mode.

Here is the code that takes care of doing that:

```c++
//This part of the code is implemented in the global variables 
float lastLatitude = 0.0;
float lastLongitude = 0.0;

bool hasPositionChanged(float currentLatitude, float currentLongitude) {
    float threshold = 0.0001; // Define a threshold for change, adjust as needed.
    return (abs(currentLatitude - lastLatitude) > threshold || abs(currentLongitude - lastLongitude) > threshold);
}

//---------------------------------------------------------------------------------

// This part of the code is implemented in the loop function

// After capturing and verifying the GPS data
if (GPS.fix && position_acquired == false) {
    float currentLatitude = convertDMMtoDD(String(float(GPS.latitude), 4)).toFloat();
    float currentLongitude = convertDMMtoDD(String(float(GPS.longitude), 4)).toFloat();
  
    if (hasPositionChanged(currentLatitude, currentLongitude)) {
        lastLatitude = currentLatitude;
        lastLongitude = currentLongitude;
        position_acquired = true;
        GPS.fix = 0;
        digitalWrite(GPS_WKUP_PIN, LOW);
        GPS.sendCommand("$PMTK225,4*2F");  // Send to backup mode
        
    }
}
```

---

To measure the effectiveness of this implementation, we will leave the board plugged into a battery for an entire night and connect the board to a device that can measure the battery's behavior in real-time.

---

**Modification :**

**Reduction in Measurement Frequency:** The timer is set by default to 1 ms, which is extremely fast. Therefore, we have increased this interval to 1 second.

```c++
//Modified lign
#define HW_TIMER_INTERVAL_MS 1000
```

---

**Modification :**

Increase in the sensitivity threshold to activate the buzzer. 

To avoid triggering the buzzer too easily and thus avoid unnecessary triggering of the buzzer.

```c++
float SmallMT = 40.0;  //     SmallMotionThreshold
float BigMT = 170.0;   //    BigMotionThreshold

float SmallRT = 40.0;  //     SmallRotationThreshold
float BigRT = 145.0;   //     BigRotationThreshold
```

---

**Alarm Management :**

`SportShield.ino`

```c++
void onWriteStopAlarm(BLEDevice central, BLECharacteristic characteristic) {
  if (StopAlarmCharacteristic.value()) {
    stopAlarm();
    StopAlarmCharacteristic.writeValue(false);
  } else {
  }
}

//--------------SETUP FUNCTION------------------------------------
StopAlarmCharacteristic.addDescriptor(stopAlarmDescriptor);
ConfigService.addCharacteristic(StopAlarmCharacteristic);
StopAlarmCharacteristic.setEventHandler(BLEWritten, onWriteStopAlarm);

//------------- ADDITIONAL FUNCTIONS ------------------------------
void stopAlarm() {
  Serial.println("Début stopAlarm"); 
  alarmShouldStop = true;
  Serial.println("alarmShouldStop défini sur true"); 
}

void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff) {
  static int buzzerState = LOW;
  unsigned long currentMillis = millis();

    // Check if the alarm should be stopped
    // Serial.println("PulseBuzzer appelée"); // Log pour débogage
    if (alarmShouldStop) {
        Serial.println("Arrêt de l'alarme en cours dans PulseBuzzer"); 
        digitalWrite(buzzerPin, LOW); // Turn off the buzzer
        alarmShouldStop = false; // Reset the flag to allow future activation
        currentRep = 0; // Reset the repetition counter
        previousMillis = 0; // Reset the time counter
        MotionSmall = false; // Reset the motion indicators
        MotionBig = false;
        return; 
    }

    // If the alarm is not requested to be stopped, continue the normal process
    if (currentRep < repetitions) {
        if ((buzzerState == LOW && currentMillis - previousMillis >= durationOff) ||
            (buzzerState == HIGH && currentMillis - previousMillis >= durationOn)) {
            
            buzzerState = !buzzerState; // Change the state of the buzzer
            digitalWrite(buzzerPin, buzzerState); // Update the state of the buzzer
            previousMillis = currentMillis; // Reset the time counter

            // If the buzzer has just been turned off, increment the repetition counter
            if (buzzerState == LOW) {
                currentRep++;
            }
        }
    } else {
        // Once all repetitions are done, reset the variables for future use
        currentRep = 0;
        previousMillis = 0;
        MotionSmall = false;
        MotionBig = false;
    }
}

```

---

`GlobalVar.h`

```c++
//---------------- GLOBAL VARIABLES -----------------------------
BLEBooleanCharacteristic StopAlarmCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1218", BLEWrite); // Adding a feature to stop the alarm
BLEDescriptor stopAlarmDescriptor("2901", "Stop Alarm");
bool alarmShouldStop = false; // Globale Variable to control the stopping of the alarm.

```


