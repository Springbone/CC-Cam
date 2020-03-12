`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/19 20:37:36
// Design Name: 
// Module Name: OV_CAM_Capture
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


module OV_CAM_Capture(
    input wire pclk,
    input wire reset,
    input wire [7:0] d_in,    
    input wire vsync,
    input wire href,
`ifdef BRAM_OUT    
    output reg [15:0] data_out,
    output reg [18:0] address_out,
`else
    output reg [23:0] data_out,
    output reg hsync_out,
    output reg vsync_out,
    output reg pclk_out,
`endif    
    output reg we
    );
    
    reg [ 2:0]  fsm;
    reg [ 2:0]  fsm_n;
    reg [ 7:0]  former_byte;
    reg [ 7:0]  former_byte_n;
    reg [ 7:0]  current_byte;
`ifdef BRAM_OUT
    reg [18:0]  address_out_n;
    reg [15:0]  data_out_n;
`else
    reg [23:0]  data_out_n;
`endif    
    
    localparam FSM_IDLE         = 0;
    localparam FSM_START        = 1;
    localparam FSM_FIRST_BYTE   = 2;
    localparam FSM_SECOND_BYTE  = 3;
    localparam FSM_STOP         = 4;
    
    //State Machine
    always @(posedge pclk or posedge reset)
        if (reset) begin
            fsm <= FSM_IDLE;
        end else begin
            fsm <= fsm_n;
        end
        
    always @(*) begin
        if (vsync)
            fsm_n = FSM_IDLE;
        else
            case(fsm)
                FSM_IDLE:
                    if (href)
                        fsm_n = FSM_START;
                    else
                        fsm_n = FSM_IDLE;
                FSM_START:
                    if (href)
                        fsm_n = FSM_SECOND_BYTE;
                    else
                        fsm_n = FSM_IDLE;
                FSM_FIRST_BYTE:
                    if (href)
                        fsm_n = FSM_SECOND_BYTE;
                    else
                        fsm_n = FSM_IDLE;
                FSM_SECOND_BYTE:
                    if (href)
                        fsm_n = FSM_FIRST_BYTE;
                    else
                        fsm_n = FSM_STOP;
                FSM_STOP:
                    fsm_n = FSM_IDLE;
                default:
                    fsm_n = FSM_IDLE;
            endcase
    end
 
    //Data input logic
    always @(posedge pclk or posedge reset)
        if (reset)
            current_byte <= 0;
        else
            current_byte <= d_in;

    always @(posedge pclk or posedge reset)
        if (reset) begin
            former_byte <= 0;
        end else begin
            former_byte <= former_byte_n;
        end
    
    always @(*)
        if (fsm == FSM_FIRST_BYTE || fsm == FSM_START)
            former_byte_n = current_byte;
        else
            former_byte_n = 0;

    //Data output logic
    always @(negedge pclk or posedge reset)
        if (reset) begin
            data_out <= 0;
        end else begin
            if (fsm == FSM_SECOND_BYTE)
                data_out <= data_out_n;
        end
        
    always @(*) begin
`ifdef BRAM_OUT  
        data_out_n = {former_byte, current_byte};
`else
        data_out_n = {//current_byte[4:0], {3{1'b0}},//Blue                   
//                      former_byte[2:0], current_byte[7:5], {2{1'b0}}, //Green
//                      former_byte[7:3], {3{1'b0}}  //Red
                      current_byte[4:0], {3{1'b0}}, //Blue
                      former_byte[7:3], {3{1'b0}},  //Red
                      former_byte[2:0], current_byte[7:5], {2{1'b0}} //Green
                      };
`endif        
    end

`ifdef BRAM_OUT    
    always @(negedge pclk or posedge reset)
        if (reset) begin
            address_out <= 0;
        end else begin
            address_out <= address_out_n;
        end

    always @(*) begin
        if (href)
            if (fsm == FSM_SECOND_BYTE)
                if (address_out == 640*120-1)
                    address_out_n = 0;
                else
                    address_out_n = address_out + 1;
            else
                address_out_n = address_out;
        else
            address_out_n = address_out;
    end
    
    always @(*) begin
            we = (~reset) & (~vsync) & (((href) & (fsm == FSM_FIRST_BYTE))|(fsm == FSM_STOP));
    end
`else
    initial pclk_out = 0;

    always @(posedge pclk or posedge reset)
        if (reset)
            pclk_out <= 0;
        else
            if (we)
                pclk_out <= (fsm == FSM_SECOND_BYTE);
            else
                pclk_out <= ~pclk_out;

    always @(*) begin
        vsync_out = vsync & (~reset);
    end
    
    always @(*)
        hsync_out = (fsm == FSM_START) & (~reset);
        
    always @(*)
        we = (~reset) & (~vsync) & (((href) & (fsm == FSM_FIRST_BYTE))|(fsm == FSM_STOP)|(fsm == FSM_SECOND_BYTE));
`endif        
    
endmodule
