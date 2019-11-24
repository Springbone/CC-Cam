`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12/16/2016 01:24:02 PM
// Design Name: 
// Module Name: OV_CAM_Control
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

module OV_CAM_Controller #(
    parameter CAMERA_MODEL = 7670,
    parameter REGADDR_WIDTH = 8,
    parameter [15:0]DVPHO = 640, 
    parameter [15:0]DVPVO=480
    )
    (
    input wire  clk,
    input wire  reset,
    input wire  start,
    output reg  done,
    input wire  sccb_done,
    output reg  sccb_start,
    output reg  [7:0] sccb_devaddr,
    output reg  [REGADDR_WIDTH-1:0] sccb_regaddr,
    output reg  [7:0] sccb_wrdata,
    output reg  resetn_out,
    output reg  pwdn_out
    );    

    localparam DELAY_TIME_30MS   = 3000;
    wire [15:0] ROM_CONFIG_SIZE;

    localparam  FSM_IDLE        = 0,
                FSM_START       = 1,
                FSM_WAIT_DONE   = 2,
                FSM_ALL_DONE    = 3;
    
    reg         [15:0]  delay_cnt;
    reg         [15:0]  delay_cnt_n;
    reg         [ 3:0]  ctl_fsm_cs;
    reg         [ 3:0]  ctl_fsm_ns;
    reg         [15:0]  rom_addr;
    reg         [REGADDR_WIDTH+8-1:0]  rom_data;
    wire        [REGADDR_WIDTH+8-1:0]  rom_data_n;
    
    generate
        case (CAMERA_MODEL)
            7670: begin: cam7670
                    assign ROM_CONFIG_SIZE =172 ;//169 //21 //172//124
                    OV7670_Config config_rom(
                        .rom_addr(rom_addr),
                        .rom_data_n(rom_data_n)                        
                    );
                  end
            5640: begin: cam5640
                    assign ROM_CONFIG_SIZE = 259;
                    OV5640_Config #(.DVPHO(DVPHO),.DVPVO(DVPVO)) 
                    config_rom(
                        .rom_addr(rom_addr),
                        .rom_data_n(rom_data_n)                        
                    );
                  end
         default: begin: cam_unknown
                    assign ROM_CONFIG_SIZE = 172; //21 //172
                    OV7670_Config config_rom(
                        .rom_addr(rom_addr),
                        .rom_data_n(rom_data_n)                        
                    );                     
                  end
        endcase
    endgenerate

    generate
        case (CAMERA_MODEL)
            7670: initial begin: cam7670_devaddr
                    sccb_devaddr = 8'h42;
                end
            5640: initial begin: cam7670_devaddr
                    sccb_devaddr = 8'h78;
                end
            default: initial begin: cam7670_devaddr
                    sccb_devaddr = 8'h42;
                end
        endcase    
    endgenerate
    
    
    always @(posedge clk or posedge reset) begin
      if (reset || ~start)
        delay_cnt <= 0;
      else
        delay_cnt <= delay_cnt_n;
    end
    
    initial begin
        pwdn_out <= 1;
        resetn_out <= 0;
    end
    
    always @( * ) begin
      if (delay_cnt >= DELAY_TIME_30MS/30*5)
        pwdn_out <= 0;
      else
        pwdn_out <= 1;
    end

    always @( * ) begin
      if (delay_cnt >= DELAY_TIME_30MS/30*10)
        resetn_out <= 1;
      else
        resetn_out <= 0;
    end
    
    always @( * ) begin
      if (delay_cnt == DELAY_TIME_30MS)
        delay_cnt_n = delay_cnt;
      else
        delay_cnt_n = delay_cnt + 1;
    end
    
    always @(posedge clk or posedge reset) begin
      if (reset)
        ctl_fsm_cs <= 0;
      else
        ctl_fsm_cs <= ctl_fsm_ns;
    end
    
    always @(*) begin
      if (delay_cnt == DELAY_TIME_30MS)
        case(ctl_fsm_cs)
          FSM_IDLE:
            ctl_fsm_ns = FSM_START;
          FSM_START:
            if (~sccb_done)
                ctl_fsm_ns = FSM_WAIT_DONE;
            else
                ctl_fsm_ns = ctl_fsm_cs;
          FSM_WAIT_DONE:            
            if (sccb_done) begin
              if (rom_addr == ROM_CONFIG_SIZE)
                ctl_fsm_ns = FSM_ALL_DONE;
              else
                ctl_fsm_ns = FSM_START;
            end else
              ctl_fsm_ns = ctl_fsm_cs;
          FSM_ALL_DONE:
            ctl_fsm_ns = ctl_fsm_cs;
          default:
            ctl_fsm_ns = FSM_IDLE;
        endcase
      else
        ctl_fsm_ns = FSM_IDLE;
    end
    
    always @(negedge sccb_done or posedge reset) begin
      if (reset) 
        rom_addr <= 0;
      else
        rom_addr <= rom_addr + 1;
    end
    
    always @(*) begin
      sccb_start = (ctl_fsm_cs == FSM_START);
    end
    
    always @(negedge sccb_done or posedge reset) begin
      if (reset)
        rom_data <= 0;
      else
        rom_data <= rom_data_n;
    end
        
    always @(*) begin
      sccb_regaddr = rom_data[REGADDR_WIDTH+8-1:8];
    end

    always @(*) begin
      sccb_wrdata = rom_data[7:0];
    end
    
    always @(*) begin
      done = (ctl_fsm_cs == FSM_ALL_DONE);
    end

endmodule
