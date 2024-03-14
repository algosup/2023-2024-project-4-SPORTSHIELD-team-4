# Functional Specification: SPORTSHIELD Project

## 1. Document Control

### 1.1 Version History

| **Version** | **Date**        | **Author**   | **Description** |
| ----------- | --------------- | ------------ | --------------- |
| 0.1         | 13th March 2024 | Lucas AUBARD | Initial Draft   |
| 0.2         | 14th March 2024 | Lucas AUBARD | Add Glossary    |

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

- [Functional Specification: SPORTSHIELD Project](#functional-specification-sportshield-project)
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
      - [6.1.1 Battery Optimization](#611-battery-optimization)
      - [6.1.2 NFC Management](#612-nfc-management)
    - [6.2 Should Have](#62-should-have)
      - [6.2.1 Battery Low-Level Management](#621-battery-low-level-management)
      - [6.2.2 Manage Simultaneous Actions](#622-manage-simultaneous-actions)
    - [6.3 Could Have](#63-could-have)
      - [6.3.1 Improve Shock Detection](#631-improve-shock-detection)
      - [6.3.2 Bluetooth Secure](#632-bluetooth-secure)
      - [6.3.3 Alarm Management](#633-alarm-management)
  - [7. Non-Functional Requirements](#7-non-functional-requirements)
  - [8. Assumptions](#8-assumptions)
  - [9. Risks](#9-risks)
  - [10. Testing Ways](#10-testing-ways)
  - [11. Glossary](#11-glossary)

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

- **Anti-Theft Protection:** The device detects unauthorized movement or tampering of sport equipment and activates an alarm to deter theft.
- **GPS Tracking:** The device is equipped with GPS functionality, allowing users to track the location of their sport equipment in real-time using a mobile app.
- **Bluetooth Connectivity:** The device communicates with a mobile app via Bluetooth connection, enabling users to configure settings and receive notifications.
- **Long Battery Life:** The device features a rechargeable battery with extended battery life, ensuring reliable operation without frequent recharging.
- **User-Friendly App:** The mobile app provides a user-friendly interface for accessing device settings, tracking sport equipment, and receiving alerts.

## 6. Acceptance Criteria

### 6.1 Must have

#### 6.1.1 Battery Optimization

- The device's battery life must exceed 30 days under normal usage conditions.

#### 6.1.2 NFC Management

- The device must support NFC pairing for easy setup and configuration.

### 6.2 Should Have

#### 6.2.1 Battery Low-Level Management

- The app must notify users when the device's battery level is low, indicating the need for recharging.

#### 6.2.2 Manage Simultaneous Actions

- The device must handle multiple simultaneous actions, such as tracking location while detecting movement.

### 6.3 Could Have

#### 6.3.1 Improve Shock Detection

- The device could enhance shock detection sensitivity to detect subtle movements indicative of tampering.

#### 6.3.2 Bluetooth Secure

- The device could implement additional security measures for Bluetooth communication to prevent unauthorized access.

#### 6.3.3 Alarm Management

- The app could allow users to customize alarm settings, such as volume and duration.

## 7. Non-Functional Requirements

The "SPORTSHIELD" device and app must meet the following non-functional requirements to ensure optimal performance and user satisfaction:

- **Reliability:** The device and app must operate reliably under various environmental conditions, including extreme temperatures and physical stress.
- **Security:** The device and app must implement robust security measures to protect user data and prevent unauthorized access.
- **Scalability:** The device and app must be scalable to accommodate future updates and expansions, including additional features and device compatibility.
- **Performance:** The device and app must deliver high performance with minimal latency, ensuring responsive user interaction and real-time tracking capabilities.
- **Usability:** The device and app must be user-friendly, with intuitive interfaces and clear instructions for setup and operation.
- **Accessibility:** The device and app must be accessible to users with disabilities, complying with relevant accessibility standards and guidelines.

## 8. Assumptions

- Users have basic knowledge of operating smartphones and mobile applications.
- The "SPORTSHIELD" device is compatible with a wide range of sport equipment, including skis, snowboards, bicycles, and hiking gear.
- The GPS functionality of the "SPORTSHIELD" device relies on satellite signals and may experience limitations in areas with poor signal reception or obstructed views of the sky.

## 9. Risks

- Technical challenges may arise during the development and implementation of GPS tracking and anti-theft functionalities.
- The device's battery life may be shorter than expected under certain usage conditions, leading to user dissatisfaction.
- Regulatory changes or legal requirements may impact the deployment and operation of the "SPORTSHIELD" device and app in specific regions or jurisdictions.

## 10. Testing Ways

The "SPORTSHIELD" device and app will undergo rigorous testing to ensure they meet the specified requirements and performance standards. Testing methods will include:

- Functional Testing: Verifying that all features and functionalities perform as expected under normal and edge case scenarios.
- Usability Testing: Evaluating the user interface and experience to ensure ease of use and intuitive operation.
- Performance Testing: Assessing the device and app's performance metrics, including battery life, responsiveness, and tracking accuracy.
- Security Testing: Identifying and addressing potential vulnerabilities and security risks to protect user data and prevent unauthorized access.
- Compatibility Testing: Testing the device and app across various platforms, devices, and operating systems to ensure broad compatibility and interoperability.
- Regulatory Compliance Testing: Ensuring that the device and app comply with relevant regulations and standards governing wireless communication, tracking technologies, and user privacy.

## 11. Glossary

- **Bluetooth:** A wireless technology standard used for exchanging data over short distances between devices.
- **GPS (Global Positioning System):** A satellite-based navigation system that provides location and time information anywhere on or near the Earth.
- **NFC (Near Field Communication):** A set of communication protocols that enable two electronic devices, one of which is usually a portable device such as a smartphone, to establish communication by bringing them within 4 cm (1.6 in) of each other.
- **RFID (Radio Frequency Identification):** A technology that uses radio waves to identify objects or people automatically.
- **GPRS (General Packet Radio Service):** A packet-oriented mobile data service on the 2G and 3G cellular communication system's global system for mobile communications (GSM).
