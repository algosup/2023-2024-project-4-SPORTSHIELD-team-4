//---------------- VARIABLES -----------------------------

// The different battery states, measured in volts.
// If you want to change the battery states, you can change the values below.
#define FULL_CHARGE 3.65
#define LOW_BATTERY 3.475
#define LOCKED_BATTERY 3.4

// Those variables are used to know the state of the battery
// !! Do not modify them
bool isLowBattery = false;
bool isLockedBattery = false;

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
  * Function to check the battery state
  * @param batteryVoltage The battery voltage, in volts
  * @return Depending on the battery state, the function acts differently
  * @note We advise you to get the battery voltage with the function getBatteryVoltage()
*/
void checkBattery(float batteryVoltage) {
  if (batteryVoltage > LOW_BATTERY) {
    isLowBattery = false;
    if (batteryVoltage >= FULL_CHARGE) {
      Serial.println("Battery fully charged");
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


/*
  * Function to start charging the battery
  * @note Don't use this function if you don't know what you are doing
*/
void stopChargingBattery() {
// !! Copilot made code, may be incorrect
  digitalWrite(P0_13, HIGH); // Stop charging the battery
}