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
  digitalWrite(LEDB, HIGH);
}

/*
 * Function called when a central device writes to the password characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic written to
 * @return void
*/
void onWritePassword(BLEDevice central, BLECharacteristic characteristic) {
  const int motDePasseAttendu = 13330;
  short int value = PasswordCharacteristic.value();
  // Conversion(value);
  isAuthenticate = (value == motDePasseAttendu);
  Serial.println(isAuthenticate ? "successful authentication" : "wrong password");
}

/*
 * Function to convert a short int to a hexadecimal string
 * @param data the short int to convert
 * @return the hexadecimal string
*/
String Conversion(unsigned short int data) {
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
  return String(mdphexadecimal);
}

/*
 * Function called when a central device writes to the name characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic written to
 * @return void
*/
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

/*
 * Function called when a central device reads the name characteristic
 * @param central the address of the central device
 * @param characteristic the characteristic read
 * @return void
*/
void onReadName(BLEDevice central, BLECharacteristic characteristic) {
  Serial.println("CALLBACK READ");
  Serial.println(isAuthenticate);
  if (isAuthenticate) {
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
  if (isAuthenticate) {
    Config.isActivate = ActivationCharacteristic.value();
    if (Config.isActivate != 0) {
      Serial.println("Alarme enabled");
      digitalWrite(SIM800_DTR_PIN, LOW);  // put in normal mode
      delay(100);
      sim800l->setPowerMode(NORMAL);  // set normal functionnality mode
    } else {
      Serial.print("Désactivation");
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
  if (isAuthenticate) {
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
  // start advertising
  BLE.advertise();
}