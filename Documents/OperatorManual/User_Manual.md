## Setup Manual

### Required Software:

To begin, you need to install the **Arduino IDE**. Download it from the official Arduino website at [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software). Follow the installation instructions for your operating system (Windows, MacOS, Linux).

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

3. Find **Seeed NRF52 mbed enabled Boards by Seeed Studio** in the list and click `Install`.

### Finalization:

After installing the required software, libraries, and board, you are ready to upload your programs to your hardware. Remember to select the correct board type in `Tools` > `Board` and the corresponding serial port for your device.

