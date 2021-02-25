# Device emulation flow
   - create an image prepared to emulate the device
   - place the .hex files meant to run on the devices someplace accessible to the entire cluster 
      (each .hex contains a different type of test)
      - can we mount a directory from the user's computer? the .hex files would go there and get picked up by the bash script that begins each an500 emulation
   - bash script 




# Testing Architecture

 - User writes tests in C 
 - They somehow get to a webserver
 - Webserver client publishes tests as messages to the broker as topics
 - broker pushes tests to the devices subscribed to each topic


- client devices are containerized qemu emulations
- broker is a linux container running mosquitto and not much else
- webserver is a linux container running python, hosting fastapi


The program that is to be tested is placed in the flash memory of each device on emulation start.
On startup, the kernel of each client device uses mosquitto to listen for messages. On receipt, the client runs code placed in memory.

(with the an500, we enjoy the luxury of pre-completed memory allocation, thanks to uvision and cmsis)
(I'll have to write memory allocation logic for the teensy and other microcontrollers)

## What are the topics?

 - Are they different kinds of tests?
 - What are the ways we want to test the code?
    - speed
    - 