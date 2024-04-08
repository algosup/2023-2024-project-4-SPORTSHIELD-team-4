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

// Après avoir capturé et vérifié les données GPS
if (GPS.fix && position_acquired == false) {
    float currentLatitude = convertDMMtoDD(String(float(GPS.latitude), 4)).toFloat();
    float currentLongitude = convertDMMtoDD(String(float(GPS.longitude), 4)).toFloat();
  
    if (hasPositionChanged(currentLatitude, currentLongitude)) {
        lastLatitude = currentLatitude;
        lastLongitude = currentLongitude;
        position_acquired = true;
        GPS.fix = 0;
        digitalWrite(GPS_WKUP_PIN, LOW);
        GPS.sendCommand("$PMTK225,4*2F");  // Envoyer au mode backup
        
    }
}
```

---

To measure the effectiveness of this implementation, we will leave the board plugged into a battery for an entire night and connect the board to a device that can measure the battery's behavior in real-time.

---

**Modification :**

**Reduction in Measurement Frequency:** The timer is set by default to 1 ms, which is extremely fast. Therefore, we have increased this interval to 1 second.

```c++
//ligne modifié
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
  Serial.println("Début stopAlarm"); // Ajoutez cette ligne
  alarmShouldStop = true;
  Serial.println("alarmShouldStop défini sur true"); // Ajoutez cette ligne
}

void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff) {
  static int buzzerState = LOW;
  unsigned long currentMillis = millis();

    // Vérifie si l'alarme doit être arrêtée
    // Serial.println("PulseBuzzer appelée"); // Log pour débogage
    if (alarmShouldStop) {
        Serial.println("Arrêt de l'alarme en cours dans PulseBuzzer"); 
        digitalWrite(buzzerPin, LOW); // Éteindre le buzzer
        alarmShouldStop = false; // Réinitialiser le drapeau pour permettre une future activation
        currentRep = 0; // Réinitialiser le compteur de répétitions
        previousMillis = 0; // Réinitialiser le compteur de temps
        MotionSmall = false; // Réinitialiser les indicateurs de mouvement
        MotionBig = false;
        return; // Sortir immédiatement de la fonction
    }

    // Si l'alarme n'est pas demandée à être arrêtée, continuer le processus normal
    if (currentRep < repetitions) {
        if ((buzzerState == LOW && currentMillis - previousMillis >= durationOff) ||
            (buzzerState == HIGH && currentMillis - previousMillis >= durationOn)) {
            
            buzzerState = !buzzerState; // Changer l'état du buzzer
            digitalWrite(buzzerPin, buzzerState); // Mettre à jour l'état du buzzer
            previousMillis = currentMillis; // Réinitialiser le compteur de temps

            // Si le buzzer vient d'être éteint, incrémenter le compteur de répétitions
            if (buzzerState == LOW) {
                currentRep++;
            }
        }
    } else {
        // Une fois toutes les répétitions effectuées, réinitialiser les variables pour une prochaine utilisation
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
BLEBooleanCharacteristic StopAlarmCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1218", BLEWrite); // Ajout d'une caractéristique pour arrêter l'alarme
BLEDescriptor stopAlarmDescriptor("2901", "Stop Alarm");
bool alarmShouldStop = false; // Variable globale pour contrôler l'arrêt de l'alarme

```


