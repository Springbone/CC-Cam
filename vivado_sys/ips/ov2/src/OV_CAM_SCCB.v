`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Shanghai Jiaotong University
// Engineer: Yingnan Wu
// 
// Create Date: 2016/12/10 15:03:45
// Design Name: 
// Module Name: OV_CAM_SCCB
// Project Name: 
// Target Devices: Zybo
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
`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Shanghai Jiaotong University
// Engineer: Yingnan Wu
//
// Create Date: 2016/12/10 15:03:45
// Design Name:
// Module Name: OV_CAM_SCCB
// Project Name:
// Target Devices: Zybo
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

module OV_CAM_SCCB #(
          REGADDR_WIDTH = 8
    )
    (
          clk,
          reset,
          start,
          done,
          devaddr,
          regaddr,
          wrdata,
          rddata,
          scl,
          sda_i,
          sda_o,
          sda_t
    );

    input           clk;
    input           reset;
    input           start;
    output          done;
    input   [ 7:0]  devaddr;
    input   [REGADDR_WIDTH-1:0]  regaddr;
    input   [ 7:0]  wrdata;
    output  [ 7:0]  rddata;
    output          scl;
    input           sda_i;
    output          sda_o;
    output          sda_t;
    
    reg             scl;
    reg             sda_o;
    reg             sda_t;

    reg     [ 4:0]  fsm_cs;
    reg     [ 4:0]  fsm_ns;
    reg     [ 4:0]  bit_cnt;

    localparam  FSM_IDLE    = 0,
                WR_START    = 1,
                WR_DEVADDR  = 2,
                WR_ACK1     = 3,
                WR_REGADDR  = 4,
                WR_ACK2     = 5,
                WR_REGDATA  = 6,
                WR_ACK3     = 7,
                WR_STOP     = 8,
                WR_RESTART1 = 9,
                WR_RESTART2 = 10;

    localparam  RD_START    = 11;



    always @ (negedge clk or posedge reset) begin
      if (reset)
        fsm_cs <= FSM_IDLE;
      else
        fsm_cs <= fsm_ns;
    end

    always @ ( * ) begin
      case(fsm_cs)
        FSM_IDLE:
          if (start && ~devaddr[0])
            fsm_ns = WR_START;
          else if (start && devaddr[1])
            fsm_ns = RD_START;
          else
            fsm_ns = FSM_IDLE;

        WR_START:
          fsm_ns = WR_DEVADDR;

        WR_DEVADDR:
          if (bit_cnt == 0)
            fsm_ns = WR_ACK1;
          else
            fsm_ns = WR_DEVADDR;

        WR_ACK1:
          if (~sda_i)
            fsm_ns = WR_REGADDR;
          else
            fsm_ns = WR_RESTART1;

        WR_REGADDR:
          if (bit_cnt[2:0] == 0)
            fsm_ns = WR_ACK2;
          else
            fsm_ns = WR_REGADDR;

        WR_ACK2:
          if (~sda_i)
            if (bit_cnt[4])
              fsm_ns = WR_REGDATA;
            else
              fsm_ns = WR_REGADDR;
          else
            fsm_ns = WR_RESTART1;

        WR_REGDATA:
          if (bit_cnt == 0)
            fsm_ns = WR_ACK3;
          else
            fsm_ns = WR_REGDATA;
        
        WR_ACK3:
          if (~sda_i)
            fsm_ns = WR_STOP;
          else
            fsm_ns = WR_RESTART1;
          
        WR_STOP:
          fsm_ns = FSM_IDLE;
          
        WR_RESTART1:
          fsm_ns = WR_RESTART2;
          
        WR_RESTART2:
          fsm_ns = WR_START;

        default:
          fsm_ns = FSM_IDLE;
      endcase
    end

    always @(negedge clk or posedge reset) begin
      if (reset)
        bit_cnt <= 7;
      else
        case(fsm_cs)
          WR_DEVADDR,
          WR_REGADDR,
          WR_REGDATA:
            bit_cnt <= bit_cnt - 1;
          WR_ACK1:
            bit_cnt <= REGADDR_WIDTH -1;
          default:
            bit_cnt <= 7;
        endcase
    end
    
    always @( * ) begin
      if (reset)
        scl = 1;
      else
        case (fsm_cs)
          WR_DEVADDR,
          WR_ACK1,
          WR_REGADDR,
          WR_ACK2,
          WR_REGDATA,
          WR_ACK3,
          WR_STOP,
          WR_RESTART1:
            scl = clk;
          default:
            scl = 1;
        endcase
    end
    
    always @( * ) begin
      if (reset)
        sda_t = 1;
      else
        case (fsm_cs)
          WR_ACK1,
          WR_ACK2,
          WR_ACK3:
            sda_t = 1;
          default:
            sda_t = 0;
        endcase
    end
    
    always @( * ) begin
      if (reset)
        sda_o = 1;
      else
        case (fsm_cs)
          WR_START:
            sda_o = 0;
          WR_DEVADDR:
            sda_o = devaddr[bit_cnt];
          WR_REGADDR:
            sda_o = regaddr[bit_cnt];
          WR_REGDATA:
            sda_o = wrdata[bit_cnt];
          WR_STOP,
          WR_RESTART1:
            sda_o = 0;
          default:
            sda_o = 1;            
        endcase
    end
    
    assign done = (fsm_cs == FSM_IDLE);

endmodule
