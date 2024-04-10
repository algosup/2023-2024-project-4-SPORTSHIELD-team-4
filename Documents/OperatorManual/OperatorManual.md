# Operator Manual

## Table of Contents

- [Operator Manual](#operator-manual)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Versions](#versions)
    - [1.0](#10)
      - [Code Changes](#code-changes)
    - [1.1](#11)
      - [Code Changes](#code-changes-1)
    - [1.2](#12)
      - [Code Changes](#code-changes-2)
    - [1.3](#13)
      - [Code Changes](#code-changes-3)
  - [Conclusion](#conclusion)

## Introduction

This document provides information on all the changes made to the code of the SPORTSHIELD system. This document is written in the following order:

- Version
- Changes and how do they affect the system
- Code changed

Thanks to this document, all the futures developers working on the SPORTSHIELD code will be able to quickly understand the changes and how to use them.

## Versions

### 1.0

This is the first version of the system, and it includes the following changes:

- Battery life improvements

The battery's life has been improved by removing unnecessary code and optimizing the existing code.

#### Code Changes

- GPS modifications:
  - If the position is not updated, the SIM module will be turned off to save battery and the GPS module will be put to sleep mode.

Here is the code that takes care of doing that in `SPORTSHIELD.ino`:

```c++
//This part of the code is implemented in the global variables
float lastLatitude = 0.0;
float lastLongitude = 0.0;

bool hasPositionChanged(float currentLatitude, float currentLongitude) {
    float threshold = 0.0001; // Define the threshold based on the precision needed
    return (abs(currentLatitude - lastLatitude) > threshold || abs(currentLongitude - lastLongitude) > threshold);
}

//---------------------------------------------------------------------------------

// This part of the code is implemented in the loop function

// After the GPS position is acquired
if (GPS.fix && position_acquired == false) {
    float currentLatitude = convertDMMtoDD(String(float(GPS.latitude), 4)).toFloat();
    float currentLongitude = convertDMMtoDD(String(float(GPS.longitude), 4)).toFloat();

    if (hasPositionChanged(currentLatitude, currentLongitude)) {
        lastLatitude = currentLatitude;
        lastLongitude = currentLongitude;
        position_acquired = true;
        GPS.fix = 0;
        digitalWrite(GPS_WKUP_PIN, LOW);
        GPS.sendCommand("$PMTK225,4*2F");  // Put GPS to sleep mode

    }
}
```

### 1.1

This version includes the following changes:

- Code optimization to increase battery lifespan
- Battery levels management
  - To increase the battery lifespan, we created thresholds for the battery levels. When the battery level is below a certain threshold, the system will disable some functionalities to save battery but if, in the other hand, the battery level is above a certain threshold, the system will stop the charging process to avoid overcharging the battery and decrease its lifespan.

#### Code Changes

- Battery level management:
  - The battery level is checked every 10 seconds, and depending on the level, the system will either disable some functionalities or stop the charging process.

Here is the code that takes care of doing that in `SPORTSHIELD.ino`:

```c++
//-------------------------------- LOOP ----------------------------------------
void loop() {

  float batteryVoltage = getBatteryVoltage();
  checkBattery(batteryVoltage); // Check the battery level at the beginning of the loop and take action if necessary

    ...
}

//-------------------------------- FUNCTIONS -----------------------------------

void onWriteActivation(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate) {
    Config.isActivate = ActivationCharacteristic.value();
    if (Config.isActivate != 0 && isLowBattery == false) {
      Serial.println("Alarme enabled");
      digitalWrite(SIM800_DTR_PIN, LOW);  // put in normal mode
      delay(100);
      sim800l->setPowerMode(NORMAL);  // set normal functionnality mode
    } else if (Config.isActivate == 0 && isLockedBattery == false) {
      Serial.print("Désactivation");
      sim800l->setPowerMode(MINIMUM);      // set minimum functionnality mode
      digitalWrite(SIM800_DTR_PIN, HIGH);  // put in sleep mode
    } else {
      Serial.println("Battery level too low, please charge the device.");
    }
  } else {
    ActivationCharacteristic.writeValue(Config.isActivate);
  }
}

void onWriteUnlock(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate) {
    if (isLockedBattery == false) {
      // activate electromagnet
      Serial.println("Unlock");
      digitalWrite(aimantPin, HIGH);
      delay(2000);
      digitalWrite(aimantPin, LOW);
    } else {
      Serial.println("Battery level too low, please charge the device.");
    }
  }
}
```

and the one in 'battery.h':

```c++
#pragma once

/*
  This file contains the functions and setup functions for the Battery Management System.
*/

// Globale variables
#ifndef GLOBALVAR_H
  #include "globalVar.h"
#endif


//---------------- VARIABLES -----------------------------

// The different battery states, measured in volts.
// If you want to change the battery states, you can change the values below.
#define FULL_CHARGE 3.65
#define LOW_BATTERY 3.475
#define LOCKED_BATTERY 3.4

//------------- FUNCTIONS ------------------------------

/*
  * Function to get the battery voltage
  * @return The battery voltage, in volts
*/
float getBatteryVoltage() {
  //unsigned int adcCount = analogRead(PIN_VBAT);
  float adcCount = analogRead(PIN_VBAT);
  float adcVoltage = (((adcCount - 3000) / 4096) * 0.55) + 3.6;
  //float vBat = adcVoltage * 1510.0/510.0;
  return adcVoltage;
}

/*
  * Function to start charging the battery
  * @note Don't use this function if you don't know what you are doing
*/
void stopChargingBattery() {
  // To implement with the good material
}

/*
  * Function to check the battery state
  * @param batteryVoltage The battery voltage, in volts
  * @return Depending on the battery state, the function acts differently
  * @note We advise you to get the battery voltage with the function getBatteryVoltage()
*/
void checkBattery(float batteryVoltage) {
  if (batteryVoltage > LOW_BATTERY) {
    isLowBattery = false;
    if (batteryVoltage >= FULL_CHARGE) {
      //Serial.println("Battery fully charged");
      stopChargingBattery();
    }
  } else {
    isLockedBattery = false;
    isLowBattery = true;
    if (batteryVoltage == LOW_BATTERY) {
      Serial.println("Battery put in low battery mode, you can only unlock the device. Please charge the device.");
    } else if (batteryVoltage <= LOCKED_BATTERY) {
      isLockedBattery = true;
      Serial.println("Battery put in locked mode, please charge the device.");
    }
  }
}
```

For further information, please refer to the Battery Management System documentation that can be found in the documents folder or by clicking [here](../CodeDocumentation/batteryImprovement.md).

### 1.2

This version includes the following changes:

- Code optimization to increase battery lifespan
- Better battery levels management
- Code optimization to improve Bluetooth security
  - The system now requires the user to enter a password to access the functionalities. The password is stored in the system and compared to the one entered by the user.

#### Code Changes

- Bluetooth security:
  - Now, if you want to access the functionalities of the system, you need to enter a password. If the password is correct, you will be able to access the functionalities. Otherwise, you will be denied access.

Here is the code that takes care of doing that in `bluetooth.h`:

```c++
/*
  This file contains the functions and setup functions for the Bluetooth Low Energy module
*/

#pragma once

#ifndef GLOBALVAR_H
  #include "globalVar.h"
#endif

//------------- FUNCTIONS ------------------------------

/*
 * Function called when a central device connects to the peripheral
 * @param central the address of the central device
 * @return void
*/
void onConnect(BLEDevice central) {
  Serial.print("Connected to ");
  Serial.println(central.address());
  Serial.println(BLE.address());
  digitalWrite(LEDB, LOW);
}

/*
 * Function called when a central device disconnects from the peripheral
 * @param central the address of the central device
 * @return void
*/
void onDisconnect(BLEDevice central) {
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());
  isAuthenticate = false;
  userDevice = BLEDevice();
  digitalWrite(LEDB, HIGH);
}

/*
 * Function called when a central device writes to the password characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic written to
 * @return void
*/
void onWritePassword(BLEDevice central, BLECharacteristic characteristic) {
  String password = "13330";
  String value = PasswordCharacteristic.value();
  isAuthenticate = (password.compareTo(value) == 0);
  if(isAuthenticate){
    Serial.println("Successful authentication");
    userDevice = central;
  }
  else{
    Serial.println("Wrong password");
  }
}


/*
 * Function called when a central device writes to the name characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic written to
 * @return void
*/
void onWriteName(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate && (userDevice.address().compareTo(central.address()) == 0)){
    Config.Name = NameCharacteristic.value();
    String value = NameCharacteristic.value();
    Serial.print("Written name : ");
    Serial.println(value);
  } else {
    NameCharacteristic.writeValue("\n");
  }
}

/*
 * Function called when a central device reads the name characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic read
 * @return void
*/
void onReadName(BLEDevice central, BLECharacteristic characteristic) {
  Serial.println("CALLBACK READ");
  Serial.println(isAuthenticate);
  if (isAuthenticate && (userDevice.address().compareTo(central.address()) == 0)) {
    NameCharacteristic.writeValue(Config.Name);
  } else {
    NameCharacteristic.writeValue("\n");
  }
}

/*
 * Function called when a central device writes to the activation characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic written to
 * @return void
*/
void onWriteActivation(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate && (userDevice.address().compareTo(central.address()) == 0)) {
    Config.isActivate = ActivationCharacteristic.value();
    if (Config.isActivate != 0) {
      Serial.println("Alarme enabled");
      digitalWrite(SIM800_DTR_PIN, LOW);  // put in normal mode
      delay(100);
      sim800l->setPowerMode(NORMAL);  // set normal functionnality mode
    } else {
      Serial.print("Deactivation");
      sim800l->setPowerMode(MINIMUM);      // set minimum functionnality mode
      digitalWrite(SIM800_DTR_PIN, HIGH);  // put in sleep mode
    }
  } else {
    ActivationCharacteristic.writeValue(Config.isActivate);
  }
}

/*
 * Function called when a central device reads the activation characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic read
 * @return void
*/
void onReadActivation(BLEDevice central, BLECharacteristic characteristic) {
  // Serial.println("CALLBACK READ");
  // Serial.println(isAuthenticate);
  ActivationCharacteristic.writeValue(Config.isActivate);
}

/*
 * Function called when a central device writes to the unlock characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic written to
 * @return void
*/
void onWriteUnlock(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate && (userDevice.address().compareTo(central.address()) == 0)) {
    // activate electromagnet
    Serial.println("Unlock");
    digitalWrite(aimantPin, HIGH);
    delay(2000);
    digitalWrite(aimantPin, LOW);
  }
}

//------------- SETUP FUNCTIONS ------------------------------

/*
 * Function to setup the Bluetooth Low Energy module
 * @return void
*/
void ble_setup(void) {
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1)  // set a reset in this case? risk of card crash?
      ;
  }
  // Set random seed for token
  randomSeed(analogRead(0));
  // set advertised local name and service UUID:
  BLE.setLocalName("Team4");
  BLE.setDeviceName("Team4");
  BLE.setAdvertisedService(PasswordService);
  // add descriptors
  PasswordCharacteristic.addDescriptor(PasswordDescriptor);
  NameCharacteristic.addDescriptor(NameDescriptor);
  ActivationCharacteristic.addDescriptor(ActivationDescriptor);
  UnlockCharacteristic.addDescriptor(UnlockDescriptor);
  MACCharacteristic.addDescriptor(MACDescriptor);
  // add the characteristic to the service
  PasswordService.addCharacteristic(PasswordCharacteristic);
  ConfigService.addCharacteristic(NameCharacteristic);
  ConfigService.addCharacteristic(ActivationCharacteristic);
  ConfigService.addCharacteristic(UnlockCharacteristic);
  ConfigService.addCharacteristic(MACCharacteristic);
  // add service
  BLE.addService(PasswordService);
  BLE.addService(ConfigService);
  // set the initial value for the characeristic:
  PasswordCharacteristic.writeValue("0");
  NameCharacteristic.writeValue("\n");
  ActivationCharacteristic.writeValue(false);
  UnlockCharacteristic.writeValue(false);
  MACCharacteristic.writeValue(BLE.address());
  //set event handler
  BLE.setEventHandler(BLEConnected, onConnect);
  BLE.setEventHandler(BLEDisconnected, onDisconnect);
  PasswordCharacteristic.setEventHandler(BLEWritten, onWritePassword);
  NameCharacteristic.setEventHandler(BLEWritten, onWriteName);
  NameCharacteristic.setEventHandler(BLERead, onReadName);
  ActivationCharacteristic.setEventHandler(BLEWritten, onWriteActivation);
  ActivationCharacteristic.setEventHandler(BLERead, onReadActivation);
  UnlockCharacteristic.setEventHandler(BLEWritten, onWriteUnlock);
  // start advertising
  BLE.advertise();
}
```

For further information, please refer to the Bluetooth Low Energy documentation that can be found in the documents folder or by clicking [here](../CodeDocumentation/bluetoothSecurity.md).

### 1.3

This version includes the following changes:

- Code optimization to increase battery lifespan
- Better battery levels management
- Code optimization to improve Bluetooth security
- Alarm system management
  - The system now includes an alarm system that can be activated and deactivated using the Bluetooth module. The alarm system can be stopped by sending a command to the system.

#### Code Changes

- Alarm management:
  - The system now includes an alarm system that can be activated and deactivated using the Bluetooth module. The alarm system can be stopped by sending a command to the system.

Here is the code that takes care of doing that in `SPORTSHIELD.ino`:

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
  Serial.println("Start stopAlarm"); // Add this line
  alarmShouldStop = true;
  Serial.println("alarmShouldStop defined on true"); // Add this line
}

void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff) {
  static int buzzerState = LOW;
  unsigned long currentMillis = millis();

    // Check if the alarm should be stopped
    if (alarmShouldStop) {
        Serial.println("Arrêt de l'alarme en cours dans PulseBuzzer");
        digitalWrite(buzzerPin, LOW); // Turn off the buzzer
        alarmShouldStop = false; // Reset the alarm stop flag for next use
        currentRep = 0; // Reset the repetitions counter
        previousMillis = 0; // Reset the time counter
        MotionSmall = false; // Reset the small motion flag
        MotionBig = false;
        return; // Exit the function
    }

    // If the alarm should not be stopped, continue the normal operation
    if (currentRep < repetitions) {
        if ((buzzerState == LOW && currentMillis - previousMillis >= durationOff) ||
            (buzzerState == HIGH && currentMillis - previousMillis >= durationOn)) {

            buzzerState = !buzzerState; // Invert the buzzer state
            digitalWrite(buzzerPin, buzzerState); // Set the buzzer state
            previousMillis = currentMillis; // Update the time counter

            // If the buzzer is turned off, increment the repetitions counter
            if (buzzerState == LOW) {
                currentRep++;
            }
        }
    } else {
        // Once the repetitions are done, reset the variables
        currentRep = 0;
        previousMillis = 0;
        MotionSmall = false;
        MotionBig = false;
    }
}

```

and the one in `globalVar.h`:

```c++
//---------------- GLOBAL VARIABLES -----------------------------
BLEBooleanCharacteristic StopAlarmCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1218", BLEWrite); // Add this line to the global variables
BLEDescriptor stopAlarmDescriptor("2901", "Stop Alarm");
bool alarmShouldStop = false; // Global variable to stop the alarm
```

For further information, please refer to the Alarm System documentation that can be found in the documents folder or by clicking [here](../CodeDocumentation/Multitasking.md).

## Conclusion

Even if we were unable to implement all the functionalities we wanted, such as the NFC reader (you can find the reason in the NFC documentation [here](../CodeDocumentation/NFC.md)), we are proud of the work we have accomplished. We have managed to create a system that is both efficient and secure. We hope that this document will help you understand the changes made to the SPORTSHIELD system and that you will be able to use it to its full potential.
