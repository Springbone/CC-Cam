# The robot arm control is developed on the base of LeArm51's open source code.  
We use serial port to enable PYNQ to command the arm's motion, so we modify the interface and protocol of serial port which are originally designed to communicate with PC.
* Comparing to the original code, the modified files are listed below:
	- PCMsg.c
	- PCMsg.h
	- PWM.c
	- PWM.h
The added instructions are: `CMD_MY_LEFT`, `CMD_MY_RIGHT`, `CMD_MY_UP`, `CMD_MY_DOWN`;   
the added function is `ServoSetPluseAndTime_my`