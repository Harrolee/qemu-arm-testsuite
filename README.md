
# Integration testing for ARM boards

## two functional versions:
### demo:
The steps required to use this are pretty specific to the mps2-an500. The important part of the demo is this:
**complied code can be run on an emulated machine within a container**

### test engine:
**work in progress**
 - upload code to a front end
 - recieve a file describing the output sent to GPIO pins 


## versions described below

#### demo

##### you can refactor this to run any code on any QEMU-supported ARM-based machine
    - Currently, the container is set to emulate the mps2-an500.
    - QEMU passes the .hex file directly into the flash memory of the device.
    - In order for your code to run, you will need to compile it with an mps2-an500 CMSIS package through ARM's free development tool, Keil MDK (https://developer.arm.com/tools-and-software/embedded/keil-mdk)
    - You will need to build your code into a .hex file 

##### if you build and run the docker image in the demo directory:
 - the dockerfile copies a sample "Blinky" program from the 'hex' directory into the container
 - the container emulates the mps2-an500 machine and runs the "Blinky.hex" file

#### test engine

##### to upload the file that you have exported as a hex from klein:
 - find the external ip provided by the cmdhub-lb service.
 - send a post request to the /upload-code/ path:
    - curl -F file=@k8s/pods/emu_device/code.hex http://EXTERNAL_IP/upload-code/


## Currently supports:
### - mps22-an500

## Upcoming support (April, 2021):
### - teensy 4.0
    will need to write teensy 4.0 as a QOM machine first
