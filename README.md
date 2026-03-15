# Arduino Smart Car 🚗

This project is an Arduino-based smart car that can be controlled via Bluetooth and is also capable of automatically avoiding obstacles.

## Features

- Bluetooth control via mobile phone
- Ultrasonic sensor for obstacle detection
- Servo motor for scanning left and right
- Automatic path decision (left or right)
- Buzzer alert when an obstacle is detected
- Back LED when the car moves backward
- LCD display for system messages

## Components Used

- Arduino Uno
- L298N Motor Driver
- HC-05 Bluetooth Module
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- LCD I2C Display (16x2)
- Buzzer
- LEDs
- DC Motors
- Battery pack

## How It Works

1. The car can be controlled via Bluetooth commands from a mobile phone.
2. The ultrasonic sensor continuously measures the distance in front of the car.
3. If an obstacle is detected within 20 cm:
   - The car stops
   - The buzzer alerts
   - The car moves backward
   - The servo rotates the ultrasonic sensor left and right
   - The car chooses the direction with more free space.

## Bluetooth Commands

| Command | Action |
|-------|------|
| F | Move Forward |
| B | Move Backward |
| L | Turn Left |
| R | Turn Right |
| S | Stop |
| Y | Activate Buzzer |

## Author

Ahmed Magdi
