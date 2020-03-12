//#define CSIM_DEBUG

#ifndef _PYNQ_FISTA_H_
#define _PYNQ_FISTA_H_

#include <ap_fixed.h>
#include <ap_int.h>
#include "hls_fft.h"
#include "hls_x_complex.h"
#include "hls_math.h"
using namespace hls;
/***************************************/
#define SLT 8 //Slice for Transfer
#define SLM 4 //Slice for Multiplier
/*************************************/
#define DATA_WIDTH 32


#define RAW_HEIGHT 480
#define RAW_WIDTH 640
#define HEIGHT 120
#define WIDTH 160
#define PAD_HEIGHT 256
#define PAD_WIDTH 512
#define STARTI 68
#define STARTJ 176
#define ENDI 187
#define ENDJ 335

#define NORM 128

#define FFT_BUFF_H_B	9
#define FFT_BUFF_V_B	8
#define FFT_BUFF_H 		1<<FFT_BUFF_H_B //512 in horizontal direction
#define FFT_BUFF_V 		1<<FFT_BUFF_V_B //256 in vertical direction

/******************Scaling schedule*************/
#define SCH1 0x18A	//FFT-row 2-9
#define SCH2 0x14A	//FFT-col 2-8
#define SCH3 0x141	//IFFT-row
#define SCH4 0x141	//IFFT-col


#ifdef CSIM_DEBUG
	typedef float FIX_IM;	//fix point
	typedef float FIX_TK;
	typedef float FIX_FFT;
	typedef float FIX_OUT;
#else
	typedef ap_fixed<DATA_WIDTH, 2> FIX_IM; //main type to take place of float
	typedef ap_fixed<DATA_WIDTH, 16> FIX_TK;
	typedef ap_fixed<DATA_WIDTH, 8> FIX_ALPHA;//34.861476685771116
	typedef ap_fixed<DATA_WIDTH, 1> FIX_FFT;
	typedef float FIX_OUT;
#endif

typedef ap_uint<8> uint8;
typedef ap_uint<16> uint16;
typedef hls::x_complex<FIX_FFT > cmpxData;

/************************FFT*************************************/

// configurable params
const char FFT_INPUT_WIDTH                     = DATA_WIDTH;//24//16
const char FFT_OUTPUT_WIDTH                    = FFT_INPUT_WIDTH;
const char FFT_CONFIG_WIDTH                    = 16;//16
const char FFT_NFFT_MAX_ROW                    = 9;//512-->9 ,256-->8
const char FFT_NFFT_MAX_COL                    = 8;//512-->9 ,256-->8
/*******************************************/
struct config1 : hls::ip_fft::params_t {
	static const unsigned input_width = FFT_INPUT_WIDTH;
	static const unsigned output_width = FFT_OUTPUT_WIDTH;
	static const unsigned status_width = 8;
    static const unsigned ordering_opt = hls::ip_fft::natural_order;
    static const unsigned config_width = FFT_CONFIG_WIDTH;
    static const unsigned phase_factor_width = 24;//float-->24bits; data 16bits-->16bits phase
    static const unsigned max_nfft = FFT_NFFT_MAX_ROW;

};
struct config2 : hls::ip_fft::params_t {
	static const unsigned input_width = FFT_INPUT_WIDTH;
	static const unsigned output_width = FFT_OUTPUT_WIDTH;
	static const unsigned status_width = 8;
    static const unsigned ordering_opt = hls::ip_fft::natural_order;
    static const unsigned config_width = FFT_CONFIG_WIDTH;

    static const unsigned phase_factor_width = 24;//float-->24bits; data 16bits-->16bits phase
    static const unsigned max_nfft = FFT_NFFT_MAX_COL;
};

typedef hls::ip_fft::config_t<config1> config_t_1;
typedef hls::ip_fft::status_t<config1> status_t_1;
typedef hls::ip_fft::config_t<config2> config_t_2;
typedef hls::ip_fft::status_t<config2> status_t_2;

/*********************FUNCTIONS************************************************/
void FISTA_GRAD(
		float b_axi[HEIGHT][WIDTH],//[0-1]-->FIX_FFT
		cmpxData H_axi[PAD_HEIGHT][PAD_WIDTH],//[0]:real,[1]:image//[0-1]-->cmpxData<FIX_FFT>
		float vk_axi[PAD_HEIGHT][PAD_WIDTH],//[0-1]-->cmpxData<FIX_FFT>
		cmpxData vk_mid[PAD_HEIGHT][PAD_WIDTH],
		float grad_out[PAD_HEIGHT][PAD_WIDTH]//[0-1]FIX_FFT-->float
);
void fft_one_row(
		bool direction,
		cmpxData fft_buf_h_1[PAD_WIDTH],
		cmpxData vk_mid[PAD_HEIGHT][PAD_WIDTH],int row);
void fft_one_col(bool direction,
		cmpxData vk_axi[PAD_HEIGHT][PAD_WIDTH],
		cmpxData fft_buf_v_2[PAD_HEIGHT],int col);
//void fft_col(bool direction,cmpxData vk_axi[PAD_HEIGHT][PAD_WIDTH],
//		cmpxData vk_mid[PAD_HEIGHT][PAD_WIDTH]);
/*************************************/
void load_row_shift_real(cmpxData line_in[PAD_WIDTH],
		float dim2[PAD_HEIGHT][PAD_WIDTH],int row);
void load_row_shift_cmpx(cmpxData line_in[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row);
void load_row_noshift_cmpx(cmpxData line_in[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row);
void push_row_shift(cmpxData line_out[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row);
void push_row_noshift(cmpxData line_out[PAD_WIDTH],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int row);
void load_col_shift(cmpxData line_in[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col);
void load_col_noshift(cmpxData line_in[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col);
void push_col_shift(cmpxData line_out[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col);
void push_col_noshift(cmpxData line_out[PAD_HEIGHT],
		cmpxData dim2[PAD_HEIGHT][PAD_WIDTH],int col);
void push_col_shift_real(cmpxData line_out[PAD_HEIGHT],
		float dim2[PAD_HEIGHT][PAD_WIDTH],int col);
void load_b_row(FIX_FFT b_row[WIDTH],//output
		float b_axi[WIDTH]);
void get_diff_clear_row(cmpxData vk_axi_in[PAD_WIDTH],//input
		float b_axi_row[WIDTH],//input
		cmpxData vk_axi_out[PAD_WIDTH]);
void clean_vk_row(cmpxData vk[PAD_WIDTH]);
void push_vk_row(cmpxData vk_row[PAD_WIDTH],//output
		cmpxData vk_mid[PAD_WIDTH]);
void dot_multiply_H_row(bool no_adj,
		cmpxData vk_in[PAD_WIDTH],//mem
		cmpxData H_axi[PAD_WIDTH],
		cmpxData vk_out[PAD_WIDTH]);
#endif

