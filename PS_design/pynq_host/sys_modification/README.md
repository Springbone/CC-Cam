* **wifi.py**:
	+ Editing the configuration in `/etc/rc.local` to let this script run automatically when the PYNQ board is turned on.
* **usbserial.zip**:
	+ image.ub: Replace the file named the same in `/boot` to enable usb-serial drivers.
	Details can be found [here](https://forums.xilinx.com/t5/综合讨论/学生竞赛问题解答专用贴/td-p/900717)	
	+ usbserial.cfg: The detailed list for these drivers is in "usbserial.cfg".
* **dma.py**:
	+ The interputions of VDMA's read and write channels are disabled otherwise errors will be reported in video flow when host file is running. 
	This file is located in lib on PYNQ.
	