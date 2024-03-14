# Functional Specifications: SPORTSHIELD Project

## 1. Document Control

### 1.1 Version History

| **Version** | **Date**        | **Author**   | **Description**                        |
| ----------- | --------------- | ------------ | -------------------------------------- |
| 0.1         | 13th March 2024 | Lucas AUBARD | Initial Draft                          |
| 0.2         | 14th March 2024 | Lucas AUBARD | Add Glossary and document informations |

### 1.2 Document Approval

| **Role**          | **Name**        | **Date**        | **Signature** |
| ----------------- | --------------- | --------------- | ------------- |
| Project Manager   | Maxime CARON    | 14th March 2024 |               |
| Program Manager   | Lucas AUBARD    | 14th March 2024 |               |
| Technical Leader  | Alexis LASSELIN | 14th March 2024 |               |
| Software Engineer | Wilfred PORTET  | 14th March 2024 |               |
| Technical Writer  | Paul NOWAK      | 14th March 2024 |               |
| Quality Assurance | Habi CAILLEAU   | 14th March 2024 |               |

<details>
<summary>Table of Contents</summary>

- [Functional Specifications: SPORTSHIELD Project](#functional-specifications-sportshield-project)
  - [1. Document Control](#1-document-control)
    - [1.1 Version History](#11-version-history)
    - [1.2 Document Approval](#12-document-approval)
  - [2. Overview](#2-overview)
    - [2.1 Project](#21-project)
    - [2.2 Client](#22-client)
    - [2.3 Material](#23-material)
      - [Hardware Material:](#hardware-material)
      - [Software:](#software)
  - [3. Use Cases](#3-use-cases)
    - [3.1 Use Case 1: Purchase "SPORTSHIELD" Device](#31-use-case-1-purchase-sportshield-device)
    - [3.2 Use Case 2: Prevent Theft of Snowboard](#32-use-case-2-prevent-theft-of-snowboard)
    - [3.3 Use Case 3: Locate Lost Sport Equipment Using GPS Functionality](#33-use-case-3-locate-lost-sport-equipment-using-gps-functionality)
  - [4. Constraints](#4-constraints)
  - [5. Targeted Features](#5-targeted-features)
  - [6. Acceptance Criteria](#6-acceptance-criteria)
    - [6.1 Must have](#61-must-have)
      - [6.1.1 Battery Optimisation :](#611-battery-optimisation-)
      - [6.1.2 NFC Management :](#612-nfc-management-)
    - [6.2 Should Have](#62-should-have)
      - [6.2.1 Battery low level management](#621-battery-low-level-management)
      - [6.2.2 Manage simultaneous actions](#622-manage-simultaneous-actions)
    - [6.3 Could Have](#63-could-have)
      - [6.3.1 Improve shock detection](#631-improve-shock-detection)
      - [6.3.2 Bluetooth Secure](#632-bluetooth-secure)
      - [6.3.3 Alarm management](#633-alarm-management)
  - [7. Non-Functional Requirements](#7-non-functional-requirements)
  - [8. Assumptions](#8-assumptions)
  - [9. Risks](#9-risks)
  - [10. Testing Ways](#10-testing-ways)
  - [11. Future Improvements](#11-future-improvements)
  - [12. Glossary](#12-glossary)

</details>

## 2. Overview

### 2.1 Project

France is a premier destination for winter tourism, attracting an average of 40 million visitors to its ski resorts annually. The majority of these guests embark on their journey to skiing and snowboarding. While a portion of these visitors opts for rental equipment, a significant number arrive equipped with their personal skis and snowboards, an investment that often ranges from 300€ to over 1000€. CORIS Innovation introduces the SPORTSHIELD project, crafted to enhance the skiing experience, instilling a sense of freedom and confidence among winter sport enthusiasts. SPORTSHIELD is a connected anti-theft device for securing your equipment. It can be used on your skis, snowboard, or any other sports equipment.

### 2.2 Client

The main customer for this project is CORIS Innovation, but it is also indirectly the product's end customer.

### 2.3 Material

Several elements are given for this project:

#### Hardware Material:

| Equipment         | Description                                                                                                                                                                         | Reference               | Brand            |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------- | ---------------- |
| Development board | Ultra-compact, ultra-low-power Bluetooth development board based on the Nordic nRF52840.                                                                                            | Seeed XIAO BLE nRF52840 | Seeed Studio     |
| Battery           | Lithium-ion polymer rechargeable battery.                                                                                                                                           | LP603449                | EEMB             |
| GPS module        | Module utilizes the MediaTek GNSS Chipset MT3333 that support various location and navigation applications, including autonomous GPS, GLONASS, GALILEO, QZSS, SBAS, DGPS, and AGPS. | CD-PA1010D              | CDtop Technology |
| GSM module        | Miniature cellular module which allows for GPRS transmission.                                                                                                                       | SIM800L                 | SIMCom           |
| NFC module        | NFC, RFID antenna.                                                                                                                                                                  | 146236                  | Molex            |

#### Software:

An Arduino code is provided, which is the prototype version of the project's code and contains features already developed.

## 3. Use Cases

### 3.1 Use Case 1: Purchase "SPORTSHIELD" Device

- **Description:** John, a 35-year-old avid skier, is devastated when he discovers one morning that his beloved skis have been stolen from his garage. Determined to prevent such incidents in the future, he decides to invest in a sport protection device. After researching online, he comes across the "SPORTSHIELD" device and decides to purchase it.
- **Actors:**
  - John: A passionate skier who values the safety and security of his equipment.
- **Pre-conditions:**
  - John has access to the internet and a valid payment method.
- **Post-conditions:**
  - John successfully purchases the "SPORTSHIELD" device and tests its effectiveness.
- **Flow of Events:**
  1. John searches online for ski protection devices and reads about various options.
  2. He discovers the "SPORTSHIELD" device through a web search or advertisement.
  3. John reads product descriptions, reviews, and pricing information on the manufacturer's website or an e-commerce platform.
  4. Impressed by the features and positive reviews, John decides to purchase the "SPORTSHIELD" device.
  5. He adds the device to his online shopping cart and proceeds to checkout.
  6. John provides his shipping and payment details.
  7. He confirms the purchase and receives an order confirmation.
  8. Once the "SPORTSHIELD" device arrives, John carefully follows the instructions to install it on his skis.
  9. John tests the device by attempting to remove his skis from their storage location without triggering the alarm.
  10. Satisfied with the device's performance during the test, John feels confident in its ability to protect his skis from theft.
- **Alternate Flows:**
  - If John encounters technical issues during the checkout process, he may contact customer support for assistance.
- **Priority:** Medium

### 3.2 Use Case 2: Prevent Theft of Snowboard

- **Description:** Sarah, a 28-year-old snowboarder, notices a suspicious individual attempting to steal her snowboard from the ski resort's rack. The "Sport Shield" device installed on her snowboard automatically detects the theft attempt and activates the alarm to prevent the theft.
- **Actors:**
  - Sarah Dawson: A 28-year-old snowboard enthusiast who values the safety and security of her equipment. Sarah is an experienced snowboarder who enjoys spending weekends at the ski resort, where she participates in various snowboarding activities.
  - Thief: An opportunistic individual attempting to steal Sarah's snowboard for personal gain.
- **Pre-conditions:**
  - Sarah's snowboard is equipped with the "SPORTSHIELD" device.
  - Sarah is present at the ski resort and within range of her snowboard.
- **Post-conditions:**
  - The thief is unable to steal Sarah's snowboard due to the activation of the "SPORTSHIELD" device.
- **Flow of Events:**
  1. Sarah, enjoying a day of snowboarding at the resort, notices a suspicious individual lurking around the area where her snowboard is parked.
  2. As the thief attempts to remove the snowboard from the rack, the "SPORTSHIELD" device automatically detects the movement and shock.
  3. The device emits three short alarm sounds, alerting Sarah and nearby individuals to the attempted theft.
  4. Startled by the alarm, Sarah rushes to the scene to confront the thief and protect her snowboard.
  5. As the thief applies more force in an attempt to steal the snowboard, causing a significant movement/shock, the "SPORTSHIELD" device activates a louder alarm consisting of five long sound bursts.
  6. Sarah and nearby individuals are immediately alerted to the threat, and the thief, realizing the increased attention drawn to the scene, abandons the theft attempt and flees the area.
  7. Sarah, relieved that her snowboard is safe, checks the device to ensure it is secure and unharmed, grateful for the protection provided by the "SPORTSHIELD" device.
- **Alternate Flows:**
  - If Sarah is unable to intervene, nearby individuals may be alerted by the audible alarm and take action to prevent the theft.
- **Priority:** High

### 3.3 Use Case 3: Locate Lost Sport Equipment Using GPS Functionality

- **Description:** Michael, a 40-year-old enthusiastic skier and outdoor enthusiast, realizes after leaving a restaurant that he has misplaced his skis. He uses the GPS functionality in the "SPORTSHIELD" app to locate his lost equipment.
- **Actors:**
  - Michael: An experienced skier who has been passionate about skiing since his teenage years. He enjoys spending weekends and holidays on the slopes, exploring various ski resorts and backcountry trails. Michael values the safety and security of his equipment and always ensures he has the necessary gear for a successful ski trip.
- **Pre-conditions:**
  - Michael's skis are equipped with the "SPORTSHIELD" device, and the device is connected to the app on his phone.
- **Post-conditions:**
  - Michael successfully locates his lost skis using the GPS functionality in the "SPORTSHIELD" app.
- **Flow of Events:**
  1. After leaving the restaurant, Michael realizes that he cannot find his skis.
  2. He accesses the "SPORTSHIELD" app on his phone, which displays the last known GPS location of his skis.
  3. Michael follows the map displayed in the app to navigate to the location of his skis.
  4. Upon arriving at the location indicated by the GPS, Michael locates his skis and retrieves them.
  5. Michael checks the condition of his skis to ensure they are undamaged and ready for use.
  6. Satisfied that his skis are safe, Michael continues with his skiing activities for the day, grateful for the assistance provided by the "Sport Shield" device.
- **Alternate Flows:**
  - If the GPS signal is weak or unavailable, Michael may need to rely on other methods to locate his skis, such as asking nearby individuals or contacting the restaurant staff.
- **Exceptions:**
  - In rare cases, the GPS functionality may experience inaccuracies due to signal interference or technical issues.
- **Priority:** Medium

## 4. Constraints

The "SPORTSHIELD" device and app offer valuable features to enhance the security and protection of sport equipment. However, several constraints must be considered to ensure the successful implementation and utilization of the product:

- **Battery Life:** The device's battery life is limited and must be optimized to ensure long-term functionality without frequent recharging.
- **Technical Compatibility:** The device and app must be compatible with various types of sport equipment and operating systems to accommodate a wide range of users.
- **User Interface:** The app's user interface should be intuitive and user-friendly, providing easy access to essential features and settings.
- **Cost:** The cost of the device and app should be reasonable, making it accessible to a broad audience of sport enthusiasts.
- **Regulatory Compliance:** The device and app must comply with relevant regulations and standards governing the use of wireless communication and tracking technologies.

## 5. Targeted Features

The "SPORTSHIELD" project aims to deliver the following key features to meet the needs and expectations of sport enthusiasts:

- **Long Battery Life:** The device features a rechargeable battery with extended battery life, ensuring reliable operation without frequent recharging.
- **Anti-Theft Protection:** The device detects unauthorized movement or tampering of sport equipment and activates an alarm to deter theft.
- **GPS Tracking:** The device is equipped with GPS functionality, allowing users to track the location of their sport equipment in real-time using a mobile app.
- **Bluetooth Connectivity:** The device communicates with a mobile app via Bluetooth connection, enabling users to configure settings and receive notifications.
- **User-Friendly App:** The mobile app provides a user-friendly interface for accessing device settings, tracking sport equipment, and receiving alerts.
- **NFC Integration:** The device integrates Near Field Communication (NFC) technology, allowing users to activate and deactivate anti-theft protection using NFC cards or smartphones.

## 6. Acceptance Criteria

Acceptance criteria are a detailed and measurable list of conditions that must be met for a project element to be considered complete and acceptable. They play an essential role in communicating expectations between stakeholders and in ensuring the quality of the final product.

### 6.1 Must have

These are the critical acceptance criteria that absolutely must be met for the project to be considered successful. They represent the core functionalities or features without which the project cannot proceed. These criteria should be the highest priority and receive the most attention during development and testing. They are composed of :

#### 6.1.1 Battery Optimisation :

1. Improve energy efficiency of the system:

   - Components must be activated only when necessary to conserve battery power.

2. Increase the battery lifespan:

   - Implement measures to limit battery charging to a maximum of 80% of its maximum capacity (Vmax) to prolong battery lifespan.

   - Enforce a minimum battery charge threshold of 20% to prevent deep discharge cycles that could degrade the battery's health over time.

#### 6.1.2 NFC Management :

1. NFC activation of anti-theft system and cable unlocking:

   - Users should be able to activate and deactivate the anti-theft system and unlock the cable using NFC technology with Bluetooth.

2. Integration with Bluetooth via smartphone:

   - The system should seamlessly integrate with the Blutooth, allowing users to manage device functions through their smartphones.

### 6.2 Should Have

These acceptance criteria are important for the overall success of the project but are not as critical as the "Must Have" criteria. They represent functionalities or features that are highly desirable and should be included if possible. However, the project can still move forward if some of these criteria are not fully met.

#### 6.2.1 Battery low level management

- Management of a low battery situation:

  - Ensure that critical safety features such as ski securing mechanisms are prioritized over non-essential functions when the battery is low.

  - Implement fail-safe measures to prevent unsafe situations, such as ensuring that the electromagnet cannot be powered to release the cable when the battery is critically low.

#### 6.2.2 Manage simultaneous actions

1. Alarm ringing while sending HTTP notification to the server:

   - The system should allow the alarm to continue ringing while simultaneously sending a HTTP notification to the server.

2. Improved management of interruptions:

   - Implement better management of interruptions to ensure that simultaneous actions do not interfere with each other.

   - Prioritize critical actions such as alarm ringing and HTTP notifications, while appropriately handling other interruptions to maintain system functionality.

### 6.3 Could Have

These acceptance criterias are optional and represent functionalities or features that would enhance the project but are not essential for its success. They can be included if time and resources permit, but their absence would not significantly impact the project's overall outcome.

#### 6.3.1 Improve shock detection

- Explore and implement advanced algorithms to enhance the accuracy and sensitivity of shock detection.

#### 6.3.2 Bluetooth Secure

- Implement stronger encryption protocols for Bluetooth communication to ensure secure data transmission between devices.
- Allow users to create a whitelist of trusted Bluetooth devices that are permitted to connect to the system.

#### 6.3.3 Alarm management

- Implement the option for users to stop the alarm manually, even if the ringing cycle is not finished. This feature provides users with more control over the alarm system, allowing them to silence the alarm promptly if necessary.

## 7. Non-Functional Requirements

Description of the performance,reliability, or other non-functional aspects expected from the solution

- **User friendly** :

The anti-theft system must offer an intuitive user interface and a quick locking process, minimizing the steps required to activate and deactivate protection. Given that the primary users will be mountain vacationers, regulars and locals, who want to quickly secure their winter sports equipment during their breaks, the user experience must be fluid and frictionless. It's imperative that users can secure their skis or snowboard with confidence and return to their activities without undue concern for the safety of their equipment.

- **Energy savings and autonomy** :

The anti-theft system must be optimized for minimum energy consumption, allowing continuous use over a period of one week without the need for recharging. This means that the device must be able to operate for 6 hours a day in active mode and 18 hours in standby mode. This autonomy enables users to enjoy their mountain vacations without the worry of recharging the device, ensuring an uninterrupted user experience and constant equipment security.

- **Compatibility**:

The system should be compatible with different smartphone models and versions of mobile operating systems to ensure a consistent user experience.

- **Reliability**:

The system must operate reliably and consistently, with effective management of low-battery situations to avoid failure due to power loss.

- **Performance**:

The system should be able to handle anti-theft activation/deactivation and cable unlocking quickly, with minimal response time to avoid delaying the user.

- **Availability**:

The system must be operational and accessible via NFC and the SportShield application at all times, guaranteeing close to 100% availability. guidelines.

## 8. Assumptions

| **Assumption**                                  | **Impact**                                                                                                    | **Mitigation**                                                                                         |
| :---------------------------------------------- | :------------------------------------------------------------------------------------------------------------ | :----------------------------------------------------------------------------------------------------- |
| Implementation of energy-efficient strategies   | These strategies could extend the battery life and enhance the user experience                                | Making research about battery alimentation                                                             |
| Electronic measures requirements                | To check if the device respect the expected nominal voltage, we need to make some measurements                | We should use a multimeter, and perhaps a breadboard for electronic tests                              |
| Sleep mode triggering at low battery            | When it reaches 20% of battery, it could enter in a sleep mode similar to cellphones to economize the battery | Testing about sleep mode and checking how much time the battery can handle                             |
| Simultaneous actions could consume more battery | Allowing a device to do several actions at the time might increase the battery consumption                    | Simultaneous actions might be limited, and we should monitor the tension depending on the actions used |
| New HTTP server creation                        | We have to get used to send HTTPs requests to get familiarized with the base device                           | We should train ourselves sending and receiving HTTPs requests with simple programs                    |
| NFC integration improving interactivity         | The user interaction with the device and the system's usability will be enhanced                              | Make sure the customer will be able to use the NFC card without trouble                                |

## 9. Risks

| **Risk**                          | **Impact**                                                                                                                                                     | **Mitigation**                                                                                                                  |
| :-------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------ |
| Battery insufficient power        | The battery might not be able to power up the microprocessor implemented with the new code                                                                     | Study what components are used for the code, compare with different batteries, and choose the one most adapted to the situation |
| Obsolete battery                  | After an excessive use, the LiPo battery won't have any voltage anymore to power up our device                                                                 | Simply take another LiPo battery                                                                                                |
| Battery lifespan inaccuracy       | A bad management of the lifespan can lead to premature battery degradation or failure                                                                          | Checking and monitoring the evolution of the first battery's voltage.                                                           |
| Alarm manual deactivation failure | Depending on some circumstances, the HTTPs requests sent by the user could have trouble being detected by the device, hindering remote monitoring and response | Proceeding with tests of sending HTTPs requests and/or improving the sending speed                                              |
| Alarm management conflicts        | The alarm interruptions and conflicts could lead to system instability or inconsistent behavior                                                                 | Adding limitations of alarm desactivation, like a waiting time                                                                   |
| NFC smartphones brands issues     | The user could experience some issues with the NFC communication due to using a different smartphone                                                           | Making the NFC buffer type always the same regardless of the smartphone type                                                    |
| NFC malfunctions                  | The NFC cards can provoke software bugs, affection activation/desactivations, and potentially unlock the cable at the wrong time                                | Creating a valuable test environment for NFC communication                                                                      |
| Data privacy breaches             | Through NFC communication, private user data could be exposed due to a wrongful use of a NFC card                                                              | The NFC cards should just send information to the device instead of receiving.                                                  |

## 10. Testing Ways

Below are the testing methods that will be employed to ensure the robustness and reliability of the system:

1. **Unit Testing**: This phase will involve testing each system's module in isolation to verify its functionality.

   _Why:_ Unit testing is essential to identify and address any defect in the individual components before they are integrated into the system.

   _Example:_ We will conduct unit tests by activating the alarm system and verifying if the alarm responds appropriately.

2. **Integration Testing**: Integration testing will focus on validating the interactions between different modules when they are integrated into the system.

   _Why:_ Integration testing is crucial to ensure that the components work together as intended and that the system's functionality is not compromised.

   _Example:_ Integration tests will involve connecting the alarm with the sensor and confirming if the alarm is triggered upon detection of a strong shock.

3. **System Testing**: This comprehensive testing phase evaluates the system as a whole to ensure all components work together seamlessly.

   _Why:_ System testing is essential to validate the system's overall functionality and performance, including user interactions and system responses.

   _Example:_ System tests will include subjecting the sensor to a strong shock and verifying if the alarm is triggered while also checking if the system sends an alert to the user.

4. **Regression Testing**: Whenever changes are made to the system, regression testing will be performed to ensure that existing functionalities are not adversely affected.

   _Why:_ Regression testing is necessary to confirm that new changes do not introduce defects or issues that impact the system's existing functionality.

   _Example:_ After modifying the alarm system, regression tests will be conducted to confirm that the alarm still functions correctly in response to sensor triggers.

5. **Performance Testing**: This phase evaluates the system's performance under various conditions to ensure optimal operation.

   _Why:_ Because the system's performance is a priority to the client, performance testing is essential to ensure that the system can handle different scenarios and loads.

   _Example:_ Performance tests will assess the system's responsiveness under normal and low temperature to ensure consistent performance.

6. **Security Testing**: Security testing aims to identify vulnerabilities and ensure the system is resilient against unauthorized access or attacks.

   _Why:_ Security testing is critical to safeguard the system from potential threats and breaches.

   _Example:_ Security tests will try to bypass the system's security measures to modify or disable the alarm, and verify if the system can protect against such attempts.

By employing these testing methodologies, we aim to deliver a reliable and robust SPORTSHIELD system that meets the highest standards of performance, security, and user satisfaction.

## 11. Future Improvements

The SPORTSHIELD project is designed to provide essential anti-theft and tracking functionalities for sport equipment. However, there are several areas for future improvements and enhancements to further elevate the system's capabilities and user experience:

1. **Enhanced Shock Detection**: Implement advanced algorithms and sensors to improve the accuracy and sensitivity of shock detection, allowing the system to detect and respond to subtle movements or impacts.
2. **Bluetooth Secure**: Integrate stronger encryption protocols for Bluetooth communication to ensure secure data transmission between devices, enhancing the system's security and privacy.
3. **Led Light Indicators**: Integrate LED light indicators on the device to provide visual feedback to users, such as battery status, alarm activation, and system status.
4. **Secure Charge Cable**: Improve the charge cable to be sure that an unauthorized person cannot unlock the cable and steal the equipment by using his computer to change the code in the device.
5. **Alarm Management**: Implement the option for users to stop the alarm manually, even if the ringing cycle is not finished. This feature provides users with more control over the alarm system, allowing them to silence the alarm promptly if necessary.

## 12. Glossary

- **Bluetooth:** A wireless technology standard used for exchanging data over short distances between devices.
- **GPS (Global Positioning System):** A satellite-based navigation system that provides location and time information anywhere on or near the Earth.
- **NFC (Near Field Communication):** A set of communication protocols that enable two electronic devices, one of which is usually a portable device such as a smartphone, to establish communication by bringing them within 4 cm (1.6 in) of each other.
- **RFID (Radio Frequency Identification):** A technology that uses radio waves to identify objects or people automatically.
- **GPRS (General Packet Radio Service):** A packet-oriented mobile data service on the 2G and 3G cellular communication system's global system for mobile communications (GSM).
