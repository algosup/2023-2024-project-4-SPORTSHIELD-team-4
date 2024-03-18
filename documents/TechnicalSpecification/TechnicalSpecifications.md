# Technical Specifications

---

## Table of Contents

<details>
<summary><b>Click to expand</b></summary>

- [Technical Specifications](#technical-specifications)
  - [Table of Contents](#table-of-contents)
  - [I. Introduction](#i-introduction)
    - [1. Overview](#1-overview)
    - [2. Context](#2-context)
    - [3. Goals and Objectives](#3-goals-and-objectives)
    - [4. Out of Scope](#4-out-of-scope)
    - [7. Future Goals](#7-future-goals)
    - [8. Assumptions](#8-assumptions)
  - [II. Hardware](#ii-hardware)
    - [1. Development Board](#1-development-board)
    - [2. Battery](#2-battery)
    - [3. GPS Module](#3-gps-module)
    - [4. GSM Module](#4-gsm-module)
    - [5. NFC Module](#5-nfc-module)
    - [6. Electromagnet](#6-electromagnet)
    - [7. Piezoelectric Buzzer](#7-piezoelectric-buzzer)
    - [8 . Electronic Configuration](#8--electronic-configuration)
  - [III. Solutions](#iii-solutions)
    - [1. Current Product](#1-current-product)
      - [A. Pros](#a-pros)
      - [B. Cons](#b-cons)
    - [2. Proposed Solutions](#2-proposed-solutions)
      - [A. Battery Improvement](#a-battery-improvement)
        - [a. Battery Management](#a-battery-management)
        - [b. Battery Life Enhancement](#b-battery-life-enhancement)
      - [B. NFC Integration](#b-nfc-integration)
      - [C. Simultaneous Actions Handling](#c-simultaneous-actions-handling)
      - [D. Bluetooth Security Enhancement](#d-bluetooth-security-enhancement)
      - [E. Alarm Control Enhancement](#e-alarm-control-enhancement)
    - [3. Test Plan](#3-test-plan)
    - [4. Monitoring and Alerting Plan](#4-monitoring-and-alerting-plan)
    - [5. Rollout Plan](#5-rollout-plan)
    - [6. Rollback Plan](#6-rollback-plan)
    - [7. Alternate Solutions](#7-alternate-solutions)
  - [IV. Further Considerations](#iv-further-considerations)
    - [1. Constraints and Impact](#1-constraints-and-impact)
    - [2. Considerations](#2-considerations)
      - [A. Security Considerations](#a-security-considerations)
      - [B. Privacy Considerations](#b-privacy-considerations)
      - [C. Risks](#c-risks)
  - [V. Work](#v-work)
    - [1. Work Estimates and Timelines](#1-work-estimates-and-timelines)
    - [2. Prioritization](#2-prioritization)
    - [3. Milestones](#3-milestones)
    - [4. Future Work](#4-future-work)
  - [VI. Glossary](#vi-glossary)

</details>

---

## I. Introduction

### 1. Overview

A French company named CORIS Innovation asked us to improve their product named SPORTSHIELD. The product is a device that serves as a lock for all sorts of sports equipment. The device is connected to a mobile application that allows the user to lock and unlock the equipment. The company has been facing a lot of issues with the current solution and has asked us to come up with a new solution that will solve the issues they are facing. The stakeholders are the company and the users of the product.

### 2. Context

The decision for the company to seek improvement for their product stems from numerous issues within the current solution. These include limitations such as the device's autonomy, the lack of user notification during alarm activation, and the inability to halt the alarm once the ringing cycle initiates.

### 3. Goals and Objectives

Fortunately, the company has provided us with a comprehensive list of requirements for the new solution:

- Ensure the device maintains a battery life of at least 7 days, allowing for up to 6 hours of active use per day.
- Implement NFC functionality for device unlocking.
- Introduce multi-action capability, such as sending user notifications when the alarm activates.
- Enhance security protocols for accessing key system features like lock/unlock and alarm management.

### 4. Out of Scope

Several requirements fall outside the scope of this project and will not be addressed:

- Implementing LED blinking to indicate device functionality.
- Addressing security concerns related to charging. (Blocking the insertion of code into the device's firmware during charging.)
- Further enhancements to shock detection.

### 7. Future Goals

Certain requirements have been identified for future iterations:

- Securing the Bluetooth connection between the device and the mobile application.
- Enhancing alarm management to allow users to halt the alarm once the ringing cycle commences.

### 8. Assumptions

We are operating under the following assumptions:

- All essential hardware and software components required for development and testing will be readily available.
- Access to the current solution will be granted to facilitate understanding of its functionality and encountered issues.
- The company will furnish us with the requisite documentation and assistance to comprehend the current solution and its associated challenges.

## II. Hardware

The SPORTSHIELD device comprises various hardware components carefully selected for optimal performance and functionality:

### 1. Development Board

- **Description:** An ultra-compact, ultra-low-power Bluetooth development board based on the Nordic nRF52840.
- **Reference:** Seeed XIAO BLE nRF52840
- **Brand:** Seeed Studio

![Development Board](./Images/XiaoBLE.png)

### 2. Battery

- **Description:** Lithium-ion polymer rechargeable battery.
- **Reference:** LP603449
- **Brand:** EEMB

![Battery](./Images/Battery.png)

### 3. GPS Module

- **Description:** Utilizes the MediaTek GNSS Chipset MT3333, supporting various location and navigation applications, including autonomous GPS, GLONASS, GALILEO, QZSS, SBAS, DGPS, and AGPS.
- **Reference:** CD-PA1010D
- **Brand:** CDtop Technology

![GPS Module](./Images/ModuleGPS-removebg-preview.png)

### 4. GSM Module

- **Description:** A miniature cellular module enabling GPRS transmission.
- **Reference:** SIM800L
- **Brand:** SIMCom

![GSM Module](./Images/Sim.png)

### 5. NFC Module

- **Description:** NFC and RFID antenna.
- **Reference:** 146236
- **Brand:** Molex

![NFC Module](./Images/NFCReader.png)

### 6. Electromagnet

- **Description:** Electromagnet with specifications of 12V and 500mA.
- **Dimensions:** 2.7 x 1.6 x 1.3 cm

![Electromagnet](./Images/Electromagnet.png)

### 7. Piezoelectric Buzzer

- **Description:** Piezoelectric buzzer with oscillator control circuit.
- **Specifications:** Operates at 12V, producing a sound intensity of approximately 90-100 dB.

![Piezoelectric Buzzer](./Images/Buzzer.png)

### 8 . Electronic Configuration

This is how the electronic configuration of the device looks like:

![Electronic Configuration](./Images/ElectronicConfiguration.png)

## III. Solutions

### 1. Current Product

The current solution is still in the development phase and encompasses the following features:

- The device functions as a lock for various sports equipment.
- It is paired with a mobile application that enables users to lock and unlock the equipment remotely.
- The device typically has a battery life of 3 days under optimal conditions.
- Bluetooth connectivity facilitates communication between the device and the mobile application.
- An alarm is triggered upon detecting a shock, emitting 3 light sounds for minor shocks and 5 long high sounds for significant shocks.
- Locking and unlocking of the device can be performed via the mobile application.
- The mobile application provides geo-location functionality for tracking the device's location.

#### A. Pros

- Provides remote locking and unlocking capabilities, enhancing convenience for users.
- Offers shock detection functionality to alert users of potential tampering or unauthorized access.
- Incorporates geo-location features to assist users in tracking misplaced or stolen equipment.

#### B. Cons

- Limited battery life may necessitate frequent recharging, potentially leading to user inconvenience.
- Reliance on Bluetooth connectivity may result in connectivity issues or limitations in range.
- The alarm system's simplicity may not adequately address all potential security concerns or user preferences.

### 2. Proposed Solutions

#### A. Battery Improvement

To address the challenge of limited battery life, we propose the following enhancements:

**Objective**: Extend the device's battery life to 7 days with up to 6 hours of active use per day by optimizing power consumption and implementing efficient battery management techniques.

- **Acceptance Criteria**:
  - The device's battery life will be extended to 7 days under optimal conditions, allowing for up to 6 hours of active use per day.
  - Charging will be restricted to 80% of the battery's capacity to enhance longevity.

##### a. Battery Management

- **Implementation Strategy**:
  One of the most consuming parts of the device is the GPS module. That's why, instead of sending the GPS data every 5 minutes, we send it only if the device feels a shock. This will allow us to save a lot of battery.

  ![GPS Management](./Images/GPSFlow.png)

  If we wanted to save even more battery, once we're in low battery mode, we could stop the GPS module but it would mean that the device would not be able to send its location to the mobile application.

##### b. Battery Life Enhancement

- **Implementation Strategy**:
  - Employ efficient battery management algorithms to regulate power usage effectively.
  - Implement a charging limit of 80% of the battery's capacity to prolong its lifespan.

![Battery Manager](./Images/BatteryFlow.png)

#### B. NFC Integration

To expand the device's functionality, we propose integrating NFC capabilities to facilitate device locking and unlocking:

**Objective**: Incorporate NFC functionality to enable users to lock/unlock the device using their mobile phones.

- **Implementation Approach**:

  - Utilize a library compatible with the device's development board to enable NFC functionality. This will allow the device to communicate with the mobile application using NFC.
    Unfortunately, we don't have the library that we will use to implement the NFC functionality.

- **Acceptance Criteria**:
  - The device will support locking/unlocking via the mobile application using NFC functionality.
  - NFC functionality will be validated using a smartphone's NFC tag for testing purposes.

#### C. Simultaneous Actions Handling

**Objective**: Develop a system for managing simultaneous actions, with a specific focus on notifying the user when the alarm is triggered.

- **Implementation Strategy**:

  - Instead of doing the actions in parallel, we will do them in series, allowing us to save a lot of battery and to avoid the device being overwhelmed by the actions.

  Here is the flow of the actions:

  ![Simultaneous Actions](./Images/SimultaneousActionsFlow.png)

- **Acceptance Criteria**:
  - The system effectively identifies and manages simultaneous actions, especially the activation of the alarm.
  - Users receive timely notifications on their mobile devices when the alarm is triggered.
  - The notification system operates efficiently, delivering real-time alerts without delays.

#### D. Bluetooth Security Enhancement

**Objective**: Strengthen the security protocols governing Bluetooth connectivity between the device and the mobile application.

- **Implementation Approach**:

  - Implement robust encryption protocols to secure data transmission over Bluetooth.
  - Utilize secure pairing mechanisms to establish a trusted connection between the device and the mobile application.
  - Integrate authentication measures to validate the identities of the device and the mobile application during pairing.

- **Acceptance Criteria**:

  - Data transmitted over Bluetooth will be encrypted to ensure confidentiality and integrity.
  - Secure pairing mechanisms will prevent unauthorized devices from connecting to the SPORTSHIELD device.
  - Authentication measures will successfully validate the identities of the device and the mobile application, mitigating the risk of unauthorized access.

  Unfortunately, we don't have the actual implementation of the Bluetooth security, leading to the fact that we can't provide a flow for this feature.

#### E. Alarm Control Enhancement

**Objective**: Improve the alarm management system to enable users to stop the alarm once the ringing cycle begins.

- **Implementation Strategy**:

  - Develop a mechanism allowing users to halt the alarm once activated, as an example, if the device is moved accidentally and starts ringing. The user will have two ways to stop the alarm:
    - The first way is to stop the alarm using the mobile application, Bluetooth. This will allow the user to stop the alarm from a distance.
    - The second way is to stop the alarm using the NFC functionality. This will allow the user to stop the alarm without the need to run the mobile application.

  You can see the flow of the alarm management below:

  ![Alarm Management](./Images/AlarmManagementFlow.png)

- **Acceptance Criteria**:
  - Users can stop the alarm once the ringing cycle starts, either through the mobile application or the device itself.

### 3. Test Plan

The following tests will be conducted to ensure that the new solution meets the user requirements:

- **Battery Life Improvement & Low Level Management**:

  - Unit tests will be conducted to verify the effectiveness of power consumption optimization and battery management algorithms.
  - Integration tests will be performed to assess the device's battery life under various usage scenarios.
  - Quality assurance (QA) testing will be carried out to validate the device's battery life and charging management.

- **NFC Functionality**:

  - Unit tests will be conducted to evaluate the implementation of NFC functionality for device locking and unlocking.
  - Integration tests will be performed to ensure seamless integration between the device and the mobile application for NFC-based locking/unlocking.
  - QA testing will be carried out to validate the device's NFC functionality and its compatibility with the mobile application.

- **Simultaneous Actions Management**:

  - Unit tests will be conducted to verify the system's ability to detect and manage simultaneous actions, particularly the activation of the alarm.
  - Integration tests will be performed to assess the notification system's performance and real-time alert delivery.
  - QA testing will be carried out to validate the system's ability to manage simultaneous actions and deliver timely notifications to users.

- **Bluetooth Security**:
  - Unit tests will be conducted to evaluate the implementation of encryption protocols, secure pairing mechanisms, and authentication measures for Bluetooth security.
  - Integration tests will be performed to assess the security of data transmission and the establishment of trusted connections between the device and the mobile application.
  - QA testing will be carried out to validate the effectiveness of Bluetooth security measures and their ability to prevent unauthorized access.
- **Alarm Control Enhancement**:
  - Unit tests will be conducted to verify the implementation of the alarm management system, including the ability to stop the alarm once the ringing cycle begins.
  - Integration tests will be performed to assess the user's ability to stop the alarm using the Bluetooth and NFC functionality.
  - QA testing will be carried out to validate the effectiveness of the alarm control enhancement and the user's ability to halt the alarm.

### 4. Monitoring and Alerting Plan

The following monitoring and alerting plan will be implemented to ensure the health and observability of the new solution:

- **Metrics for Health Measurement**:

  - Battery life: Monitoring the device's battery life and charging status to ensure optimal performance.
  - NFC functionality: Observing the usage and performance of NFC functionality for device locking and unlocking.
  - Simultaneous actions management: Tracking the system's ability to detect and manage simultaneous actions, particularly the activation of the alarm.
  - Bluetooth security: Monitoring the security of data transmission and the establishment of trusted connections between the device and the mobile application.

- **Alerting Plan**:

  - Battery life: Alerts will be triggered when the device's battery life falls below a predefined threshold, indicating the need for recharging.
  - NFC functionality: Alerts will be generated in case of NFC functionality issues, such as failure to lock/unlock the device using NFC.
  - Simultaneous actions management: Alerts will be raised if the system fails to detect and manage simultaneous actions, particularly the activation of the alarm.
  - Bluetooth security: Alerts will be triggered in the event of security breaches or unauthorized access attempts over Bluetooth.

### 5. Rollout Plan

- **Deployment Architecture**:

  - The new solution will be deployed using a phased roll-out approach, allowing for gradual implementation and testing of each feature.
  - Deployment environments will include development, testing, staging, and production environments to facilitate thorough testing and validation.

- **Phased Roll-out Plan**:
- **Phase 1**:
  - Battery life improvement & low-level management: Implement power consumption optimization and battery management algorithms.
  - NFC functionality: Integrate NFC functionality for device locking and unlocking.
- **Phase 2**:
  - Simultaneous actions management: Develop a system for managing simultaneous actions, particularly the activation of the alarm.
  - Bluetooth security: Enhance the security protocols governing Bluetooth connectivity between the device and the mobile application.

Each phase will involve thorough testing and validation before proceeding to the next phase.

To communicate with the client about the different phases, we will use the resume summary of each feature. This will allow the client to understand the progress of the project and to give feedback on the different features.

### 6. Rollback Plan

<!--
Detailed and specific liabilities
Plan to reduce liabilities
Plan to describe how to prevent other components, services, and systems from being affected
-->

In the event of any issues or failures during the roll-out of the new solution, the following rollback plan will be implemented:

- **Liabilities**:

  - Battery life improvement & low-level management: Potential issues may arise with power consumption optimization and battery management algorithms, leading to reduced battery life or charging problems.
  - NFC functionality: Failures in the implementation of NFC functionality may result in issues with device locking/unlocking using NFC.
  - Simultaneous actions management: System failures may occur in detecting and managing simultaneous actions, particularly the activation of the alarm.
  - Bluetooth security: Security breaches or unauthorized access attempts over Bluetooth may pose significant liabilities.

- **Liability Reduction Plan**:

  - Battery life improvement & low-level management: Thorough testing and validation will be conducted to identify and address any issues related to power consumption optimization and battery management algorithms.
  - NFC functionality: Extensive testing will be carried out to ensure the seamless integration of NFC functionality for device locking and unlocking.
  - Simultaneous actions management: Rigorous testing and validation will be performed to verify the system's ability to detect and manage simultaneous actions, particularly the activation of the alarm.
  - Bluetooth security: Comprehensive testing and validation will be conducted to identify and address any security breaches or unauthorized access attempts over Bluetooth.

### 7. Alternate Solutions

<!--
Summary statement for each alternative solution
Pros and cons for each alternative
Reasons why each solution couldn’t work
Ways in which alternatives were inferior to the proposed solution
Migration plan to next best alternative in case the proposed solution falls through
-->

The following alternate solutions were considered but ultimately deemed inferior to the proposed solution:

- **Alternative Solution 1**:

  - **Summary**: Implement a more powerful battery to extend the device's battery life.
  - **Pros**: Potential for significantly extended battery life.
  - **Cons**: Increased cost and complexity, the potential impact on device size and weight.
  - **Reasons**: The proposed solution offers a more cost-effective and efficient approach to extending battery life without significant changes to the device's hardware.
  - **Migration Plan**: If the proposed solution falls through, the next best alternative would be to explore more powerful battery options and their impact on the device's design and performance.

- **Alternative Solution 2**:

  - **Summary**: Develop a separate device for NFC functionality, eliminating the need to integrate it into the SPORTSHIELD device.
  - **Pros**: Simplified device design and development, potential for reduced cost and complexity.
  - **Cons**: Additional hardware and maintenance requirements, potential impact on user experience and convenience.
  - **Reasons**: The proposed solution offers a more integrated and user-friendly approach to incorporating NFC functionality into the SPORTSHIELD device, enhancing its capabilities and convenience for users.
  - **Migration Plan**: If the proposed solution falls through, the next best alternative would be to explore the development of a separate device for NFC functionality and its integration with the SPORTSHIELD device.

- **Alternative Solution 3**:

  - **Summary**: Focus on enhancing the device's shock detection capabilities to address security concerns.
  - **Pros**: Improved security and tamper detection, potential for enhanced user confidence.
  - **Cons**: Limited impact on battery life and user convenience, potential for increased complexity and cost.
  - **Reasons**: The proposed solution offers a more comprehensive and user-centric approach to addressing multiple user requirements, including battery life improvement, NFC functionality, and simultaneous actions management.
  - **Migration Plan**: If the proposed solution falls through, the next best alternative would be to explore the enhancement of the device's shock detection capabilities and their impact on security and user experience.

- **Alternative Solution 4**:
  - **Summary**: Focus on enhancing the device's Bluetooth connectivity and security features.
  - **Pros**: Improved data transmission security, potential for enhanced user privacy and protection.
  - **Cons**: Limited impact on battery life and user convenience, potential for increased complexity and cost.
  - **Reasons**: The proposed solution offers a more comprehensive and user-centric approach to addressing multiple user requirements, including battery life improvement, NFC functionality, and simultaneous actions management.
  - **Migration Plan**: If the proposed solution falls through, the next best alternative would be to explore the enhancement of the device's Bluetooth connectivity and security features and their impact on data transmission and user privacy.

## IV. Further Considerations

### 1. Constraints and Impact

<!--
How will this increase the work of other people?
-->

Because we're adding a lot of features to the device such as the alarm management or the NFC functionality, the team that is in charge of the mobile application will have to update the application to support these new features. This will increase their workload. They are those who will be most impacted by the changes we are making.

### 2. Considerations

#### A. Security Considerations

<!--
What are the potential threats?
How will they be mitigated?
How will the solution affect the security of other components, services, and systems?
-->

There are two main threats that we will have to mitigate:

- **Unauthorized Access**: The device is connected to the mobile application via Bluetooth. This means that if the Bluetooth connection is not secure, an attacker could connect to the device and unlock it. We will have to make sure that the Bluetooth connection is secure enough to prevent this from happening.
  The device may also be "infected" with a virus if the device is connected to a computer via the charging cable but we will not address this issue in this project.
- **Stolen Device**: If the device is stolen, the thief could unlock it and steal the equipment. We will have to make sure that the device is secure enough to prevent this from happening.

#### B. Privacy Considerations

<!--
Does the solution follow local laws and legal policies on data privacy?
How does the solution protect users’ data privacy?
What are some of the tradeoffs between personalization and privacy in the solution?
-->

Because we're only working on the device and not on how the data is handled, we don't have to worry about the privacy of the users' data. The company is in charge of the data and how it is handled. However, there is still a risk that the data could be compromised if the device is stolen.

#### C. Risks

<!--
What risks are being undertaken with this solution?
Are there risks that once taken can’t be walked back?
What is the cost-benefit analysis of taking these risks?
-->

The main risk we are taking is that we are adding a lot of features to the device. This could lead to the device being more complex and therefore more prone to bugs. We will have to make sure that we test the device thoroughly to prevent this from happening.

There are a lot of risks that we will describe in the table below:

| Risk                                                                   | Impact                                                                                                          |
| ---------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------- |
| The device is locked and there is an issue with the battery thresholds | The user will not be able to unlock the device and will have to wait for the charge of the device to unlock it. |
| The device is stolen while the alarm is deactivated                    | The user will not be notified and will not be able to track the device.                                         |
| The device's components are broken                                     | The device will not work properly and the user will not be able to use it.                                      |
| The battery is not charging properly                                   | The device will not respect the battery life and will not fulfil the client's requirements.                     |
| The device is not able to connect to the mobile application            | The user will not be able to lock or unlock the device.                                                         |

## V. Work

### 1. Work Estimates and Timelines

| Task                                        | Resources Needed                  | Time Estimate   |
| ------------------------------------------- | --------------------------------- | --------------- |
| Solution A.1: Battery Life Improvement      | The complete hardware             | 2 weeks         |
| Solution A.2: Battery Low Level Management  | The complete hardware             | To Define       |
| Solution B: NFC Functionality               | The complete hardware + NFC Tools | 2 week and half |
| Solution C: Simultaneous Actions Management | The complete hardware             | To Define       |

All the tasks will be done in parallel to reduce the time of the project.

### 2. Prioritization

<!--
Categorization of tasks by urgency and impact
-->

As written in the MoSCoW method, we will prioritize the tasks as follows:

- **Must Have**:
  - Solution A.1: Battery Life Improvement
  - Solution B: NFC Functionality
- **Should Have**:
  - Solution A.2: Battery Low-Level Management
  - Solution C: Simultaneous Actions Management
- **Could Have**:
  - Solution D: Bluetooth Security
  - Solution E: Alarm Management
- **Won't Have**:
  - Blinking LED to indicate device status
  - Security concerns related to charging
  - Further enhancements to shock detection

### 3. Milestones

<!--
Dated checkpoints when significant chunks of work will have been completed
Metrics to indicate the passing of the milestone
-->

The following milestones will be established to track the progress of the project:

- **Milestone 1**:

  - Completion of Solution A.1: Battery Life Improvement
  - Metrics: The device's battery life is extended to 7 days under optimal conditions, allowing for up to 6 hours of active use per day.

- **Milestone 2**:
- Completion of Solution B: NFC Functionality

  - Metrics: The device supports locking/unlocking via the mobile application using NFC functionality.

- **Milestone 3**:
- Completion of Solution A.2: Battery Low-Level Management

  - Metrics: Charging is restricted to 80% of the battery's capacity to enhance longevity.

- **Milestone 4**:
- Completion of Solution C: Simultaneous Actions Management

  - Metrics: The system effectively identifies and manages simultaneous actions, especially the activation of the alarm.

- **Milestone 5**:
- Completion of Solution E: Alarm Management

  - Metrics: Users can stop the alarm once the ringing cycle starts, either through the mobile application or the device itself.

- **Milestone 6**:
- Completion of Solution D: Bluetooth Security
  - Metrics: Data transmitted over Bluetooth encrypted to ensure confidentiality and integrity.

### 4. Future Work

<!--
List of tasks that will be completed in the future
-->

The following tasks have been identified for future iterations:

- **Working LED Blinking**: Implement LED blinking to indicate device functionality.
- **Charging Security**: Address security concerns related to charging, such as blocking the insertion of code into the device's firmware during charging.
- **Shock Detection Enhancement**: Further enhancements to shock detection to improve security and tamper detection.

## VI. Glossary

<!--
New terms you come across as you research your design or terms you may suspect your readers/stakeholders not to know.
-->

| Term | Definition                                                                                                                                                                                                                           | Source                                                                                               |
| ---- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------- |
| GPS  | GPS, or Global Positioning System, is a satellite-based navigation system that allows users to determine their approximate location (latitude, longitude, and altitude) anywhere on Earth.                                           | [Wikipedia](https://fr.wikipedia.org/wiki/Global_Positioning_System)                                 |
| GSM  | GSM (Global System for Mobile Communication) is a digital mobile network that is widely used by mobile phone users in Europe and other parts of the world.                                                                           | [Techopedia](https://www.techopedia.com/definition/5062/global-system-for-mobile-communications-gsm) |
| LED  | A light-emitting diode (LED) is a semiconductor light source that emits light when current flows through it. LEDs are used in a variety of applications, including displays, lighting, and automotive lighting.                      | [Wikipedia](https://en.wikipedia.org/wiki/Light-emitting_diode)                                      |
| NFC  | NFC, or near-field communication, is a short-range wireless technology that allows your phone to act as a transit pass or credit card, quickly transfer data, or instantly pair with Bluetooth devices like headphones and speakers. | [Wikipedia](https://en.wikipedia.org/wiki/Near-field_communication)                                  |
| RFID | RFID, or radio-frequency identification, uses electromagnetic fields to automatically identify and track tags attached to objects. The tags contain electronically stored information. RFID tags are used in many industries.        | [Wikipedia](https://en.wikipedia.org/wiki/Radio-frequency_identification)                            |
