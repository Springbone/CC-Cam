# hls_sp文件夹用于使用Vivado HLS 2018.3设计梯度计算的IP核
* generated_ip:
	- 经过C Synthesis生成的ip核压缩包，解压后用Vivado中添加IP位置，在Block Design中加入；
	- 各数据端口用于寻址的寄存器的地址、以及如何读写状态寄存器来控制ip核行为的说明在：<br>
	<ip核文件夹>/drivers/FISTA_GRAD_v1_0/src/xfista_grad_hw.h
* scripts:
	- 最顶层模块FISTA_GRAD在main_static.cpp;
	- fista_static.h内为各种参数的宏定义、各种自定义类型的定义、函数声明；
	- grad.cpp:各子模块（子函数）的定义
	- tb.cpp:用于C Simulation的测试程序，复现工程时需要修改载入二进制测试文件的路径
* test_binfile:
	- 提供一张flower图片和相关的bin文件供C仿真使用，如需测试别的bin文件则在py2hls_test_tools下使用GD.ipynb生成<br>
	仿真结果的验证使用py2hls_test_tools下的log_files进行比对
	- 将仿真结束获得的result.bin用python脚本可以对结果可视化，计算与python计算有一定差别，例如见hls_vs_py_1021.png