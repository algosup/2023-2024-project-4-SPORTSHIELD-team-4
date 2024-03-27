**Implementation :**

The modifications have been implemented at the GPS level. The goal was to ensure that when a GPS position is retrieved and then sent via SMS, IF within 15 minutes when sending the next notification, the retrieved position is equal to the previously sent position, then the SIM module should not be activated to send the notification, and the GPS should be put back into energy-saving mode.

Here is the code that takes care of doing that:

```c++
//This part of the code is implemented in the global variables 
float lastLatitude = 0.0;
float lastLongitude = 0.0;

bool hasPositionChanged(float currentLatitude, float currentLongitude) {
    float threshold = 0.0001; // Définis un seuil de changement, ajuste selon le besoin
    return (abs(currentLatitude - lastLatitude) > threshold || abs(currentLongitude - lastLongitude) > threshold);
}

//---------------------------------------------------------------------------------

// This part of the code is implemented in the loop function

// After capturing and checking GPS data
if (GPS.fix && position_acquired == false) {
    float currentLatitude = convertDMMtoDD(String(float(GPS.latitude), 4)).toFloat();
    float currentLongitude = convertDMMtoDD(String(float(GPS.longitude), 4)).toFloat();
  
    if (hasPositionChanged(currentLatitude, currentLongitude)) {
        lastLatitude = currentLatitude;
        lastLongitude = currentLongitude;
        position_acquired = true;
        GPS.fix = 0;
        digitalWrite(GPS_WKUP_PIN, LOW);
        GPS.sendCommand("$PMTK225,4*2F");  // Send in backup mode
        
    }
}
```

---

To measure the effectiveness of this implementation, we will leave the board plugged into a battery for an entire night and connect the board to a device that can measure the battery's behavior in real-time.

**Test : Battery**

**Protocol :**
To test the battery's durability, we left the board connected to the battery overnight and connected the battery to an oscillometer to determine its exact consumption over 18 hours.

**Result :**
The result of this test was positive: the battery lost 0.16V over a period of 18 hours and 18 minutes.


---

**Modification :**

**Reduction in Measurement Frequency:** The timer is set by default to 1 ms, which is extremely fast. Therefore, we have increased this interval to 1 second.

```c++
//lign modified
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

