#include "fista_static.h"
//#define CSIM_DEBUG_MID

/********************************fftrow*********************/
void dummy_proc_fe(
    cmpxData in[PAD_WIDTH],
    cmpxData out[PAD_WIDTH]
	)
{
#pragma HLS INTERFACE ap_fifo depth=512 port=out
    int i;
    for (i=0; i< PAD_WIDTH; i++)
        out[i] = in[i];
}
void dummy_proc_be(
    cmpxData in[PAD_WIDTH],
    cmpxData out[PAD_WIDTH])
{
#pragma HLS INTERFACE ap_fifo depth=512 port=in
    int i;
    for (i=0; i< PAD_WIDTH; i++)
        out[i] = in[i];
}
void dummy_proc_fe_col(
    cmpxData in[PAD_HEIGHT],
    cmpxData out[PAD_HEIGHT]
	)
{
#pragma HLS INTERFACE ap_fifo depth=256 port=out
    int i;
    for (i=0; i< PAD_HEIGHT; i++)
        out[i] = in[i];
}
void dummy_proc_be_col(
    cmpxData in[PAD_HEIGHT],
    cmpxData out[PAD_HEIGHT])
{
#pragma HLS INTERFACE ap_fifo depth=256 port=in
    int i;
    for (i=0; i< PAD_HEIGHT; i++)
        out[i] = in[i];
}
void fft_top_row(
	bool direction,//1:fft,0:ifft
    cmpxData in[PAD_WIDTH],
    cmpxData out[PAD_WIDTH]
)
{
#pragma HLS INTERFACE ap_fifo depth=512 port=in,out
#pragma HLS DATAFLOW
	config_t_1 fft_config;
	status_t_1 fft_status;
    if(direction){
    	fft_config.setDir(1);//FFT
    	fft_config.setSch(SCH1);
    }
    else{
    	fft_config.setDir(0);//IFFT
    	fft_config.setSch(SCH3);
    }
	// FFT IP
    hls::fft<config1>(in, out, &fft_status, &fft_config);
}
void fft_top_col(
	bool direction,
    cmpxData in[PAD_HEIGHT],
    cmpxData out[PAD_HEIGHT]
)
{
#pragma HLS INTERFACE ap_fifo depth=256 port=in,out
#pragma HLS DATAFLOW
	config_t_2 fft_config;
	status_t_2 fft_status;
    if(direction){
    	fft_config.setDir(1);//FFT
    	fft_config.setSch(SCH2);
    }
    else{
    	fft_config.setDir(0);//IFFT
    	fft_config.setSch(SCH4);
    }
    // FFT IP
    hls::fft<config2>(in, out, &fft_status, &fft_config);
}


