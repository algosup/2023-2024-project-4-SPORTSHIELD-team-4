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
    - [1. Development Board\*\*](#1-development-board)
    - [2. Battery](#2-battery)
    - [3. GPS Module](#3-gps-module)
    - [4. GSM Module](#4-gsm-module)
    - [5. NFC Module](#5-nfc-module)
    - [6. Electromagnet](#6-electromagnet)
    - [7. Piezoelectric Buzzer](#7-piezoelectric-buzzer)
    - [8 . Electronic Configuration](#8--electronic-configuration)
  - [III. Solutions](#iii-solutions)
    - [1. Current Product](#1-current-product)
      - [Pros](#pros)
      - [Cons](#cons)
    - [2. Suggested Solutions](#2-suggested-solutions)
      - [A. Battery Life Improvement \& Low Level Management](#a-battery-life-improvement--low-level-management)
      - [B. NFC Functionality](#b-nfc-functionality)
      - [C. Simultaneous Actions Management](#c-simultaneous-actions-management)
      - [D. Bluetooth Security](#d-bluetooth-security)
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
  - [VII. References](#vii-references)

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
- The company will furnish us with requisite documentation and assistance to comprehend the current solution and its associated challenges.

## II. Hardware

The SPORTSHIELD device comprises various hardware components carefully selected for optimal performance and functionality:

### 1. Development Board\*\*

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

#### Pros

- Provides remote locking and unlocking capabilities, enhancing convenience for users.
- Offers shock detection functionality to alert users of potential tampering or unauthorized access.
- Incorporates geo-location features to assist users in tracking misplaced or stolen equipment.

#### Cons

- Limited battery life may necessitate frequent recharging, potentially leading to user inconvenience.
- Reliance on Bluetooth connectivity may result in connectivity issues or limitations in range.
- The alarm system's simplicity may not adequately address all potential security concerns or user preferences.

### 2. Suggested Solutions

#### A. Battery Life Improvement & Low Level Management

To address the issue of limited battery life, the following improvements will be implemented:

**Objective**: Extend the device's battery life to 7 days with up to 6 hours of active use per day by optimizing power consumption and implementing efficient battery management.

- **How To Implement**:
  - Optimize power consumption through software and hardware adjustments.
  - Implement efficient battery management algorithms to regulate power usage.
  - Limit the charge to 80% of the battery's capacity to extend its lifespan.

![Battery Manager](./Images/BatteryFlow.png)

- **Acceptance Criteria**:
  - The device's battery life will be extended to 7 days under optimal conditions, with up to 6 hours of active use per day.
  - Charging will be limited to 80% of the battery's capacity to prolong its lifespan.

#### B. NFC Functionality

To expand the device's capabilities, NFC functionality will be incorporated to facilitate device locking and unlocking:

**Objective**: Integrate NFC functionality to enable users to lock/unlock the device using their mobile phones.

- **How To Implement**:

  - Utilize the NFC tag M24LR6E library from Seed Studio to implement NFC functionality.
  - Employ the library to enable reading data from the NFC tag, which will be utilized for device locking and unlocking.

- **Acceptance Criteria**:
  - The device will support locking/unlocking via the mobile application using NFC functionality.
  - Testing of NFC functionality will be conducted using the NFC tag of a smartphone, as access to the mobile application is unavailable for testing purposes.

#### C. Simultaneous Actions Management

**Objective**: Implement a system for managing simultaneous actions, particularly focusing on notifying the user when the alarm is activated.

- **How To Implement**:

  - Develop a mechanism to detect simultaneous actions such as shock detection triggering the alarm.
  - Integrate a notification system within the mobile application to alert the user when the alarm activates.
  - Ensure seamless coordination between the device and the mobile application to deliver real-time notifications.

- **Acceptance Criteria**:
  - The system successfully detects and manages simultaneous actions, particularly the activation of the alarm.
  - Users receive timely notifications on their mobile devices when the alarm is activated.
  - The notification system operates efficiently, providing real-time alerts without significant delays.

#### D. Bluetooth Security

**Objective**: Enhance the security protocols governing Bluetooth connectivity between the device and the mobile application.

- **How To Implement**:

  - Implement encryption protocols to secure data transmission over Bluetooth.
  - Utilize secure pairing mechanisms to establish a trusted connection between the device and the mobile application.
  - Integrate authentication measures to verify the identity of both the device and the mobile application during the pairing process.

- **Acceptance Criteria**:
  - Data transmitted over Bluetooth is encrypted, ensuring confidentiality and integrity.
  - Secure pairing mechanisms are employed, preventing unauthorized devices from connecting to the SPORTSHIELD device.
  - Authentication measures successfully validate the identity of both the device and the mobile application, reducing the risk of unauthorized access.

### 3. Test Plan

<!--
Explanations of how the tests will make sure user requirements are met
Unit tests
Integrations tests
QA
-->

### 4. Monitoring and Alerting Plan

<!--
Logging plan and tools
Monitoring plan and tools
Metrics to be used to measure health
How to ensure observability
Alerting plan and tools
-->

### 5. Rollout Plan

<!--
Deployment architecture
Deployment environments
Phased roll-out plan e.g. using feature flags
Plan outlining how to communicate changes to the users, for example, with release notes
-->

### 6. Rollback Plan

<!--
Detailed and specific liabilities
Plan to reduce liabilities
Plan describing how to prevent other components, services, and systems from being affected
-->

### 7. Alternate Solutions

<!--
Short summary statement for each alternative solution
Pros and cons for each alternative
Reasons why each solution couldn’t work
Ways in which alternatives were inferior to the proposed solution
Migration plan to next best alternative in case the proposed solution falls through
-->

## IV. Further Considerations

### 1. Constraints and Impact

<!--
How will this increase the work of other people?
-->

Because we're adding a lot of features in the device such as the alarm management or the NFC functionality, the team that is in charge of the mobile application will have to update the application to support these new features. This will increase their workload. They are those who will be most impacted by the changes we are making.

### 2. Considerations

#### A. Security Considerations

<!--
What are the potential threats?
How will they be mitigated?
How will the solution affect the security of other components, services, and systems?
-->

#### B. Privacy Considerations

<!--
Does the solution follow local laws and legal policies on data privacy?
How does the solution protect users’ data privacy?
What are some of the tradeoffs between personalization and privacy in the solution?
-->

Because we're only working on the device and not on how the data is handled, we don't have to worry about the privacy of the users' data. The company is in charge of the data and how it is handled. However, there is still a risk that the data could be compromised if the device is stolen. We will have to make sure that the device is secure enough to prevent this from happening.

#### C. Risks

<!--
What risks are being undertaken with this solution?
Are there risks that once taken can’t be walked back?
What is the cost-benefit analysis of taking these risks?
-->

The main risk we are taking is that we are adding a lot of features to the device. This could lead to the device being more complex and therefore more prone to bugs. We will have to make sure that we test the device thoroughly to prevent this from happening.

There is a lot of risk that we will describe in the table below:

| Risk                                                                   | Impact                                                                                                      |
| ---------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------- |
| The device is locked and there is an issue with the battery thresholds | The user will not be able to unlock the device and will have to wait the charge of the device to unlock it. |
| The device is stolen while the alarm is deactivated                    | The user will not be notified and will not be able to track the device.                                     |
| The device's components are broken                                     | The device will not work properly and the user will not be able to use it.                                  |
| The battery is not charging properly                                   | The device will not respect the battery life and will not fill the client's requirements.                   |
| The device is not able to connect to the mobile application            | The user will not be able to lock or unlock the device.                                                     |

## V. Work

### 1. Work Estimates and Timelines

<!--
List of specific, measurable, and time-bound tasks
Resources needed to finish each task
Time estimates for how long each task needs to be completed
-->

### 2. Prioritization

<!--
Categorization of tasks by urgency and impact
-->

### 3. Milestones

<!--
Dated checkpoints when significant chunks of work will have been completed
Metrics to indicate the passing of the milestone
-->

### 4. Future Work

<!--
List of tasks that will be completed in the future
-->

## VI. Glossary

<!--
New terms you come across as you research your design or terms you may suspect your readers/stakeholders not to know.
-->

| Term | Definition                                                                                                                                                                                                                           | Source                                                              |
| ---- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------- |
| NFC  | NFC, or near-field communication, is a short-range wireless technology that allows your phone to act as a transit pass or credit card, quickly transfer data, or instantly pair with Bluetooth devices like headphones and speakers. | [Wikipedia](https://en.wikipedia.org/wiki/Near-field_communication) |

## VII. References

<!--
Links to documents and resources that you used when coming up with your design and wish to credit.
-->

---
