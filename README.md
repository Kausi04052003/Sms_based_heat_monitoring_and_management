# 🌡️ SMS Based Heat Monitoring and Management System

## 📌 Project Overview

The SMS Based Heat Monitoring and Management System is an embedded system project designed for real-time temperature monitoring and control using SMS-based communication.

The system continuously monitors temperature-sensitive environments and provides alert notifications through GSM communication when the temperature exceeds the configured threshold. It also allows users to remotely update temperature settings, modify alert phone numbers, and request sensor information through SMS commands.

The system is developed using an LPC2148 microcontroller with temperature sensing, GSM communication, EEPROM storage, LCD display, and alert mechanisms. It can be used in industrial facilities, cold storage systems, and server rooms where continuous temperature monitoring is required.

---

## 🚀 Features

- Real-time temperature monitoring using DS18B20 temperature sensor
- Automatic SMS alert notification during high-temperature conditions
- Remote temperature threshold configuration through SMS
- Password-based SMS command security
- EEPROM-based storage for temperature settings and phone numbers
- LCD display for temperature and system information
- Buzzer/LED alert indication during overheating conditions
- Real-time clock integration for timestamp-based alerts
- GSM-based remote communication

---

## 🛠️ Hardware Components

- LPC2148 ARM7 Microcontroller
- GSM Module (M660A)
- DS18B20 Temperature Sensor
- 16x2 LCD Display
- Buzzer
- AT25LC512 SPI EEPROM
- RTC Module
- Power Supply Components

---

## 💻 Software Requirements

- Embedded C Programming
- Keil C Compiler
- Flash Magic
- UART Communication Programming
- SPI Communication Programming

---

## ⚙️ System Working

1. The DS18B20 temperature sensor continuously measures the current temperature.
2. The LPC2148 microcontroller processes the temperature readings.
3. The temperature value is displayed on the LCD.
4. The system compares current temperature with the predefined set point stored in EEPROM.
5. If the temperature exceeds the limit:
   - The buzzer/LED alert is activated.
   - SMS alert is sent to the registered mobile number.
6. Users can configure system parameters through secure SMS commands.

---

## 📲 SMS Command Control

### Change Temperature Set Point

Format:
```
XXXXTTemperatureValue$
```

Example:
```
0786T38$
```

### Change Alert Mobile Number

Format:
```
XXXXMMobileNumber$
```

Example:
```
0786M9866666699$
```

### Request Sensor Information

Format:
```
XXXXI$
```

Example:
```
0786I$
```

---

## 🏗️ System Architecture

```
        DS18B20
            |
            ↓
      LPC2148 MCU
            |
   -----------------
   |       |       |
  LCD    RTC   EEPROM
            |
            ↓
       GSM Module
            |
            ↓
      SMS Notification
            |
            ↓
          User
```

---

## 🔒 Security Mechanism

The system uses password-based SMS authentication to prevent unauthorized access. Only messages containing the correct passkey and valid command format are processed.

---

## 🌍 Applications

- Industrial temperature monitoring
- Cold storage monitoring systems
- Server room temperature protection
- Electronic equipment safety monitoring
- Laboratory temperature control systems

---

## ✅ Advantages

- Real-time temperature monitoring
- Remote configuration using SMS
- No internet dependency
- Secure user authentication
- Low-cost embedded solution
- Reliable alert mechanism

---

## 🔮 Future Enhancements

- Mobile application-based monitoring
- Cloud data logging
- Multiple sensor support
- Automatic cooling system control
- Advanced security authentication

---

## 👨‍💻 Project Category

**Embedded Systems | ARM Microcontroller | Embedded C | GSM Communication | Temperature Monitoring**

---

## ✍️ Author

**Kausalya Indeti**