/***********************************row*****************************/
void load_row_shift_real(cmpxData line_in[PAD_WIDTH],
		float dim2[PAD_HEIGHT][PAD_WIDTH],int row)
{//FFT
	for(int i=0;i<PAD_WIDTH/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			if(i*SLT+s<PAD_WIDTH/2){
				line_in[i*SLT+s]=dim2[row][i*SLT+s+(PAD_WIDTH/2)];
			}
			else{
				line_in[i*SLT+s]=dim2[row][i*SLT+s-(PAD_WIDTH/2)];
			}
		}
	}

}
void load_row_shift_cmpx(cmpxData line_in[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row)
{//FFT
	for(int i=0;i<PAD_WIDTH/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			if(i*SLT+s<PAD_WIDTH/2){
				line_in[i*SLT+s] = dim2[row][i*SLT+s+(PAD_WIDTH/2)].real();
			}
			else{
				line_in[i*SLT+s] = dim2[row][i*SLT+s-(PAD_WIDTH/2)].real();
			}
		}
	}
}
void load_row_noshift_cmpx(cmpxData line_in[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row)
{//IFFT
	for(int i=0;i<PAD_WIDTH/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			line_in[i*SLT+s] = dim2[row][i*SLT+s];
		}
	}
}
void push_row_shift(cmpxData line_out[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row)
{//IFFT
	for(int i=0;i<PAD_WIDTH/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			if(i*SLT+s<PAD_WIDTH/2){
				dim2[row][i*SLT+s] = line_out[i*SLT+s+(PAD_WIDTH/2)];
			}
			else{
				dim2[row][i*SLT+s] = line_out[i*SLT+s-(PAD_WIDTH/2)];
			}
		}

	}
}
void push_row_noshift(cmpxData line_out[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row)
{//FFT
	for(int i=0;i<PAD_WIDTH/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			dim2[row][i*SLT+s] = line_out[i*SLT+s];
		}

	}
}
void push_row(bool dir,cmpxData line_out[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row)
{
	if(dir){//FFT
		push_row_noshift(line_out,dim2,row);
	}
	else{//IFFT
		push_row_shift(line_out,dim2,row);
	}
}
/**********************col********************************/
void load_col_shift(cmpxData line_in[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col)
{//FFT
	for(int i=0;i<PAD_HEIGHT/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			if(i*SLT+s<PAD_HEIGHT/2){
				line_in[i*SLT+s]=dim2[i*SLT+s+(PAD_HEIGHT/2)][col];
			}
			else{
				line_in[i*SLT+s]=dim2[i*SLT+s-(PAD_HEIGHT/2)][col];
			}
		}
	}
}
void load_col_noshift(cmpxData line_in[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col)
{//IFFT
	for(int i=0;i<PAD_HEIGHT/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL

			line_in[i*SLT+s]=dim2[i*SLT+s][col];
		}
	}//no shift here
}
void load_col(bool dir,cmpxData line_in[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col)
{//IFFT
	if(dir){
		load_col_shift(line_in,dim2,col);
	}
	else{
		load_col_noshift(line_in,dim2,col);
	}

}
void push_col_shift(cmpxData line_out[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col)
{//IFFT
	for(int i=0;i<PAD_HEIGHT/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			if(i*SLT+s<PAD_HEIGHT/2){
				dim2[i*SLT+s][col]=line_out[i*SLT+s+(PAD_HEIGHT/2)];
			}
			else{

				dim2[i*SLT+s][col]=line_out[i*SLT+s-(PAD_HEIGHT/2)];
			}
		}

	}
}
void push_col_shift_real(cmpxData line_out[PAD_HEIGHT],
		float dim2[PAD_HEIGHT][PAD_WIDTH],int col)
{//IFFT
	for(int i=0;i<PAD_HEIGHT/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			if(i*SLT+s<PAD_HEIGHT/2){
				dim2[i*SLT+s][col]=line_out[i*SLT+s+(PAD_HEIGHT/2)].real().to_float();
			}
			else{
				dim2[i*SLT+s][col]=line_out[i*SLT+s-(PAD_HEIGHT/2)].real().to_float();
			}
		}

	}
}
void push_col_noshift(cmpxData line_out[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col)
{//FFT
	for(int i=0;i<PAD_HEIGHT/SLT;i++){
#pragma HLS PIPELINE
		for(int s=0;s<SLT;s++){
#pragma HLS UNROLL
			dim2[i*SLT+s][col]=line_out[i*SLT+s];
		}

	}
}

/******************************************************************/
void push_vk_row(cmpxData vk_row[PAD_WIDTH],//output
		cmpxData vk_mid[PAD_WIDTH])//input
{
	for(int col=0;col<PAD_WIDTH/SLM;col++){
#pragma HLS PIPELINE
		for(int i=0;i<SLM;i++){
#pragma HLS UNROLL
			vk_mid[col*SLM+i] = vk_row[col*SLM+i];
		}

	}
}
void load_vk_row(cmpxData vk_row[PAD_WIDTH],//output
		cmpxData vk_axi[PAD_WIDTH]){
	for(int col=0;col<PAD_WIDTH;col++){
#pragma HLS PIPELINE
		vk_row[col]=vk_axi[col];
	}
}
void load_b_row(FIX_FFT b_row[WIDTH],//output
		float b_axi[WIDTH])//input
{
	for(int col=0;col<WIDTH;col++){
#pragma HLS PIPELINE
		b_row[col]=b_axi[col];
	}
}
void clean_vk_row(cmpxData vk[PAD_WIDTH])//input
{
	for(int col=0;col<PAD_WIDTH;col++){
#pragma HLS PIPELINE
		vk[col]=0;
	}
}
void diff_clear(cmpxData vk_in[PAD_WIDTH],
		FIX_FFT b_row[WIDTH],
		cmpxData vk_out[PAD_WIDTH]){
#pragma HLS ARRAY_PARTITION variable=vk_in 	cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=b_row 	cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=vk_out 	cyclic factor=8 dim=1
	for(int col=0;col<PAD_WIDTH/8;col++){
#pragma HLS PIPELINE
		for(int i=0;i<8;i++){
#pragma HLS UNROLL
			if(col*8+i>=STARTJ && col*8+i<=ENDJ){
				vk_out[col*8+i] =vk_in[col*8+i]- b_row[col*8+i-176];
			}
			else{
				vk_out[col*8+i] = 0;
			}
		}
	}
}
void get_diff_clear_row(cmpxData vk_axi_in[PAD_WIDTH],//input
		float b_axi_row[WIDTH],//input
		cmpxData vk_axi_out[PAD_WIDTH])//output
{
FIX_FFT b_row[WIDTH];
cmpxData tmp_vk_in[PAD_WIDTH];
cmpxData tmp_vk_out[PAD_WIDTH];
#pragma HLS DATAFLOW
	load_b_row(b_row,b_axi_row);
	load_vk_row(tmp_vk_in,vk_axi_in);
	diff_clear(tmp_vk_in,b_row,tmp_vk_out);
	push_vk_row(tmp_vk_out,vk_axi_out);
}

void fft_one_row(
		bool direction,
		cmpxData fft_buf_h_1[PAD_WIDTH],
		cmpxData vk_mid[PAD_HEIGHT][PAD_WIDTH],int row){
#pragma HLS DATAFLOW
	cmpxData fft_buf_h_2[PAD_WIDTH];//mem
	cmpxData fft_buf_h_3[PAD_WIDTH];
	cmpxData fft_buf_h_4[PAD_WIDTH];//fifo

	dummy_proc_fe(fft_buf_h_1,fft_buf_h_3);
	fft_top_row(direction,fft_buf_h_3,fft_buf_h_4);//FFT_h
	dummy_proc_be(fft_buf_h_4,fft_buf_h_2);
	push_row(direction,fft_buf_h_2,vk_mid,row);
}
void fft_one_col(bool direction,
		cmpxData vk_axi[PAD_HEIGHT][PAD_WIDTH],
		cmpxData fft_buf_v_2[PAD_HEIGHT],int col){
#pragma HLS DATAFLOW
	cmpxData fft_buf_v_1[PAD_HEIGHT];
	cmpxData fft_buf_v_3[PAD_HEIGHT];
	cmpxData fft_buf_v_4[PAD_HEIGHT];//fifo

	load_col(direction,fft_buf_v_1,vk_axi,col);
	dummy_proc_fe_col(fft_buf_v_1,fft_buf_v_3);
	fft_top_col(direction,fft_buf_v_3,fft_buf_v_4);//FFT_h
	dummy_proc_be_col(fft_buf_v_4,fft_buf_v_2);
}
void load_H(bool no_adj,cmpxData H_row[PAD_WIDTH],//output
		cmpxData H_axi[PAD_WIDTH]){
	for(int col=0;col<PAD_WIDTH/SLM;col++){
#pragma HLS PIPELINE
		for(int i=0;i<SLM;i++){
#pragma HLS UNROLL
			if(no_adj){
				H_row[col*SLM+i] = H_axi[col*SLM+i];
			}
			else{
				H_row[col*SLM+i]=cmpxData(H_axi[col*SLM+i].real(),-H_axi[col*SLM+i].imag());
			}
		}
	}
}

void dot_multiply_H_multi(cmpxData vk_in[PAD_WIDTH],//in
		cmpxData H_row[PAD_WIDTH],
		cmpxData vk_out[PAD_WIDTH]){
#pragma HLS ARRAY_PARTITION variable=vk_in 	cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=H_row 	cyclic factor=8 dim=1
#pragma HLS ARRAY_PARTITION variable=vk_out 	cyclic factor=8 dim=1
	for(int col=0;col<PAD_WIDTH/8;col++){
#pragma HLS PIPELINE
		for(int i=0;i<8;i++){
#pragma HLS UNROLL
			vk_out[col*8+i] = vk_in[col*8+i]*H_row[col*8+i];
		}

	}
}
void dot_multiply_H_row(bool no_adj,
		cmpxData vk_in[PAD_WIDTH],//mem
		cmpxData H_axi[PAD_WIDTH],
		cmpxData vk_out[PAD_WIDTH])//mem
{
cmpxData vk_tmp[PAD_WIDTH];
cmpxData hrow_buf[PAD_WIDTH];//mem
cmpxData vkrow_buf[PAD_WIDTH];

#pragma HLS DATAFLOW
	load_H(no_adj,hrow_buf,H_axi);
	load_vk_row(vkrow_buf,vk_in);
	dot_multiply_H_multi(vkrow_buf,hrow_buf,vk_tmp);
	push_vk_row(vk_tmp,vk_out);
}
