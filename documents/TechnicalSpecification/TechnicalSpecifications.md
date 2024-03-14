# Technical Specifications

---

## Table of Contents

<details>
<summary><b>Click to expand</b></summary>

- [Technical Specifications](#technical-specifications)
  - [Table of Contents](#table-of-contents)
  - [I. Introduction](#i-introduction)
    - [1. Overview](#1-overview)
    - [2. Glossary](#2-glossary)
    - [3. Context](#3-context)
    - [4. Goals and Objectives](#4-goals-and-objectives)
    - [5. Out of Scope](#5-out-of-scope)
    - [6. Future Goals](#6-future-goals)
    - [7. Assumptions](#7-assumptions)
  - [II. Solutions](#ii-solutions)
    - [1. Current Solution](#1-current-solution)
      - [Pros](#pros)
      - [Cons](#cons)
    - [2. Suggested Solution](#2-suggested-solution)
    - [3. Test Plan](#3-test-plan)
    - [4. Monitoring and Alerting Plan](#4-monitoring-and-alerting-plan)
    - [5. Rollout Plan](#5-rollout-plan)
    - [6. Rollback Plan](#6-rollback-plan)
    - [7. Alternate Solutions](#7-alternate-solutions)
  - [III. Further Considerations](#iii-further-considerations)
    - [1. Impact on Other Teams](#1-impact-on-other-teams)
    - [2. Third-Party Services](#2-third-party-services)
    - [3. Considerations](#3-considerations)
      - [A. Security Considerations](#a-security-considerations)
      - [B. Privacy Considerations](#b-privacy-considerations)
      - [C. Regional Considerations](#c-regional-considerations)
      - [D. Accessibility Considerations](#d-accessibility-considerations)
      - [E. Operational Considerations](#e-operational-considerations)
      - [F. Risks](#f-risks)
      - [G. Support Considerations](#g-support-considerations)
  - [IV. Success Evaluation](#iv-success-evaluation)
    - [1. Impact](#1-impact)
    - [2. Metrics](#2-metrics)
    - [V. Work](#v-work)
      - [1. Work Estimates and Timelines](#1-work-estimates-and-timelines)
      - [2. Prioritization](#2-prioritization)
      - [3. Milestones](#3-milestones)
      - [4. Future Work](#4-future-work)
  - [VI. Conclusion](#vi-conclusion)
  - [VII. References](#vii-references)

</details>

---

## I. Introduction

### 1. Overview

A French company named CORIS Innovation asked us to improve their product named SPORTSHIELD. The product is a device that serves as a lock for all sorts of sports equipment. The device is connected to a mobile application that allows the user to lock and unlock the equipment. The company has been facing a lot of issues with the current solution and has asked us to come up with a new solution that will solve the issues they are facing. The stakeholders are the company and the users of the product.

### 2. Glossary

<!--
New terms you come across as you research your design or terms you may suspect your readers/stakeholders not to know.
-->

| Term | Definition                                                                                                                                                                                                                           | Source                                                              |
| ---- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------- |
| NFC  | NFC, or near-field communication, is a short-range wireless technology that allows your phone to act as a transit pass or credit card, quickly transfer data, or instantly pair with Bluetooth devices like headphones and speakers. | [Wikipedia](https://en.wikipedia.org/wiki/Near-field_communication) |

### 3. Context

The decision for the company to seek improvement for their product stems from numerous issues within the current solution. These include limitations such as the device's autonomy, the lack of user notification during alarm activation, and the inability to halt the alarm once the ringing cycle initiates.

### 4. Goals and Objectives

Fortunately, the company has provided us with a comprehensive list of requirements for the new solution:

- Ensure the device maintains a battery life of at least 7 days, allowing for up to 6 hours of active use per day.
- Implement NFC functionality for device unlocking.
- Introduce multi-action capability, such as sending user notifications when the alarm activates.
- Enhance security protocols for accessing key system features like lock/unlock and alarm management.

### 5. Out of Scope

Several requirements fall outside the scope of this project and will not be addressed:

- Implementing LED blinking to indicate device functionality.
- Addressing security concerns related to charging.
- Further enhancements to shock detection.

### 6. Future Goals

Certain requirements have been identified for future iterations:

- Securing the Bluetooth connection between the device and the mobile application.
- Enhancing alarm management to allow users to halt the alarm once the ringing cycle commences.

### 7. Assumptions

We are operating under the following assumptions:

- All essential hardware and software components required for development and testing will be readily available.
- Access to the current solution will be granted to facilitate understanding of its functionality and encountered issues.
- The company will furnish us with requisite documentation and assistance to comprehend the current solution and its associated challenges.

## II. Solutions

### 1. Current Solution

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

### 2. Suggested Solution

<!--
External components that the solution will interact with and that it will alter
Dependencies of the current solution
Pros and cons of the proposed solution
**Data Model / Schema Changes**
  Schema definitions
  New data models
  Modified data models
  Data validation methods
**Business Logic**
  API changes
  Pseudocode
  Flowcharts
  Error states
  Failure scenarios
  Conditions that lead to errors and failures
  Limitations
**Presentation Layer**
  User requirements
  UX changes
  UI changes
  Wireframes with descriptions
  Links to UI/UX designer’s work
  Mobile concerns
  Web concerns
  UI states
  Error handling
**Other questions to answer**
  How will the solution scale?
  What are the limitations of the solution?
  How will it recover in the event of a failure?
  How will it cope with future requirements?
-->

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

## III. Further Considerations

### 1. Impact on Other Teams

<!--
How will this increase the work of other people?
-->

### 2. Third-Party Services

<!--
Is it really worth it compared to building the service in-house?
What are some of the security and privacy concerns associated with the services/platforms?
How much will it cost?
How will it scale?
What possible future issues are anticipated?
-->

### 3. Considerations

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

#### C. Regional Considerations

<!--
What is the impact of internationalization and localization on the solution?
What are the latency issues?
What are the legal concerns?
What is the state of service availability?
How will data transfer across regions be achieved and what are the concerns here?
-->

#### D. Accessibility Considerations

<!--
How accessible is the solution?
What tools will you use to evaluate its accessibility?
-->

#### E. Operational Considerations

<!--
Does this solution cause adverse aftereffects?
How will data be recovered in case of failure?
How will the solution recover in case of a failure?
How will operational costs be kept low while delivering increased value to the users?
-->

#### F. Risks

<!--
What risks are being undertaken with this solution?
Are there risks that once taken can’t be walked back?
What is the cost-benefit analysis of taking these risks?
-->

#### G. Support Considerations

<!--
How will the support team get across information to users about common issues they may face while interacting with the changes?
How will we ensure that the users are satisfied with the solution and can interact with it with minimal support?
Who is responsible for the maintenance of the solution?
How will knowledge transfer be accomplished if the project owner is unavailable?
-->

## IV. Success Evaluation

### 1. Impact

<!--
Security impact
Performance impact
Cost impact
Impact on other components and services
-->

### 2. Metrics

<!--
List of metrics to capture
Tools to capture and measure metrics
-->

### V. Work

#### 1. Work Estimates and Timelines

<!--
List of specific, measurable, and time-bound tasks
Resources needed to finish each task
Time estimates for how long each task needs to be completed
-->

#### 2. Prioritization

<!--
Categorization of tasks by urgency and impact
-->

#### 3. Milestones

<!--
Dated checkpoints when significant chunks of work will have been completed
Metrics to indicate the passing of the milestone
-->

#### 4. Future Work

<!--
List of tasks that will be completed in the future
-->

## VI. Conclusion

<!--
Summary of the solution
-->

## VII. References

<!--
Links to documents and resources that you used when coming up with your design and wish to credit.
-->

---
