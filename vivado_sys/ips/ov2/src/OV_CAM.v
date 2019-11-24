`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/10 20:28:48
// Design Name: 
// Module Name: OV_CAM_TOP
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module OV_CAM #(
    parameter CAMERA_MODEL = 5640,
    parameter CLOCK_FREQ = 100,
    parameter [15:0]DVPHO = 640, 
    parameter [15:0]DVPVO=480
    )
    (
    input   clock,
    input   reset,
    input   start,
    output  ready,
    output  done,
    output  [7:0] data_out,
    input   sccb_sda_i,
    output  sccb_sda_o,
    output  sccb_sda_t,
    input   sccb_scl_i,
    output  sccb_scl_o,
    output  sccb_scl_t,
    output  resetn_out,
    output  pwdn_out,
    input   pclk,
    input   vsync,
    input   href,
    input   [7:0] d_in,
`ifdef BRAM_OUT
    output  [15:0] pixel_data_out,
    output  [18:0] address_out,
`else
    output  [23:0] pixel_data_out,
    output  hsync_out,
    output  vsync_out,
    output  pclk_out,
`endif
    output  we
    );    
    
    localparam REGADDR_WIDTH = (CAMERA_MODEL==5640)?16:8;
    
    wire    sccb_clk;
    wire    sccb_start;
    wire    sccb_done;
    wire    [7:0] devaddr;
    wire    [REGADDR_WIDTH-1:0] regaddr;
    wire    [7:0] wrdata;
    wire    rising;
    wire    falling;
    
    assign sccb_scl_t = 0;        
    
    OV_CAM_SCCB #(REGADDR_WIDTH) 
        sccb (
        .clk(sccb_clk),
        .reset(reset),
        .start(sccb_start),
        .done(sccb_done),
        .devaddr(devaddr),
        .regaddr(regaddr),
        .wrdata(wrdata),
        .rddata(data_out),
        .sda_i(sccb_sda_i),
        .sda_o(sccb_sda_o),
        .sda_t(sccb_sda_t),
        .scl(sccb_scl_o)
    );
    
    OV_CAM_CLK_Divider #(CLOCK_FREQ)
        divider (
        .refclk(clock),
        .sccbclk(sccb_clk),
        .rising(rising),
        .falling(falling)
    );
        
    OV_CAM_Controller #(
        .CAMERA_MODEL(CAMERA_MODEL),
        .REGADDR_WIDTH(REGADDR_WIDTH),
        .DVPHO(DVPHO),
        .DVPVO(DVPVO)
        )
        controller(
        .clk(sccb_clk),
        .reset(reset),
        .start(start),
        .done(done),
        .sccb_done(sccb_done),
        .sccb_start(sccb_start),
        .sccb_devaddr(devaddr),
        .sccb_regaddr(regaddr),
        .sccb_wrdata(wrdata),
        .resetn_out(resetn_out),
        .pwdn_out(pwdn_out)
    );
    
    OV_CAM_Capture capturer(
        .pclk(pclk),
        .reset(reset),
        .d_in(d_in),
        .vsync(vsync),
        .href(href),
        .data_out(pixel_data_out),
`ifdef BRAM_OUT        
        .address_out(address_out),
`else
        .hsync_out(hsync_out),
        .vsync_out(vsync_out),
        .pclk_out(pclk_out),
`endif        
        .we(we)
    );
    
endmodule
