/*
  This file is the main file of the project. It contains the setup and loop functions
*/

// Globale variables
#ifndef GLOBALVAR_H
#include "globalVar.h"
#endif

// Battery
#ifndef BATTERY_H
#include "battery.h"
#endif

/**
 * Check if the position has changed based on the current latitude and longitude compared to the last known values.
 *
 * @param currentLatitude the current latitude value
 * @param currentLongitude the current longitude value
 *
 * @return true if the position has changed beyond a certain threshold, false otherwise
 */
bool hasPositionChanged(float currentLatitude, float currentLongitude) {
    float threshold = 0.0001; // Define a threshold for change, adjust as needed
    return (abs(currentLatitude - lastLatitude) > threshold || abs(currentLongitude - lastLongitude) > threshold);
}

/**
 * Handle the event when writing to the StopAlarm characteristic.
 *
 * @param central the BLE device triggering the event
 * @param characteristic the BLE characteristic being written to
 *
 * @return void
*/
void onWriteStopAlarm(BLEDevice central, BLECharacteristic characteristic) {
  if (StopAlarmCharacteristic.value()) {
    stopAlarm();
    StopAlarmCharacteristic.writeValue(false);
  } else {
  }
}


//-------------------------------- SETUP ----------------------------------------
void setup() {
  pinMode(buzzerPin, OUTPUT);  // setup for buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(1000);
  digitalWrite(buzzerPin, LOW);
  Serial.println(" buzzer");

  pinMode(aimantPin, OUTPUT);  //setup electro-aimant
  digitalWrite(aimantPin, HIGH);
  delay(1000);
  digitalWrite(aimantPin, LOW);
  Serial.println("electro");

  //debug led initialization
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LEDR, LOW);

  // power bridge control
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);

  // power battery control with the transistor
  pinMode(D9, OUTPUT);
  digitalWrite(D9, HIGH);

  // battery charging enable with high current 100mA > 50mA
  pinMode(P0_13, OUTPUT);
  digitalWrite(P0_13, LOW);

  Serial.begin(115200);
  if (!Serial) delay(1000);
  Serial.println("BLE Antivol Peripheral");

  // Timer
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))  // Interval in microsecs
  {
    Serial.print(F("Starting ITimer OK, millis() = "));
    Serial.println(millis());
  }
  ISR_Timer.setInterval(TIMER_INTERVAL_120S, GPS_ISR);

  ble_setup();
  Serial.println(" ble_setup");
  imu_setup();
  Serial.println(" imu_setup");
  gps_setup();
  Serial.println(" gps_setup");
  Serial2.begin(9600);
  delay(100);
  sim800l = new SIM800L((Stream*)&Serial2, SIM800_RST_PIN, 200, 512);
  pinMode(SIM800_DTR_PIN, OUTPUT);
  delay(1000);
  //sim_setup();
  Serial.println("SIM SETUP");

  analogReadResolution(ADC_RESOLUTION);  //setup battery reading
  pinMode(PIN_VBAT, INPUT);
  pinMode(VBAT_ENABLE, OUTPUT);
  digitalWrite(VBAT_ENABLE, LOW);

  Serial.println("end setup ");
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  Temps();

  Serial.print("V Bat: ");
  Serial.println(getBatteryVoltage());
}

