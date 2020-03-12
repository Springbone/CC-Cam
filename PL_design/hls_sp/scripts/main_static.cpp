#include "fista_static.h"

//#define CSIM_DEBUG_MID
void TRANS_FIX(float H_float_re[PAD_HEIGHT][PAD_WIDTH],
		float H_float_im[PAD_HEIGHT][PAD_WIDTH],
		cmpxData H_fix[PAD_HEIGHT][PAD_WIDTH]
		){
#pragma HLS INTERFACE m_axi depth=256*512 		port=H_float_re		offset=slave	bundle=FLT_IN
#pragma HLS INTERFACE m_axi depth=256*512 		port=H_float_im		offset=slave	bundle=FLT_IN
#pragma HLS INTERFACE m_axi depth=256*512 		port=H_fix		offset=slave	bundle=FIX_OUT
#pragma HLS INTERFACE s_axilite register			port=return			bundle=CTRL
	for(int row=0;row<PAD_HEIGHT;row++){
		for(int col=0;col<PAD_WIDTH;col++){
#pragma HLS PIPELINE
			H_fix[row][col].real(H_float_re[row][col]);
			H_fix[row][col].imag(H_float_im[row][col]);
		}
	}
}
/************************************************/
void FISTA_GRAD(
		float b_axi[HEIGHT][WIDTH],//[0-1]-->FIX_FFT
		cmpxData H_axi[PAD_HEIGHT][PAD_WIDTH],//[0]:real,[1]:image//[0-1]-->cmpxData<FIX_FFT>
		float vk_axi[PAD_HEIGHT][PAD_WIDTH],//[0-1]-->cmpxData<FIX_FFT>
		cmpxData vk_mid[PAD_HEIGHT][PAD_WIDTH],
		float grad_out[PAD_HEIGHT][PAD_WIDTH]//[0-1]FIX_FFT-->float
){
#pragma HLS INTERFACE axis depth=120*160 		port=b_axi		offset=slave	bundle=INPUT
#pragma HLS INTERFACE axis depth=256*512	port=H_axi		offset=slave	bundle=INPUT
#pragma HLS INTERFACE axis depth=256*512		port=vk_axi		offset=slave	bundle=INPUT
#pragma HLS INTERFACE axis depth=256*512		port=grad_out	offset=slave	bundle=OUTPUT
#pragma HLS INTERFACE axis depth=256*512		port=vk_mid		offset=slave	bundle=OUTPUT

#pragma HLS INTERFACE s_axilite register			port=return			bundle=CONTROL

//#pragma HLS INTERFACE ap_fifo depth=160 port=b_row
/*****************calcuA******************************/
#ifdef CSIM_DEBUG_MID
	cout<<"*****************************VK_MID FFT_FIRST TEST***120*******0**"<<endl;
	cout<<"vk[120]["<<20<<"]="<<vk_axi[120][20]<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<vk_axi[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<vk_axi[120][STARTJ+40]<<endl;
	cout<<"vk[120]["<<PAD_WIDTH-20<<"]="<<vk_axi[120][PAD_WIDTH-20]<<endl;
	cout<<"************************************************"<<endl;
#endif
/******************BUFFERS*******************/
cmpxData fft_buf_h_1[PAD_WIDTH];
cmpxData fft_buf_v_2[PAD_HEIGHT];
//cmpxData H_row[PAD_WIDTH];
//cmpxData vk_row[PAD_WIDTH];

//FIX_FFT b_row[WIDTH];

	FFT_0:{
			FFT_h_0:for(int row=0;row<PAD_HEIGHT;row++){
				load_row_shift_real(fft_buf_h_1,vk_axi,row);
				fft_one_row(1,fft_buf_h_1,vk_mid,row);
			}
			FFT_v_0:for(int col=0;col<PAD_WIDTH;col++){
				fft_one_col(1,vk_mid,fft_buf_v_2,col);
				push_col_noshift(fft_buf_v_2,vk_mid,col);
			}
		}
#ifdef CSIM_DEBUG_MID
	cout<<"*****************************VK_MID FFT_FIRST TEST***120*******0.5**"<<endl;
	cout<<"vk[120]["<<20<<"]="<<vk_mid[120][20]<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<vk_mid[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<vk_mid[120][STARTJ+40]<<endl;
	cout<<"vk[120]["<<PAD_WIDTH-20<<"]="<<vk_mid[120][PAD_WIDTH-20]<<endl;
	cout<<"************************************************"<<endl;
#endif
			/******************dot-multiply H********************/
		dot_multiply:for(int row=0;row<PAD_HEIGHT;row++){
				dot_multiply_H_row(1,vk_mid[row],H_axi[row],vk_mid[row]);
			}
#ifdef CSIM_DEBUG_MID
	cout<<"*****************************VK_MID FFT_FIRST TEST***120*******1**"<<endl;
	cout<<"vk[120]["<<20<<"]="<<vk_mid[120][20]<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<vk_mid[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<vk_mid[120][STARTJ+40]<<endl;
	cout<<"vk[120]["<<PAD_WIDTH-20<<"]="<<vk_mid[120][PAD_WIDTH-20]<<endl;
	cout<<"************************************************"<<endl;
#endif
	/******************IFFT-FFTSHIFT*****************/
	IFFT_0:{
			IFFT_h_0:for(int row=0;row<PAD_HEIGHT;row++){
				load_row_noshift_cmpx(fft_buf_h_1,vk_mid,row);
				fft_one_row(0,fft_buf_h_1,vk_mid,row);
			}
			IFFT_v_0:for(int col=0;col<PAD_WIDTH;col++){
				fft_one_col(0,vk_mid,fft_buf_v_2,col);
				push_col_shift(fft_buf_v_2,vk_mid,col);
			}
		}

#ifdef CSIM_DEBUG_MID
	cout<<"*****************************VK_MID FFT_FIRST TEST***120*******2**"<<endl;
	cout<<"vk[120]["<<20<<"]="<<vk_mid[120][20]<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<vk_mid[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<vk_mid[120][STARTJ+40]<<endl;
	cout<<"vk[120]["<<PAD_WIDTH-20<<"]="<<vk_mid[120][PAD_WIDTH-20]<<endl;
	cout<<"************************************************"<<endl;
#endif
		/***************Get diff and clear*********************************/
				//#pragma???
				diff_clear:for(int row=0;row<PAD_HEIGHT;row++){
					if(row>=STARTI && row<=ENDI){
//						load_b_row(b_row,b_axi[row-STARTI]);
//						get_diff_clear_row(vk_mid[row],b_row);
						get_diff_clear_row(vk_mid[row],b_axi[row-STARTI],vk_mid[row]);
					}
					else{
						clean_vk_row(vk_mid[row]);
					}
				}
#ifdef CSIM_DEBUG_MID
	cout<<"*****************************VK_MID FFT_FIRST TEST***120*******3**"<<endl;
	cout<<"vk[120]["<<20<<"]="<<vk_mid[120][20]<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<vk_mid[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<vk_mid[120][STARTJ+40]<<endl;
	cout<<"vk[120]["<<PAD_WIDTH-20<<"]="<<vk_mid[120][PAD_WIDTH-20]<<endl;
	cout<<"************************************************"<<endl;
#endif
/*****************calcuAHerm**************************************************/
		/*****************IFFTSHIFT-FFT**************/
	FFT_1:{
			FFT_h_1:for(int row=0;row<PAD_HEIGHT;row++){
				load_row_shift_cmpx(fft_buf_h_1,vk_mid,row);
				fft_one_row(1,fft_buf_h_1,vk_mid,row);
			}
			FFT_v_1:for(int col=0;col<PAD_WIDTH;col++){
				fft_one_col(1,vk_mid,fft_buf_v_2,col);
				push_col_noshift(fft_buf_v_2,vk_mid,col);
			}
		}

#ifdef CSIM_DEBUG_MID
	cout<<"*****************************VK_MID FFT_FIRST TEST***120*******4**"<<endl;
	cout<<"vk[120]["<<20<<"]="<<vk_mid[120][20]<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<vk_mid[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<vk_mid[120][STARTJ+40]<<endl;
	cout<<"vk[120]["<<PAD_WIDTH-20<<"]="<<vk_mid[120][PAD_WIDTH-20]<<endl;
	cout<<"************************************************"<<endl;
#endif
		/******************dot-multiply Hadj***************************/
		dot_multiply_HERM:for(int row=0;row<PAD_HEIGHT;row++){
//				dot_multiply_H_row(0,vk_mid[row],H_axi[row]);
				dot_multiply_H_row(0,vk_mid[row],H_axi[row],vk_mid[row]);


			}
#ifdef CSIM_DEBUG_MID
	cout<<"*****************************VK_MID FFT_FIRST TEST***120*******5**"<<endl;
	cout<<"vk[120]["<<20<<"]="<<vk_mid[120][20]<<endl;
	cout<<"vk[120]["<<STARTJ+20<<"]="<<vk_mid[120][STARTJ+20]<<endl;
	cout<<"vk[120]["<<STARTJ+40<<"]="<<vk_mid[120][STARTJ+40]<<endl;
	cout<<"vk[120]["<<PAD_WIDTH-20<<"]="<<vk_mid[120][PAD_WIDTH-20]<<endl;
	cout<<"************************************************"<<endl;
#endif
			/******************IFFT-FFTSHIFT*****************/
	IFFT_1:{
			IFFT_h_1:for(int row=0;row<PAD_HEIGHT;row++){
				load_row_noshift_cmpx(fft_buf_h_1,vk_mid,row);
				fft_one_row(0,fft_buf_h_1,vk_mid,row);
			}
			IFFT_v_1:for(int col=0;col<PAD_WIDTH;col++){
				fft_one_col(0,vk_mid,fft_buf_v_2,col);
				push_col_shift_real(fft_buf_v_2,grad_out,col);
			}
		}



}

