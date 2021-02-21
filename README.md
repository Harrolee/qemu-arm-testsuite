
# Integration testing for ARM boards

## atm, this launches the mps2-an500 and runs a sample "Blinky" program

# notebook:

requirements:
	- Board needs to talk to a webserver on the network
	- Board needs to run tests:
		- What kind of tests?

The point of integration testing is to run new code alongside existing code.

We need a place to input new code
	A suite of tests needs to be run with that new code

We need a place to input existing codebase

We need a place to record the existing architecture, state
	What does that architecture look like?
		In the case of a pinball machine, there is a teensy 4.0 and a custom device that listens for commands on a serial port.
		In this case, our tests will need to prove that commands sent from a webserver to the teensy can be received and then sent to the custom device over serial.
			In reality, the custom device executes operations on motors and then returns whether the command was successful. 
			In our environment, the custom device recieves commands from the teensy, attempts to execute the connected operation, and then returns whether the operation succeeded or failed. My goal is to test the ability of the webserver to respond in cases where operations sent from the teensy fail.

	When the webserver recieves notice that a test failed, it files the information about the pinball machine, the device that failed, the failure code, the time of failure, onto a pub/sub message bus. A webservice, subscribed to that post type, will get the email of the user from a NoSQL db and send the error to the user.


Pinball Case Study:

::K8s cluster::

	::Pod Type 3 - email sender::
	 - Pub/Sub bus
	 - NoSQL DB

	::Pod Type 4 - error logger::
	- Webserver
		- recieves error from Pinball simulator
		- formats as message
		- sends message to email sender
	- SQL DB --> PinballMachine : Error Type : Time :   

	::Pod Type 1 - command center::
	 - Webserver

	::Pod Type 2 - Pinball simulator::
	 - Teensy
	 - Custom device
:::::::::::::::::::::

Resources that should be shared:
	NoSQL DB of email addresses
	SQL DB of error information




We want to test load



	In a farm, there may be 4 different device types. Each device might be a node in a network of xbee connected devices.
		
	


## Currently supports:
### - mps22-an500

## Upcoming support:
### - teensy 4.0