//-------------------------------- LOOP ----------------------------------------
void loop() {

  MotionData = getMotionData();
  RotationData = getRotationData();

  float batteryVoltage = getBatteryVoltage();
  //Serial.println(batteryVoltage);
  checkBattery(batteryVoltage); // Check the battery level at the beginning of the loop and take action if necessary

  if (Config.isActivate) {  //alarm enalbled
    activateGPS();

    if (MotionData > BigMT || RotationData > BigRT) {  //Big motion detection
      if (MotionData > BigMT) {
        Serial.print("Motion detected : ");
        Serial.println(MotionData);
      } else {
        Serial.print("Rotation detected : ");
        Serial.println(RotationData);
      }
      MotionBig = true;
      MotionSmall = false;
      send_move = true;

    } else if ((MotionBig == false) && (MotionData > SmallMT || RotationData > SmallRT)) {  //Small motion detection
      if (MotionData > SmallMT) {
        Serial.print(" Small motion: ");
        Serial.println(MotionData);
      } else {
        Serial.print("Small rota : ");
        Serial.println(RotationData);
      }
      MotionSmall = true;
    }
  }

  if (MotionBig) {
    PulseBuzzer(5, 500, 1000);  // repetitions, DurationOn , DurationOff
    //sending positions & shock notif via SIM module
  }

  if (MotionSmall) {
    PulseBuzzer(10, 100, 100);  // repetitions, DurationOn , DurationOff
  }

  MotionDetect = true;
  if ((MotionData > SmallMT) || (RotationData > SmallRT)) {
    if (MotionData > SmallMT) {
      Serial.print("WAKE UP : ");
      Serial.println(MotionData);
    } else {
      Serial.print("WAKE UP Rota: ");
      Serial.println(RotationData);
    }
  }

  //if a mvt is detected and bluetooth is disabled bluetooth activation
  if (MotionDetect == true) {
    tim_connec = millis();
    MotionDetect = false;
    if (BLE_activated == false) {
      BLE_activated = true;
      Serial.println("MVT_detect->setup");
      ble_setup();
    }
  }

  //bluetooth actived when we are interacting with the module or when the alarm is on
  if ((BLE_activated == true) || (Config.isActivate)) {
    BLE.poll();  //communication allowed
  }

  //at the end of the time during which the lock has not moved, if bluetooth is activated, and the lock is not in activation mode then it is turned off to save the battery
  if ((millis() - tim_connec > TIME_OUT_MS_BLE_ACT) && (BLE_activated == true) && (Config.isActivate != 1)) {
    BLE_activated = false;
    Serial.println("timeout->BLE_END");
    BLE.end();
  }

  //capture clocked GPS data
  GPS.read();
  if (GPS.newNMEAreceived()) {
    Serial.print(GPS.lastNMEA());    // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA()))  // this also sets the newNMEAreceived() flag to false
      Serial.println("fail to parse");
    ;  // we can fail to parse a   sentence in which case we should just wait for another
  }


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



  if (send_move) {  //sending of positions via SIM module
    Serial.println("Send motion detection");
    sim800l->setupGPRS("iot.1nce.net");
    sim800l->connectGPRS();
    String Route = "http://141.94.244.11:2000/sendNotfication/" + BLE.address();
    String RouteCoord = "http://141.94.244.11:2000/updateCoordinate/" + BLE.address();
    String str = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\"}";
    String bat = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryVoltage()) + "\"}";
    char position[200];
    char posbat[200];
    str.toCharArray(position, str.length() + 1);
    //Serial.println(str);
    bat.toCharArray(posbat, bat.length() + 1);
    Serial.println(posbat);
    char direction[200];
    char directionCoord[200];
    Route.toCharArray(direction, Route.length() + 1);
    RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
    sim800l->doPost(direction, "application/json", position, 10000, 10000);
    sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
    sim800l->disconnectGPRS();
    send_move = false;
  }

  if (send_position) {  //regular sending of positions via SIM module
    Serial.println("Envoi regulier position");
    sim800l->setupGPRS("iot.1nce.net");
    sim800l->connectGPRS();
    String RouteCoord = "http://141.94.244.11:2000/updateCoordinate/" + BLE.address();
    String bat = "{\"latitude\": \" " + convertDMMtoDD(String(float(GPS.latitude), 4)) + "\", \"longitude\":\"" + convertDMMtoDD(String(float(GPS.longitude), 4)) + "\", \"batterie\":\"" + String(getBatteryVoltage()) + "\"}";
    char posbat[200];
    bat.toCharArray(posbat, bat.length() + 1);
    Serial.println(posbat);
    Serial.println(RouteCoord);
    char directionCoord[200];
    RouteCoord.toCharArray(directionCoord, RouteCoord.length() + 1);
    sim800l->doPost(directionCoord, "application/json", posbat, 10000, 10000);
    sim800l->disconnectGPRS();
    send_position = false;
  }
}

