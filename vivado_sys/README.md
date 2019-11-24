# 本文件包含用Vivado 2018.3复现整个Block Design需要的全部设计文件
sys_1116.pdf: block design概览<br>
sys_1115.tcl: 使用tcl文件可以复现整个工程，在那之前需要先定位好所有用到的ip的位置<br>
const_cam: 引脚约束文件，对应的是PYNQ-Z2板卡<br>
design_1.bd: block design文件<br>
ips文件夹：包含摄像头驱动ip（内含源码），digilent在github上提供的rgb2dvi的显示驱动ip和tmds_v1_0的interface<br>
	(注意：hls生成的两个ip核在../hls_sp/generated_ip文件夹中)
