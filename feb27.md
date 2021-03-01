# notebook:

## Feb 25

constraints: one emulated device

story: user wants to run code on emulated device.
	User wants to see the gpio output from their code on the emulated device.
	 -- Later: User wants to see the output under different circumstance 
	User uploads code
	GPIO output is returned to user
		--> displayed as output in CLI
		--> formatted into a file 
			--> format can show: 
				- pin number
				- time between GPIO outputs
				- (memory location that prompted output?)


### user story:

User wants to run code on an500.
user launches application.
	WebApp pod wakes up.
	QEMU pod wakes up.
User sends .hex file to WebApp
	WebApp sends .hex to QEMU pod.

	QEMU pod begins an500 emulation with .hex file
	events sent to GPIO are formatted into file format
	file output is returned to User
User checks output against their expectations, iterates.

	



### UnMade components:

	[] an500 base image
	--> what do I need in order to get the .hex file to the machine?
		WebApp has .hex on local dir
		an500 curls .hex from the server
		
		okay. 
			[x] [] we need a docker image for the an500 and for the web_app.
			then, we need to make deployment yamls for each pod
			then, we need to write service nodeport yamls to give each pod an ip 
				and make the frontend accessible to the host
		next:
			How do we get the ip of the webserver pod?



	NodePort service
	GPIO device



## Networking

frontend pod:	
	- webserver port:		8000
		- rest api within it
		- mosquitto client
	- mosquitto broker:		1863
	- xxxx?

machine emulator:
	- qemu monitor port:	7000
	- mosquitto client:		1863
	- xxxx?

database:
	- port:					????



## tasks:

Figure out how to curl cmd-hub from the host machine.
	- you have: 
		a LoadBalancer k8s service
			-- external ip is stuck in pending
				--> consult https://www.qwiklabs.com/focuses/557?parent=catalog
		an exposed port

Write a nodeport service for cmd-hub deployment
	Then, emu_machine can curl cmd-hub
--> you MIGHT not need a service for emu_machine YET












## Before Feb 23

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