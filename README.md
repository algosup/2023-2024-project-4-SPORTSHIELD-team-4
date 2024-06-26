# SPORTSHIELD Team 4

**SPORTSHIELD** is an original anti-theft system for sports equipment. It's a project contracted by the company [Coris Innovation](https://www.corisinnovation.com/).

This device is designed to protect sports equipment such as skis and snowboards. It is composed of a **GPS** and a **GSM** module. The **GPS** module is used to locate the equipment, and the **GSM** module is used to send the location to the user's smartphone. The device is also equipped with a **gyroscope** to detect any movement of the equipment. The user can then be alerted in case of theft. The device is powered by a **battery** and can be recharged via a **USB-C** port. It's also equipped with an **NFC** module to unlock or lock the device. Finally, a **buzzer** is used to alert the user in case of theft.

For this project, Coris Innovation has asked us to:

- Increase the lifespan of the **battery**.🔋
- Add the possibility to use **NFC** to unlock or lock the device.🔓
- Implement a way to manage simultaneous actions on the device.🔄

## Technologies used

- **Arduino** for the development of the hardware. <img src="Documents/TechnicalSpecification/Images/Arduino-removebg-preview.png" width="15px" height="15px"/> (And to develop it we use <img src="Documents/TechnicalSpecification/Images/Clogo-removebg-preview.png" width="15px" height="15px"/> and <img src="Documents/TechnicalSpecification/Images/C++_logo-removebg-preview.png" width="15px" height="15px"/> )

## Documentation

Here is the list of all the main documents related to the project:

- [Management Artifacts](Documents/Management/ManagementArtifacts.md)
- [Functional Specification](Documents/FunctionalSpecifications/FunctionalSpecifications.md)
- [Technical Specification](Documents/TechnicalSpecification/TechnicalSpecifications.md)
- [User Manual](/User%20Manual%20SportShield%20.pdf)
- [Test Plan](Documents/QA/TestPlan.md)

## How to Use

### Prerequisites

Before getting started, ensure you have the following:

- **Arduino IDE**: Install it on your computer. You can download it [here](https://www.arduino.cc/en/software).
- Download all the libraries used in the project.
- **LightBlue** Application: Install it on your smartphone. You can download it for [Android](https://play.google.com/store/apps/details?id=com.punchthrough.lightblueexplorer&hl=fr&gl=US) and [iOS](https://apps.apple.com/fr/app/lightblue/id557428110).
- **Arduino** Board: Make sure you have one available.

### Installation

Follow these steps to set up:

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/algosup/2023-2024-project-4-SPORTSHIELD-team-4.git
   ```

2. **Open Arduino IDE**:
   Open the Arduino IDE and navigate to the SPORTSHIELD.ino file located in the Code folder here: `2023-2024-project-4-SPORTSHIELD-team-4/Code/SPORTSHIELD/SPORTSHIELD.ino`

3. **Install Libraries**:
   Install all the libraries used in the project. You can find them here in the Required Libraries section.

4. **Connect Arduino Board**:
   Connect your Arduino board to your computer.

5. **Configure Arduino IDE**:
   Select the correct board and port in the Arduino IDE.

6. **Upload Code**:
   Upload the code to your Arduino board.

7. **Open LightBlue Application**:
   Launch the LightBlue application on your smartphone.

8. **Connect to SPORTSHIELD Device**:
   Find and connect to the SPORTSHIELD device. It should appear in the list of devices in the LightBlue application with the name "Team 4".

9. **Start Using SPORTSHIELD**:
   Now you can start using the SPORTSHIELD device. Enjoy!

### Required Libraries:

After installing the Arduino IDE, open it and install the following libraries through the **Library Manager** (`Sketch` > `Include Library` > `Manage Libraries...`).

1. **NRF52_MBED_TimerInterrupt (V1.4.1)**

   - In the search field, type `NRF52_MBED_TimerInterrupt`, select version `1.4.1`, and click `Install`.

2. **ArduinoBLE (V1.3.6)**

   - Search for `ArduinoBLE`, select version `1.3.6`, and click `Install`.

3. **Adafruit GPS Library (V1.7.4)**

   - Type `Adafruit GPS Library`, select version `1.7.4`, and click `Install`.

4. **Sim800L http connector (V1.14.0)**

   - Search for `Sim800L http connector`, choose version `1.14.0`, and click `Install`.

5. **Seeed Arduino LSM6DS3 (V2.0.3)**

   - Type `Seeed Arduino LSM6DS3`, select version `2.0.3`, and click `Install`.

6. **OneWire (V2.3.7)**

   - Search for `OneWire`, choose version `2.3.7`, and click `Install`.

### Required Board:

To install the necessary board, follow these steps in the Arduino IDE:

1. Open the **Board Manager** by going to `Tools` > `Board` > `Boards Manager...`.

2. In the Boards Manager search bar, type `Seeed NRF52 mbed enabled Boards`.

## Contributors

| Photo                                                                                                                                     | Name            | Role              | LinkedIn                                                           |
| ----------------------------------------------------------------------------------------------------------------------------------------- | --------------- | ----------------- | ------------------------------------------------------------------ |
| [<img src="Documents/TechnicalSpecification/Images/MaximeCARON.jpeg" width="100px" height="100px"/>](https://github.com/MaximeAlgosup)    | Maxime CARON    | Project Manager   | [LinkedIn](https://www.linkedin.com/in/maxime-caron-dev/)          |
| [<img src="Documents/TechnicalSpecification/Images/LucasAUBARD.png" width="100px" height="100px"/>](https://github.com/LucasAub)          | Lucas AUBARD    | Program Manager   | [LinkedIn](https://www.linkedin.com/in/lucas-aubard-596b37251/)    |
| [<img src="Documents/TechnicalSpecification/Images/AlexisLASSELIN.png" width="100px" height="100px"/>](https://github.com/AlexisLasselin) | Alexis LASSELIN | Technical Leader  | [LinkedIn](https://www.linkedin.com/in/alexis-lasselin-318649251/) |
| [<img src="Documents/TechnicalSpecification/Images/WilfriedPORTET.png" width="100px" height="100px"/>](https://github.com/PortetWilfried) | Wilfried PORTET | Software Engineer | [LinkedIn](https://www.linkedin.com/in/wilfried-portet-a882b9293/) |
| [<img src="Documents/TechnicalSpecification/Images/PaulNOWAK.jpeg" width="100px" height="100px"/>](https://github.com/PaulNowak36)        | Paul NOWAK      | Technical Writer  | [LinkedIn](https://www.linkedin.com/in/paul-nowak-0757a61a7/)      |
| [<img src="Documents/TechnicalSpecification/Images/HabiCAILLEAU.png" width="100px" height="100px"/>](https://github.com/habicll)          | Habi CAILLEAU   | Quality Assurance | [LinkedIn](https://www.linkedin.com/in/habi-cailleau-3b72b5293/)   |
