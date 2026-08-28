# 🌡️ SMS Based Heat Monitoring and Management System

## 📌 Project Overview

The SMS Based Heat Monitoring and Management System is an embedded
system project designed for real-time temperature monitoring and control
using SMS-based communication.

The system continuously monitors temperature-sensitive environments and
provides alert notifications through GSM communication when the
temperature exceeds the configured threshold. It allows users to
remotely update temperature settings, modify alert phone numbers, and
request sensor information through secure SMS commands.

The system is developed using an LPC2148 ARM7 microcontroller with
DS18B20 temperature sensing, GSM communication, EEPROM storage, LCD
display, RTC time monitoring, and buzzer alert mechanisms.

------------------------------------------------------------------------

## 👨‍💻 Author

**Kausalya Indeti**

------------------------------------------------------------------------

# 🚀 Features

-   Real-time temperature monitoring using DS18B20 sensor
-   Automatic SMS alert during high-temperature conditions
-   Temperature threshold configuration through SMS
-   Secure SMS command authentication using passkey
-   EEPROM storage for setpoint and mobile number
-   LCD display for temperature and system status
-   Buzzer alert during overheating conditions
-   RTC-based time information in alert messages
-   GSM-based remote communication

------------------------------------------------------------------------

# 🛠️ Hardware Components

-   LPC2148 ARM7 Microcontroller
-   GSM Module (M660A)
-   DS18B20 Temperature Sensor
-   16x2 LCD Display
-   Buzzer
-   AT25LC512 SPI EEPROM
-   RTC Module
-   Power Supply Circuit

------------------------------------------------------------------------

# 💻 Software Requirements

-   Embedded C Programming
-   Keil C Compiler
-   Flash Magic
-   UART Communication
-   SPI Communication
-   ARM7 Microcontroller Programming

------------------------------------------------------------------------

# ⚙️ System Working

1.  The system initializes all peripherals including UART, LCD, SPI,
    RTC, GSM, and temperature sensor.
2.  The temperature value is continuously read from the DS18B20 sensor.
3.  The LPC2148 processes the temperature data and displays it on the
    LCD.
4.  The current temperature is compared with the stored setpoint value
    from EEPROM.
5.  If the temperature exceeds the configured limit:
    -   The buzzer is activated.
    -   An SMS alert containing temperature and RTC information is sent
        to the registered mobile number.
6.  The system continuously checks for incoming SMS commands.
7.  Authorized users can update the temperature setpoint, change alert
    mobile numbers, or request sensor information.

------------------------------------------------------------------------

# 📲 SMS Command Control

The system uses a secure SMS command format with a 4-digit passkey.

## Change Temperature Setpoint

Format:

    XXXXTTemperatureValue$

Example:

    0786T38$

Updates the temperature threshold value stored in EEPROM.

------------------------------------------------------------------------

## Change Alert Mobile Number

Format:

    XXXXMMobileNumber$

Example:

    0786M9866666699$

Updates the notification mobile number stored in EEPROM.

------------------------------------------------------------------------

## Request Sensor Information

Format:

    XXXXI$

Example:

    0786I$

Sends current temperature and time information through SMS.

------------------------------------------------------------------------

# 🏗️ Project Flow Diagram

                        START
                          |
                          ↓
            Initialize Embedded System Modules
                          |
       ---------------------------------------------
       |        |        |        |                 |
     UART     LCD      SPI      RTC              GSM
     Init     Init     Init     Init             Init
                          |
                          ↓
            Load Setpoint from EEPROM
                          |
                          ↓
              Read Temperature Sensor
                          |
                          ↓
              Display Temperature on LCD
                          |
                          ↓
                 Read RTC Time
                          |
                          ↓
            Compare Temperature & Setpoint
                          |
                 ----------------
                 |              |
                 ↓              ↓
         Temperature High    Normal Temp
                 |              |
                 ↓              ↓
           Activate Buzzer   Continue Monitoring
                 |
                 ↓
           Send Alert SMS
                 |
                 ↓
           Check Incoming SMS
                 |
                 ↓
         Verify Sender Number
                 |
                 ↓
           Validate Passkey
                 |
           -------------------------
           |           |            |
           ↓           ↓            ↓
      T Command    M Command    I Command
     Update Temp  Update Mobile Sensor Info
      Setpoint      Number        Response
           |
           ↓
     Save Data in EEPROM
           |
           ↓
     Delete SMS
           |
           ↓
     Return to Monitoring Loop

------------------------------------------------------------------------

# 🏗️ System Architecture

                 DS18B20 Temperature Sensor
                           |
                           ↓
                     LPC2148 MCU
                           |
            --------------------------------
            |              |               |
            ↓              ↓               ↓
          LCD             RTC          EEPROM
        Display          Time        Storage
                           |
                           ↓
                      GSM Module
                           |
                           ↓
                  SMS Notification
                           |
                           ↓
                        User

------------------------------------------------------------------------

# 🔒 Security Mechanism

The system uses password-based SMS authentication to prevent
unauthorized access.

Only messages containing the correct passkey and valid command format
are processed. Unauthorized senders receive an access denial message,
while invalid commands are rejected.

------------------------------------------------------------------------

# 🌍 Applications

-   Industrial temperature monitoring
-   Cold storage monitoring systems
-   Server room temperature protection
-   Electronic equipment safety monitoring
-   Laboratory temperature control systems
-   Remote environmental monitoring

------------------------------------------------------------------------

# ✅ Advantages

-   Real-time temperature monitoring
-   Remote control using SMS communication
-   No internet dependency
-   Secure authentication mechanism
-   Low-cost embedded system design
-   Reliable alert notification

------------------------------------------------------------------------

# 🔮 Future Enhancements

-   Mobile application integration
-   Multiple temperature sensor support
-   Automatic cooling system control
-   Cloud-based data logging
-   Advanced authentication methods

------------------------------------------------------------------------

# 👨‍💻 Project Category

**Embedded Systems \| ARM7 Microcontroller \| Embedded C \| GSM
Communication \| Temperature Monitoring**

------------------------------------------------------------------------

# ✍️ Author

**Kausalya Indeti**
