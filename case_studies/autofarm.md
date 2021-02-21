Definition of a test case:
	operations = things that the PAF can do

for every object, there are:
	objects = things that operations affect
	obstacles = things within the objects that affect the operation
		affects = [time to complete operation, damage to PAF, accuracy of operation, precision of operation]





(*1) 2008 Unified framework defines four components of an automated farm system:
 1 Seeding
 2 Crop Sensing
	- Data is stored in PADS: "Precision Agriculture Data Set"
 3 Follow-up in response to Crop Sensing
	- A subsystem, responding to PADS and a previously defined desire state, organizes resources to efficiently reduce the delta between current PADS and desired state
 4 Harvesting

We are interested in 2 and 3.
Crop Sensing and Follow-up are performed by isolated autonomous systems, called Precision Autonomous Farming (PAF) units in (*2).

If we desire to change the logic of any one of these systems, it will be difficult to predict how that change will affect other systems that operate in the same space.
If we want to predict whether our change interferes with existing logic, we will need a model to represent the real-world operations of an existing system.
Such a model would require four parts: state for a given time (A), logic that is generated as a result of that state (B), a collection of test-conditions (C), a collection of resultant instances of state created by logic (B) that has been affected by test-conditions (C) (D).

(*1) and (*2) define our "state for a given time" as Precision Agriculture Data Set, or PADS. The PADS would include readings from a soil-sample.
A predictive model might include 
Here, we define the Resultant Precision Agriculture Data Set as an outcome of our existing logic as affected by a test case.	
	TCDN[] (Test Condition)
	PADS
	RPADS = TCDN[i](PADS)
	 
	
The above four components give us a prediction of the real-world result of a change to the component we adjusted.





Citations:
*1 : R. Eaton, J. Katupitiya, K. W. Siew and B. Howarth, "Autonomous Farming: Modeling and Control of Agricultural Machinery in a Unified Framework," 2008 15th International Conference on Mechatronics and Machine Vision in Practice, Auckland, New Zealand, 2008, pp. 499-504, doi: 10.1109i/MMVIP.2008.4749583.
*2: H. Pota, R. Eaton, J. Katupitiya and S. D. Pathirana, "Agricultural robotics: A streamlined approach to realization of Autonomous Farming," 2007 International Conference on Industrial and Information Systems, Peradeniya, Sri Lanka, 2007, pp. 85-90, doi: 10.1109/ICIINFS.2007.4579153.
