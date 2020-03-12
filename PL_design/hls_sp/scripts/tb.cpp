#include <iostream>
#include <fstream>
using namespace std;
#include "fista_static.h"

float H_axi[PAD_HEIGHT][PAD_WIDTH][2];
FIX_FFT H_fix_dim2[2][PAD_HEIGHT][PAD_WIDTH];
cmpxData H_axi_cmpx[PAD_HEIGHT][PAD_WIDTH];
cmpxData vk_mid[PAD_HEIGHT][PAD_WIDTH];
float b_axi[HEIGHT][WIDTH];
float vk_axi[PAD_HEIGHT][PAD_WIDTH];
float grad_out[PAD_HEIGHT][PAD_WIDTH];
int main(){

	cout<<"start"<<endl;
	std::ifstream bin_file("F:/PLD_19/HLS_FISTA/test/flower_float.bin", std::ios::in | std::ios::binary);
	if(!bin_file) cout<<"Image Bin File does not exist!"<<endl;
	else cout<<"Gray Image Bin File loaded!"<<endl;
	bin_file.read((char*)(*b_axi),  HEIGHT*WIDTH*sizeof(float));
	bin_file.close();
	cout<<"**************B TEST******************"<<endl;
	cout<<"vk[52]["<<20<<"]="<<b_axi[52][20]<<endl;
	cout<<"vk[52]["<<40<<"]="<<b_axi[52][40]<<endl;


	std::ifstream H_file("F:/PLD_19/HLS_FISTA/test/H_psf_divnorm_flower_trans.bin", std::ios::in | std::ios::binary);
	if(!H_file) cout<<"H Bin File does not exist!"<<endl;
	else cout<<"H Bin File loaded!"<<endl;
	H_file.read((char*)(**H_axi),  PAD_HEIGHT*PAD_WIDTH*2*sizeof(float));
	H_file.close();
	for(int row=0;row<PAD_HEIGHT;row++){
		for(int col=0;col<PAD_WIDTH;col++){
			H_axi_cmpx[row][col]=cmpxData(H_axi[row][col][0],H_axi[row][col][1]);
			H_fix_dim2[0][row][col]=H_axi[row][col][0];
			H_fix_dim2[1][row][col]=H_axi[row][col][1];
		}
	}
	std::ofstream H_bin("F:/PLD_19/HLS_FISTA/test/H_fix1031.bin", std::ios::out | std::ios::binary);
	if(!H_bin) cout<<"Cannot create H_bin File!"<<endl;
	else{
		H_bin.write((char*)(**H_fix_dim2),  PAD_HEIGHT*PAD_WIDTH*2*sizeof(FIX_FFT));
		H_bin.close();
		cout<<"Created H_fix.bin!"<<endl;
	}
	cout<<"***********************H TEST**********************************"<<endl;
	cout<<"H_in[1][2]= "<<H_axi_cmpx[1][2]<<endl;
	cout<<"H_in[2][3]= "<<H_axi_cmpx[2][3]<<endl;
	cout<<"H_in[127][255]= "<<H_axi_cmpx[127][255]<<endl;
	cout<<"***********************H bin TEST**********************************"<<endl;
	cout<<"H_fix[0][1][2]= "<<H_fix_dim2[0][1][2]<<endl;
	cout<<"H_fix[1][2][3]= "<<H_fix_dim2[1][2][3]<<endl;
	cout<<"H_fix[1][127][255]= "<<H_fix_dim2[1][127][255]<<endl;
	cout<<"***************************************************************"<<endl;


	std::ifstream vk_file("F:/PLD_19/HLS_FISTA/test/vk_flower_iter0.bin", std::ios::in | std::ios::binary);
	if(!vk_file) cout<<"vk Bin File does not exist!"<<endl;
	else cout<<"vk Bin File loaded!"<<endl;
	vk_file.read((char*)(*vk_axi),  PAD_HEIGHT*PAD_WIDTH*sizeof(float));
	vk_file.close();
	cout<<"***********************vk TEST**********************************"<<endl;
	cout<<"vk_in[0][0]= "<<vk_axi[0][0]<<endl;
	cout<<"vk_in[128][335]= "<<vk_axi[128][335]<<endl;
	cout<<"vk_in[128][336]= "<<vk_axi[128][336]<<endl;
	cout<<"***************************************************************"<<endl;
	/******************************************************************/

	FISTA_GRAD(
			b_axi,//[0-1]-->FIX_FFT
			H_axi_cmpx,//[0]:real,[1]:image//[0-1]-->cmpxData<FIX_FFT>
			vk_axi,//[0-1]-->cmpxData<FIX_FFT>
			vk_mid,
			grad_out//[0-1]FIX_FFT-->float
	);


	cout<<"**************GRAD OUT TEST**********120*******6**********"<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<grad_out[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<grad_out[120][STARTJ+40]<<endl;
	cout<<"***********END************************************"<<endl;

	/****************save result as bin file**************************/
	std::ofstream result_bin("F:/PLD_19/HLS_FISTA/test/result.bin", std::ios::out | std::ios::binary);
	if(!result_bin) cout<<"Cannot create Result Bin File!"<<endl;
	else{
		result_bin.write((char*)(*grad_out),  HEIGHT*WIDTH*sizeof(float));
		result_bin.close();
		cout<<"Created result.bin!"<<endl;
	}

}
