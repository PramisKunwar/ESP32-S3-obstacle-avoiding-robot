# ESP32-S3-obstacle-avoiding-robot. 
My project is an esp32 s3 obstacle avoiding robot which is cable of detecting obstacle and navigate safely without user intervention.

The robot continuously measures the distance infront of it using ultrasonic sensor and when it detects something within 20cm then it stops and 
activates a warning buzzer while reversing iteself and then resumes moving forward. And the distance measured 
by the sensor and direction of motor is shown in the oled display.

I made this for breadboard ysws of hack club. I always wanted to make something useful and here it is.

![Description of image](Circuit_Image/circuit_image.svg)

![Description of image](Circuit_Image/sim2.png)

This is the link of the simulator is use:  
https://app.cirkitdesigner.com/project/f90774bd-6f8a-4112-8314-95b0661fc0bb

# Bill of material 

- ESP-32 1 pcs
- L298N motor driver 1 pcs
- HC-SR04 Ultrasonic sensor 1 pcs
- 0.96" OLED Display 1 pcs
- Buzzer 1pcs
- DC gear motor 4 pcs
- Wheels 4 pcs
- Breadboard 1 pcs
- Jumper wires 1 set
- 3s li-ion battery 3 pcs
- 3s battery holder 1 pcs 

# Creator
Pramis Kunwar 
Made for hack club
