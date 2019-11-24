# 设计文件归档说明

* paper_refer: 散射体成像理论来源和参考开源项目地址
* hls_sp: 梯度计算ip和定点数转化ip的hls设计文件
* py2hls_test_tools: hls设计与python对照，进行ip核功能性验证的辅助脚本
* vivado_sys: vivado中系统硬核布局，HDMI显示、摄像头驱动ip核
* pynq_host: jupyter notebook交互式主控文件，对linux系统配置的修改
* lobot_arm_51：机械臂51驱动板控制代码

## 复现工程需要的环境
1. Vivado 2018.3<br>
2. pynq-z2的v2.3镜像<br>
3. Keil uVision 4(或5也可以)来生成机械臂的单片机控制程序<br>
4. PC上的Python 3.6：<br>
	1. opencv-python 3.4.3.18<br>
	2. numpy 1.16.4 <br>
	3. matplotlib 3.1.1 <br>
	4. Pillow 5.4.1<br>
	5. ipywidgets 7.4.2<br>
5. PC上需要能够生成jupyter notebook环境来运行ipynb文件<br>
6. pynq上的Python3.6需要进一步安装：<br>
	1. pyserial<br>
	2. ipywidgets<br>
