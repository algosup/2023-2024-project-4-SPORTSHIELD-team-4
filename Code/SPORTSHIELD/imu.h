/*
  This file contains the functions and setup functions for the IMU accelerometer module
*/

#pragma once

#ifndef GLOBALVAR_H
  #include "globalVar.h"
#endif

//------------- FUNCTIONS ------------------------------

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