#pragma once

#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0
#include "NRF52_MBED_TimerInterrupt.h"
#include "NRF52_MBED_ISR_Timer.h"
#include <Arduino.h>
// BLE
#include <ArduinoBLE.h>
#include "struct.h"
// IMU
#include <LSM6DS3.h>
#include <Wire.h>
//GPS
#include <Adafruit_GPS.h>
//SIM
#include "SIM800L.h"


//---------------- GLOBAL VARIABLES -----------------------------
myConfig Config;
bool isAuthenticate = false;
// Timer
#define HW_TIMER_INTERVAL_MS 1000
NRF52_MBED_Timer ITimer(NRF_TIMER_3);
NRF52_MBED_ISRTimer ISR_Timer;
#define TIMER_INTERVAL_120S 120000L
// BLE
BLEService PasswordService("19B10000-E8F2-537E-4F6C-D104768A1213");  // Bluetooth® Low Energy Service
BLEService ConfigService("19B10000-E8F2-537E-4F6C-D104768A1214");

BLEShortCharacteristic PasswordCharacteristic("19B10000-E8F2-537E-4F6C-D104768A1213", BLEWrite);  // Bluetooth® Low Energy Characteristic
BLEStringCharacteristic NameCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite, 20);
BLEStringCharacteristic MACCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1217", BLERead, 20);
BLEBooleanCharacteristic ActivationCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1215", BLERead | BLEWrite);
BLEBooleanCharacteristic UnlockCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1216", BLEWrite);
BLEBooleanCharacteristic StopAlarmCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1218", BLEWrite); // Ajout d'une caractéristique pour arrêter l'alarme


BLEDescriptor PasswordDescriptor("2901", "Password");  // Bluetooth® Low Energy Descriptor
BLEDescriptor NameDescriptor("2901", "Name");
BLEDescriptor ActivationDescriptor("2901", "Activation");
BLEDescriptor UnlockDescriptor("2901", "Unlock");
BLEDescriptor MACDescriptor("2901", "MAC Address");
BLEDescriptor stopAlarmDescriptor("2901", "Stop Alarm");


bool BLE_activated = true;  //true if the bluetooth is activated
uint32_t tim_connec = 0;    // time in ms or we start to activate the bluetooth following a detection of movement
bool alarmShouldStop = false; // Variable globale pour contrôler l'arrêt de l'alarme



//IMU : LSM6DS3
LSM6DS3 imu(I2C_MODE, 0x6A);  //I2C device address 0x6A
uint32_t timer_imu = millis();
bool MotionBig = false;
bool MotionSmall = false;
bool MotionDetect = false;

// GPS PA1010D
Adafruit_GPS GPS(&Serial1);
bool start_gps = false;
bool position_acquired = false;
uint32_t timer = millis();
#define GPS_WKUP_PIN D8

// SIM800L GSM 2G Module
UART Serial2(D0, D1, NC, NC);
#define SIM800_RST_PIN A5
#define SIM800_DTR_PIN A5
#define TIME_OUT_MS_BLE_ACT 5000  // 300s 300000 times in ms or bluetooth enabled to allow connection following motion detection. (value 5000 for 5s tests)
SIM800L* sim800l;
bool send_position = false;
bool send_move = false;

// Buzzer
const int buzzerPin = D2;
void PulseBuzzer(int repetitions, unsigned long durationOn, unsigned long durationOff);
unsigned long previousMillis = 0;
int currentRep = 0;

//Electroaimant
const int aimantPin = D3;

// Set a threshold to determine a "small" or "big" movement

float SmallMT = 40.0;  //     SmallMotionThreshold
float BigMT = 170.0;   //    BigMotionThreshold

float SmallRT = 40.0;  //     SmallRotationThreshold
float BigRT = 145.0;   //     BigRotationThreshold

//batterie
#define VBAT_ENABLE 14

#define FULL_CHARGE 3.65
#define LOW_BATTERY 3.475
#define LOCKED_BATTERY 3.4

bool isLowBattery = false;
bool isLockedBattery = false;

float getBatteryVoltage();

float MotionData;
float RotationData;

unsigned long StartCoolDown = 0;  //check point for millis aided cooldown

float lastLatitude = 0.0;
float lastLongitude = 0.0;