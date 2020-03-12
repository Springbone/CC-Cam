`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/10 18:34:31
// Design Name: 
// Module Name: OV_CAM_CLK_Dividor
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


module OV_CAM_CLK_Divider #(
    parameter  CLOCK_FREQ = 125
    )
    (
    input wire refclk,
    output reg sccbclk,
    output     rising,
    output     falling
    );    
    
    localparam SCCB_DELAY = CLOCK_FREQ*10;
    reg [9:0] sccb_cnt = 0;
    
    initial sccbclk <= 0;
    
    always @(posedge refclk) begin
        if (sccb_cnt == (SCCB_DELAY/2)-1) begin
            sccb_cnt = 0;
            sccbclk = ~sccbclk;
        end else begin
            sccb_cnt = sccb_cnt + 1;
        end    
    end
    
    assign rising = sccbclk & ~(|sccb_cnt);
    assign falling = ~sccbclk & ~(|sccb_cnt);
    
endmodule