//------------- SETUP FUNCTIONS ------------------------------
void ble_setup(void) {
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1)  // set a reset in this case? risk of card crash?
      ;
  }
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
  StopAlarmCharacteristic.addDescriptor(stopAlarmDescriptor);

  // add the characteristic to the service
  PasswordService.addCharacteristic(PasswordCharacteristic);
  ConfigService.addCharacteristic(NameCharacteristic);
  ConfigService.addCharacteristic(ActivationCharacteristic);
  ConfigService.addCharacteristic(UnlockCharacteristic);
  ConfigService.addCharacteristic(MACCharacteristic);
  ConfigService.addCharacteristic(StopAlarmCharacteristic);

  // add service
  BLE.addService(PasswordService);
  BLE.addService(ConfigService);
  // set the initial value for the characeristic:
  PasswordCharacteristic.writeValue(0);
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
  StopAlarmCharacteristic.setEventHandler(BLEWritten, onWriteStopAlarm);

  // start advertising
  BLE.advertise();
}

void imu_setup(void) {
  if (imu.begin() != 0) {
    Serial.println("Device error");
  } else {
    Serial.println("Accelerometer launched");
  }
}

void gps_setup(void) {
  pinMode(GPS_WKUP_PIN, OUTPUT);
  digitalWrite(GPS_WKUP_PIN, LOW);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
  // GPS.sendCommand("$PMTK225,8*23");   // send to Always Locate backup mode
  // GPS.sendCommand("$PMTK225,9*22");   // send to Always Locate standby mode
  // GPS.sendCommand("$PMTK225,2,4000,15000,24000,90000*16");  // send to periodic standby mode
  // GPS.sendCommand("$PMTK161,0*28");   // send to standby mode
}

void sim_setup(void) {
  while (!sim800l->isReady()) {
    Serial.println(F("Problem to initialize AT command, retry in 1 sec"));
    digitalWrite(LEDR, !digitalRead(LEDR));
    delay(1000);
  }
  sim800l->enableEchoMode();
  sim800l->setupGPRS("iot.1nce.net");

  uint8_t signal = sim800l->getSignal();
  while (signal <= 0) {
    delay(1000);
    signal = sim800l->getSignal();
  }
  Serial.println(String(signal));
  NetworkRegistration network = sim800l->getRegistrationStatus();
  while (network != REGISTERED_HOME && network != REGISTERED_ROAMING) {
    delay(1000);
    network = sim800l->getRegistrationStatus();
    Serial.print(network + " ");
    Serial.println(F("Problem to register, retry in 1 sec"));
    digitalWrite(LEDG, !digitalRead(LEDG));
  }
  delay(50);
  sim800l->setPowerMode(MINIMUM);      // set minimum functionnality mode
  digitalWrite(SIM800_DTR_PIN, HIGH);  // put in sleep mode
}


//------------- ADDITIONAL FUNCTIONS ------------------------------

// provides the absolute difference in acceleration between consecutive calls, helping to monitor changes in motion over time.
float getMotionData() {
  static float previousAcceleration = 0;
  //r
  float accelX = imu.readFloatAccelX();
  float accelY = imu.readFloatAccelY();
  float accelZ = imu.readFloatAccelZ();

  float currentAcceleration = sqrt(accelX * accelX + accelY * accelY + accelZ * accelZ) * 100;
  float MotionDataerence = currentAcceleration - previousAcceleration;  // Calculate the acceleration difference
  previousAcceleration = currentAcceleration;

  return fabs(MotionDataerence);  //returns a value always positive
}

float getRotationData() {
  static float previousRotation = 0;

  // Read gyroscope values
  float gyroX = imu.readFloatGyroX();
  float gyroY = imu.readFloatGyroY();
  float gyroZ = imu.readFloatGyroZ();

  float currentRotation = sqrt(gyroX * gyroX + gyroY * gyroY + gyroZ * gyroZ);  // Calculate the current rotation based on gyroscope readings
  float RotationDataerence = currentRotation - previousRotation;                // Calculate the difference in rotation
  previousRotation = currentRotation;                                           // Update the previous rotation value

  return fabs(RotationDataerence);
}

void Temps(void) {
  unsigned long millisPassed = millis();
  unsigned int seconds = (millisPassed / 1000) % 60;
  unsigned int minutes = (millisPassed / (1000 * 60)) % 60;
  unsigned int hours = (millisPassed / (1000 * 60 * 60)) % 24;
  Serial.print("Detected at : ");
  Serial.print(hours);
  Serial.print("h");
  Serial.print(minutes);
  Serial.print("mn");
  Serial.print(seconds);
  Serial.println("s");
}

