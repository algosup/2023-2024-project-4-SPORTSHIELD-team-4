/*
  This file is the main file of the project. It contains the setup and loop functions
*/

// Globale variables
#ifndef GLOBALVAR_H
  #include "globalVar.h"
#endif

// BLE
#ifndef BLE_H
  #include "bleSettings.h"
#endif

//-------------------------------- SETUP ----------------------------------------
/*
  * Function to setup the buzzer, electro-aimant, debug led, power bridge, battery, timer, BLE, IMU, GPS, SIM800L, and analog read resolution
  * @return void
*/
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

  Serial.println("fin setup ");
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
    PulseBuzzer(3, 100, 100);  // repetitions, DurationOn , DurationOff
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
    BLE.poll();  //communication autorisé
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



  if (send_move) {  //sending of positions via SIM module
    Serial.println("Envoi detection mouvement");
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

/*
  * Function to setup the accelerometer
  * @return void
*/
void imu_setup(void) {
  if (imu.begin() != 0) {
    Serial.println("Device error");
  } else {
    Serial.println("Accelerometer launched");
  }
}

/*
  * Function to setup the GPS module
  * @return void
*/
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

/*
  * Function to setup the SIM800L module
  * @return void
*/
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
/*
  * Function to get the battery voltage
  * @return float
*/
float getBatteryVoltage() {
  //unsigned int adcCount = analogRead(PIN_VBAT);
  float adcCount = analogRead(PIN_VBAT);
  float adcVoltage = (((adcCount - 3000) / 4096) * 0.55) + 3.6;
  //float vBat = adcVoltage * 1510.0/510.0;
  return adcVoltage;
}

/*
  * Function to get the motion data; provides the absolute difference in acceleration between consecutive calls, helping to monitor changes in motion over time
  * @return float
*/
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

/*
  * Function to get the rotation data; provides the absolute difference in rotation between consecutive calls, helping to monitor changes in rotation over time
  * @return float
*/
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

/*
  * Function to print current time in hours, minutes, and seconds
  * @return void
*/
void Temps(void) {
  unsigned long millisPassed = millis();
  unsigned int seconds = (millisPassed / 1000) % 60;
  unsigned int minutes = (millisPassed / (1000 * 60)) % 60;
  unsigned int hours = (millisPassed / (1000 * 60 * 60)) % 24;
  Serial.print("Détecté a : ");
  Serial.print(hours);
  Serial.print("h");
  Serial.print(minutes);
  Serial.print("mn");
  Serial.print(seconds);
  Serial.println("s");
}

/*
  * Function to pulse the buzzer for a specified number of repetitions, duration on, and duration off
  * @param repetitions the number of times to pulse the buzzer
  * @param durationOn the duration in milliseconds the buzzer is on
  * @param durationOff the duration in milliseconds the buzzer is off
  * @return void
*/
void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff) {
  static int buzzerState = LOW;
  unsigned long currentMillis = millis();

  if (currentRep < repetitions) {
    if (currentMillis - previousMillis >= (buzzerState == LOW ? durationOn : durationOff)) {
      digitalWrite(buzzerPin, buzzerState = !buzzerState);
      previousMillis = currentMillis;
      if (!buzzerState) currentRep++;
    }
  } else {
    // Reset variables after performing all repetitions
    currentRep = 0;
    previousMillis = 0;
    MotionSmall = false;
    MotionBig = false;
  }
}

/*
  * Function to check if the position has changed
  * @param currentLatitude the current latitude
  * @param currentLongitude the current longitude
  * @return bool
*/
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

/*
  * Function to activate the GPS module
  * @return void
*/
void activateGPS() {
  if (start_gps == true) {
    digitalWrite(GPS_WKUP_PIN, HIGH);
    start_gps = false;
  }
}

/*
  * Function to activate the ISR timer
  * @return void
*/
void TimerHandler() {
  ISR_Timer.run();
}

/*
  * Function to set send_position to true
  * @return void
*/
void SIM_ISR() {
  send_position = true;
}

/*
  * Function to convert DMM coordinates to DD coordinates
  * @param dmmCoordinates the DMM coordinates to convert
  * @return String
*/
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