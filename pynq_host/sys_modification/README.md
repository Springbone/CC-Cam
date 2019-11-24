* wifi:
	+ wifi.py: 结合对/etc/rc.local的配置，使开机自动连接指定wifi；更换WIFI名需要修改脚本中的SSID名称
* usbserial.zip:
	+ image.ub: 用此替换pynq v2.3镜像的FAT32分区文件下的同名文件即可开启ps端的串口驱动
	+ usbserial.cfg: 具体驱动配置列表
* dma.py:
	+ 对pynq的lib下dma.py进行了修改，禁用了vdma的读写通道的中断
	