/**
 * Stop the alarm by setting the alarmShouldStop flag to true.
 */
void stopAlarm() {
  Serial.println("Start stopAlarm"); 
  alarmShouldStop = true;
  Serial.println("alarmShouldStop Set to true"); 
}


void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff) {
  static int buzzerState = LOW;
  unsigned long currentMillis = millis();

    // Check if the alarm should be stopped
    // Serial.println("PulseBuzzer appelée"); // Log pour débogage
    if (alarmShouldStop) {
        Serial.println("Stop the current alarm in PulseBuzzer"); 
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

void GPS_ISR() {
  if (Config.isActivate != 0) {
    if (!position_acquired) {
      start_gps = true;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    } else {
      // digitalWrite(GPS_WKUP_PIN, LOW);
      // GPS.sendCommand("$PMTK225,4*2F");  // send to backup mode
      send_position = true;
      position_acquired = false;
    }
  }
}

void activateGPS() {
  if (start_gps == true) {
    digitalWrite(GPS_WKUP_PIN, HIGH);
    start_gps = false;
  }
}

void TimerHandler() {
  ISR_Timer.run();
}

void SIM_ISR() {
  send_position = true;
}

void onConnect(BLEDevice central) {
  Serial.print("Connected to ");
  Serial.println(central.address());
  Serial.println(BLE.address());
  digitalWrite(LEDB, LOW);
}

void onDisconnect(BLEDevice central) {
  Serial.print(F("Disconnected from central: "));
  Serial.println(central.address());
  isAuthenticate = false;
  digitalWrite(LEDB, HIGH);
}
void onWritePassword(BLEDevice central, BLECharacteristic characteristic) {
  const int motDePasseAttendu = 1;
  short int value = PasswordCharacteristic.value();
  // Conversion(value);
  isAuthenticate = (value == motDePasseAttendu);
  Serial.println(isAuthenticate ? "successful authentication" : "wrong password");
}

char Conversion(unsigned short int data) {
  char mdphexadecimal[5];
  sprintf(mdphexadecimal, "%04X", data);

  for (int i = 0; i < 2; ++i) {
    char temp = mdphexadecimal[i];
    mdphexadecimal[i] = mdphexadecimal[2 + i];
    mdphexadecimal[2 + i] = temp;
  }
  //Serial.println("Mot de passe : " + String(valeur) + " ");  //used to see the value in decimal
  Serial.print("Written password  = ");
  Serial.println(mdphexadecimal);
}

void onWriteName(BLEDevice central, BLECharacteristic characteristic) {
  if (isAuthenticate) {
    Config.Name = NameCharacteristic.value();
    String value = NameCharacteristic.value();
    Serial.print("Written name : ");
    Serial.println(value);
  } else {
    NameCharacteristic.writeValue("\n");
  }
}

void onReadName(BLEDevice central, BLECharacteristic characteristic) {
  Serial.println("CALLBACK READ");
  Serial.println(isAuthenticate);
  if (isAuthenticate) {
    NameCharacteristic.writeValue(Config.Name);
  } else {
    NameCharacteristic.writeValue("\n");
  }
}

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

void onReadActivation(BLEDevice central, BLECharacteristic characteristic) {
  // Serial.println("CALLBACK READ");
  // Serial.println(isAuthenticate);
  ActivationCharacteristic.writeValue(Config.isActivate);
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

String convertDMMtoDD(String dmmCoordinates) {
  int degrees;
  float minutes;
  // Separate coordinates in degrees and decimal minutes
  if (dmmCoordinates.length() == 9) {
    degrees = dmmCoordinates.substring(0, 2).toInt();
    minutes = dmmCoordinates.substring(2).toFloat();
  } else {
    degrees = dmmCoordinates.substring(0, 1).toInt();
    minutes = dmmCoordinates.substring(1).toFloat();
  }
  // Convert decimal minutes to decimal degrees
  float decimalDegrees = degrees + (minutes / 60.0);

  // Convert to string and format coordinates to decimal degrees
  String ddCoordinates = String(decimalDegrees, 10);  // You can adjust the number of decimals here

  return ddCoordinates;
}