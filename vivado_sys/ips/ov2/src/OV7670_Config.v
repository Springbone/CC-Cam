`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Shanghai Jiaotong University
// Engineer: Wu Yingnan
// 
// Create Date: 04/08/2017 07:16:59 PM
// Design Name: 
// Module Name: OV7670_Config
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


module OV7670_Config(
    input   [15:0] rom_addr,
    output reg [15:0] rom_data_n
    );
    localparam off = 3;    
    always @(*) begin
      case(rom_addr)
//Version 1      
//        0   :   rom_data_n  =   {8'h12, 8'h80};// COM7   Reset
//        1   :   rom_data_n  =   {8'h12, 8'h80};// COM7   Reset
//        2   :   rom_data_n  =   {8'h12, 8'h04};// COM7   Size & RGB output & Test output
//        3   :   rom_data_n  =   {8'h40, 8'hd0};// COM15  Full 0-255 output, RGB 565
//        4   :   rom_data_n  =   {8'h3a, 8'h04};// TSLB settings
//        5   :   rom_data_n  =   {8'h3d, 8'hc8};// COM13 I don't know the meaning
//        6   :   rom_data_n  =   {8'h1e, 8'h01};// Normal image without flipping
//        7   :   rom_data_n  =   {8'h6b, 8'h40};// PLL x4 & Enable LDO
//        8   :   rom_data_n  =   {8'h11, 8'h03};// CLKRC  Prescaler - Fin/(1+3)
//        9   :   rom_data_n  =   {8'h3E, 8'h00};// COM14  PCLK scaling off
        
//        10  :   rom_data_n  =   {8'h70, 8'h00};// Color bar output
//        11  :   rom_data_n  =   {8'h71, 8'h00};// Color bar output
//        12  :   rom_data_n  =   {8'h8c, 8'h00};// Disable RGB444
//        13  :   rom_data_n  =   {8'h0c, 8'h00};// COM3  Swap Output data MSB and LSB
//        14  :   rom_data_n  =   {8'h15, 8'h00};// COM10 Free running PCLK & Normal HREF/VSYNC
//        //The following is not investigated
//        15  :   rom_data_n  =   {8'h32, 8'hb6};
//        16  :   rom_data_n  =   {8'h17, 8'h13};
//        17  :   rom_data_n  =   {8'h18, 8'h01};
//        18  :   rom_data_n  =   {8'h19, 8'h02};
//        19  :   rom_data_n  =   {8'h1a, 8'h7a};
//        20  :   rom_data_n  =   {8'h03, 8'h0a};

//Version 2
         0  :    rom_data_n  =   {16'h1280};
         1  :    rom_data_n  =   {16'h40d0};//4010
         2  :    rom_data_n  =   {16'h1204};
         3  :    rom_data_n  =   {16'h3a04};
         4  :    rom_data_n  =   {16'h3dc8};
         5  :    rom_data_n  =   {16'h8c00};
         
         3+off  :    rom_data_n  =   {16'h32b6};//3280
         4+off  :    rom_data_n  =   {16'h1713};//1713
         5+off  :    rom_data_n  =   {16'h1801};//1805
         6+off  :    rom_data_n  =   {16'h1902};//1902
         7+off  :    rom_data_n  =   {16'h1a7a};//1a7b
         8+off  :    rom_data_n  =   {16'h030a};//030a
         9+off  :    rom_data_n  =   {16'h0c00};//0c00
        10+off  :    rom_data_n  =   {16'h3e00};
        11+off  :    rom_data_n  =   {16'h7000};
        12+off  :    rom_data_n  =   {16'h7100};//7101
        13+off  :    rom_data_n  =   {16'h7211};
        14+off  :    rom_data_n  =   {16'h7309};
        15+off  :    rom_data_n  =   {16'ha202};
        16+off  :    rom_data_n  =   {16'h1103};//1100
        17+off  :    rom_data_n  =   {16'h7a20};
        18+off  :    rom_data_n  =   {16'h7b1c};
        19+off  :    rom_data_n  =   {16'h7c28};
        20+off  :    rom_data_n  =   {16'h7d3c};
        21+off  :    rom_data_n  =   {16'h7e55};
        22+off  :    rom_data_n  =   {16'h7f68};
        23+off  :    rom_data_n  =   {16'h8076};
        24+off  :    rom_data_n  =   {16'h8180};
        25+off  :    rom_data_n  =   {16'h8288};
        26+off  :    rom_data_n  =   {16'h838f};
        27+off  :    rom_data_n  =   {16'h8496};
        28+off  :    rom_data_n  =   {16'h85a3};
        29+off  :    rom_data_n  =   {16'h86af};
        30+off  :    rom_data_n  =   {16'h87c4};
        31+off  :    rom_data_n  =   {16'h88d7};
        32+off  :    rom_data_n  =   {16'h89e8};
        33+off  :    rom_data_n  =   {16'h13e0};
        34+off  :    rom_data_n  =   {16'h0000};
        35+off  :    rom_data_n  =   {16'h1000};
        36+off  :    rom_data_n  =   {16'h0d00};
        37+off  :    rom_data_n  =   {16'h1438};
        38+off  :    rom_data_n  =   {16'ha505};
        39+off  :    rom_data_n  =   {16'hab07};
        40+off  :    rom_data_n  =   {16'h2475};
        41+off  :    rom_data_n  =   {16'h2563};
        42+off  :    rom_data_n  =   {16'h26A5};
        43+off  :    rom_data_n  =   {16'h9f78};
        44+off  :    rom_data_n  =   {16'ha068};
        45+off  :    rom_data_n  =   {16'ha103};
        46+off  :    rom_data_n  =   {16'ha6df};
        47+off  :    rom_data_n  =   {16'ha7df};
        48+off  :    rom_data_n  =   {16'ha8f0};
        49+off  :    rom_data_n  =   {16'ha990};
        50+off  :    rom_data_n  =   {16'haa94};
        51+off  :    rom_data_n  =   {16'h13e5};
        52+off  :    rom_data_n  =   {16'h0e61};
        53+off  :    rom_data_n  =   {16'h0f4b};
        54+off  :    rom_data_n  =   {16'h1602};
        55+off  :    rom_data_n  =   {16'h1e01};//1e37
        56+off  :    rom_data_n  =   {16'h2102};
        57+off  :    rom_data_n  =   {16'h2291};
        58+off  :    rom_data_n  =   {16'h2907};
        59+off  :    rom_data_n  =   {16'h330b};
        60+off  :    rom_data_n  =   {16'h350b};
        61+off  :    rom_data_n  =   {16'h371d};
        62+off  :    rom_data_n  =   {16'h3871};
        63+off  :    rom_data_n  =   {16'h392a};
        64+off  :    rom_data_n  =   {16'h3c78};
        65+off  :    rom_data_n  =   {16'h4d40};
        66+off  :    rom_data_n  =   {16'h4e20};
        67+off  :    rom_data_n  =   {16'h695d};
        68+off  :    rom_data_n  =   {16'h6b40};//
        69+off  :    rom_data_n  =   {16'h7419};
        70+off  :    rom_data_n  =   {16'h8d4f};
        71+off  :    rom_data_n  =   {16'h8e00};
        72+off  :    rom_data_n  =   {16'h8f00};
        73+off  :    rom_data_n  =   {16'h9000};
        74+off  :    rom_data_n  =   {16'h9100};
        75+off  :    rom_data_n  =   {16'h9200};
        76+off  :    rom_data_n  =   {16'h9600};
        77+off  :    rom_data_n  =   {16'h9a80};
        78+off  :    rom_data_n  =   {16'hb084};
        79+off  :    rom_data_n  =   {16'hb10c};
        80+off  :    rom_data_n  =   {16'hb20e};
        81+off  :    rom_data_n  =   {16'hb382};
        82+off  :    rom_data_n  =   {16'hb80a};
        83+off  :    rom_data_n  =   {16'h4314};
        84+off  :    rom_data_n  =   {16'h44f0};
        85+off  :    rom_data_n  =   {16'h4534};
        86+off  :    rom_data_n  =   {16'h4658};
        87+off  :    rom_data_n  =   {16'h4728};
        88+off  :    rom_data_n  =   {16'h483a};
        89+off  :    rom_data_n  =   {16'h5988};
        90+off  :    rom_data_n  =   {16'h5a88};
        91+off  :    rom_data_n  =   {16'h5b44};
        92+off  :    rom_data_n  =   {16'h5c67};
        93+off  :    rom_data_n  =   {16'h5d49};
        94+off  :    rom_data_n  =   {16'h5e0e};
        95+off  :    rom_data_n  =   {16'h6404};
        96 +off :    rom_data_n  =   {16'h6520};
        97+off  :    rom_data_n  =   {16'h6605};
        98+off  :    rom_data_n  =   {16'h9404};
        99+off  :    rom_data_n  =   {16'h9508};
        100+off  :    rom_data_n  =   {16'h6c0a};
        101+off  :    rom_data_n  =   {16'h6d55};
        102+off  :    rom_data_n  =   {16'h6e11};
        103+off  :    rom_data_n  =   {16'h6f9f};
        104 +off :    rom_data_n  =   {16'h6a20};//G-AWB
        105+off  :    rom_data_n  =   {16'h0160};//B-AWB
        106+off  :    rom_data_n  =   {16'h0260};//R-AWB
        107 +off :    rom_data_n  =   {16'h13e7};
        108+off  :    rom_data_n  =   {16'h1500};//
        109 +off :    rom_data_n  =   {16'h4f80};
        110+off  :    rom_data_n  =   {16'h5080};
        111+off  :    rom_data_n  =   {16'h5100};
        112+off  :    rom_data_n  =   {16'h5222};
        113 +off :    rom_data_n  =   {16'h535e};
        114+off  :    rom_data_n  =   {16'h5480};
        115 +off :    rom_data_n  =   {16'h5501};//亮度
        116 +off :    rom_data_n  =   {16'h5640};//对比度
        117 +off :    rom_data_n  =   {16'h5790};
        118 +off :    rom_data_n  =   {16'h589e};
        119 +off :    rom_data_n  =   {16'h4108};
        120 +off :    rom_data_n  =   {16'h3f05};//边缘
        121 +off :    rom_data_n  =   {16'h7505};
        122 +off :    rom_data_n  =   {16'h76e1};
        123 +off :    rom_data_n  =   {16'h4c1F};//噪声
        124 +off :    rom_data_n  =   {16'h770a};
        125 +off :    rom_data_n  =   {16'h3dc2};
        126 +off :    rom_data_n  =   {16'h4b09};
        127 +off :    rom_data_n  =   {16'hc9c8};
        128 +off :    rom_data_n  =   {16'h4138};
        129 +off :    rom_data_n  =   {16'h0000};
        130 +off :    rom_data_n  =   {16'h3411};
        131 +off :    rom_data_n  =   {16'h3b02};
        132  +off:    rom_data_n  =   {16'ha489};
        133 +off :    rom_data_n  =   {16'h9600};
        134 +off :    rom_data_n  =   {16'h9730};
        135 +off :    rom_data_n  =   {16'h9820};
        136 +off :    rom_data_n  =   {16'h9930};
        137 +off :    rom_data_n  =   {16'h9a84};
        138 +off :    rom_data_n  =   {16'h9b29};
        139 +off :    rom_data_n  =   {16'h9c03};
        140 +off :    rom_data_n  =   {16'h9d4c};
        141 +off :    rom_data_n  =   {16'h9e3f};
        142 +off :    rom_data_n  =   {16'h7804};
        143 +off :    rom_data_n  =   {16'h7901};
        144 +off :    rom_data_n  =   {16'hc8f0};
        145 +off :    rom_data_n  =   {16'h790f};
        146 +off :    rom_data_n  =   {16'hc800};
        147 +off :    rom_data_n  =   {16'h7910};
        148 +off :    rom_data_n  =   {16'hc87e};
        149 +off :    rom_data_n  =   {16'h790a};
        150 +off :    rom_data_n  =   {16'hc880};
        151 +off :    rom_data_n  =   {16'h790b};
        152 +off :    rom_data_n  =   {16'hc801};
        153 +off :    rom_data_n  =   {16'h790c};
        154 +off :    rom_data_n  =   {16'hc80f};
        155 +off :    rom_data_n  =   {16'h790d};
        156 +off :    rom_data_n  =   {16'hc820};
        157 +off :    rom_data_n  =   {16'h7909};
        158 +off :    rom_data_n  =   {16'hc880};
        159 +off :    rom_data_n  =   {16'h7902};
        160 +off :    rom_data_n  =   {16'hc8c0};
        161 +off :    rom_data_n  =   {16'h7903};
        162 +off :    rom_data_n  =   {16'hc840};
        163 +off :    rom_data_n  =   {16'h7905};
        164 +off :    rom_data_n  =   {16'hc830};
        165 +off :    rom_data_n  =   {16'h69aa};
        166 +off :    rom_data_n  =   {16'h0900};
        167 +off :    rom_data_n  =   {16'h3b42};
        168 +off :    rom_data_n  =   {16'h2d01};
    default  :    rom_data_n    =    0;

//Version 3
//        8'h00 :
//            rom_data_n <= 16'h1280;
//        8'h01 :
//            rom_data_n <= 16'h1204;//1214
//        8'h02 :
//            rom_data_n <= 16'h40d0;
//        8'h03 :
//            rom_data_n <= 16'h3a04;
//        8'h04 :
//            rom_data_n <= 16'h3dc8;
//        8'h05 :
//            rom_data_n <= 16'h32b6;//3280
//        8'h06 :
//            rom_data_n <= 16'h1713;//1716
//        8'h07 :
//            rom_data_n <= 16'h1801;//1804
//        8'h08 :
//            rom_data_n <= 16'h1902;//1902
//        8'h09 :
//            rom_data_n <= 16'h1a7a;//1a7b
//        8'h0A :
//            rom_data_n <= 16'h030a;//0306
//        8'h0B :
//            rom_data_n <= 16'h0c00;
//        8'h0C :
//            rom_data_n <= 16'h1500;
//        8'h0D :
//            rom_data_n <= 16'h3e00;
//        8'h0E :
//            rom_data_n <= 16'h7000;//703a
//        8'h0F :
//            rom_data_n <= 16'h7100;//7135
//        8'h10 :
//            rom_data_n <= 16'h7211;
//        8'h11 :
//            rom_data_n <= 16'h7300;
//        8'h12 :
//            rom_data_n <= 16'ha202;
//        8'h13 :
//            rom_data_n <= 16'h1103;//1181
//        8'h14 :
//            rom_data_n <= 16'h7a20;
//        8'h15 :
//            rom_data_n <= 16'h7b1c;
//        8'h16 :
//            rom_data_n <= 16'h7c28;
//        8'h17 :
//            rom_data_n <= 16'h7d3c;
//        8'h18 :
//            rom_data_n <= 16'h7e55;
//        8'h19 :
//            rom_data_n <= 16'h7f68;
//        8'h1A :
//            rom_data_n <= 16'h8076;
//        8'h1B :
//            rom_data_n <= 16'h8180;
//        8'h1C :
//            rom_data_n <= 16'h8288;
//        8'h1D :
//            rom_data_n <= 16'h838f;
//        8'h1E :
//            rom_data_n <= 16'h8496;
//        8'h1F :
//            rom_data_n <= 16'h85a3;
//        8'h20 :
//            rom_data_n <= 16'h86af;
//        8'h21 :
//            rom_data_n <= 16'h87c4;
//        8'h22 :
//            rom_data_n <= 16'h88d7;
//        8'h23 :
//            rom_data_n <= 16'h89e8;
//        8'h24 :
//            rom_data_n <= 16'h13e0;
//        8'h25 :
//            rom_data_n <= 16'h0000;
//        8'h26 :
//            rom_data_n <= 16'h1000;
//        8'h27 :
//            rom_data_n <= 16'h0d00;
//        8'h28 :
//            rom_data_n <= 16'h1428;
//        8'h29 :
//            rom_data_n <= 16'ha505;
//        8'h2A :
//            rom_data_n <= 16'hab07;
//        8'h2B :
//            rom_data_n <= 16'h2475;
//        8'h2C :
//            rom_data_n <= 16'h2563;
//        8'h2D :
//            rom_data_n <= 16'h26a5;
//        8'h2E :
//            rom_data_n <= 16'h9f78;
//        8'h2F :
//            rom_data_n <= 16'ha068;
//        8'h30 :
//            rom_data_n <= 16'ha103;
//        8'h31 :
//            rom_data_n <= 16'ha6df;
//        8'h32 :
//            rom_data_n <= 16'ha7df;
//        8'h33 :
//            rom_data_n <= 16'ha8f0;
//        8'h34 :
//            rom_data_n <= 16'ha990;
//        8'h35 :
//            rom_data_n <= 16'haa94;
//        8'h36 :
//            rom_data_n <= 16'h13e5;
//        8'h37 :
//            rom_data_n <= 16'h0e61;
//        8'h38 :
//            rom_data_n <= 16'h0f4b;
//        8'h39 :
//            rom_data_n <= 16'h1602;
//        8'h40 :
//            rom_data_n <= 16'h1e07;//1e27
//        8'h41 :
//            rom_data_n <= 16'h2102;
//        8'h42 :
//            rom_data_n <= 16'h2291;
//        8'h43 :
//            rom_data_n <= 16'h2907;
//        8'h44 :
//            rom_data_n <= 16'h330b;
//        8'h45 :
//            rom_data_n <= 16'h350b;
//        8'h46 :
//            rom_data_n <= 16'h371b;
//        8'h47 :
//            rom_data_n <= 16'h3871;
//        8'h48 :
//            rom_data_n <= 16'h392a;
//        8'h49 :
//            rom_data_n <= 16'h3c78;
//        8'h4A :
//            rom_data_n <= 16'h4d40;
//        8'h4B :
//            rom_data_n <= 16'h4e20;
//        8'h4C :
//            rom_data_n <= 16'h6900;
//        8'h4D :
//            rom_data_n <= 16'h6b40;
//        8'h4E :
//            rom_data_n <= 16'h7419;
//        8'h4F :
//            rom_data_n <= 16'h8d4f;
//        8'h50 :
//            rom_data_n <= 16'h8e00;
//        8'h51 :
//            rom_data_n <= 16'h8f00;
//        8'h52 :
//            rom_data_n <= 16'h9000;
//        8'h53 :
//            rom_data_n <= 16'h9100;
//        8'h54 :
//            rom_data_n <= 16'h9200;
//        8'h55 :
//            rom_data_n <= 16'h9600;
//        8'h56 :
//            rom_data_n <= 16'h9a80;
//        8'h57 :
//            rom_data_n <= 16'hb084;
//        8'h58 :
//            rom_data_n <= 16'hb10c;
//        8'h59 :
//            rom_data_n <= 16'hb20e;
//        8'h5A :
//            rom_data_n <= 16'hb382;
//        8'h5B :
//            rom_data_n <= 16'hb80a;
//        8'h5C :
//            rom_data_n <= 16'h4314;
//        8'h5D :
//            rom_data_n <= 16'h44f0;
//        8'h5E :
//            rom_data_n <= 16'h4534;
//        8'h5F :
//            rom_data_n <= 16'h4658;
//        8'h60 :
//            rom_data_n <= 16'h4728;
//        8'h61 :
//            rom_data_n <= 16'h483a;
//        8'h62 :
//            rom_data_n <= 16'h5988;
//        8'h63 :
//            rom_data_n <= 16'h5a88;
//        8'h64 :
//            rom_data_n <= 16'h5b44;
//        8'h65 :
//            rom_data_n <= 16'h5c67;
//        8'h66 :
//            rom_data_n <= 16'h5d49;
//        8'h67 :
//            rom_data_n <= 16'h5e0e;
//        8'h68 :
//            rom_data_n <= 16'h6404;
//        8'h69 :
//            rom_data_n <= 16'h6520;
//        8'h6A :
//            rom_data_n <= 16'h6605;
//        8'h6B :
//            rom_data_n <= 16'h9404;
//        8'h6C :
//            rom_data_n <= 16'h9508;
//        8'h6D :
//            rom_data_n <= 16'h6c0a;
//        8'h6E :
//            rom_data_n <= 16'h6d55;
//        8'h6F :
//            rom_data_n <= 16'h4f80;
//        8'h70 :
//            rom_data_n <= 16'h5080;
//        8'h71 :
//            rom_data_n <= 16'h5100;
//        8'h72 :
//            rom_data_n <= 16'h5222;
//        8'h73 :
//            rom_data_n <= 16'h535e;
//        8'h74 :
//            rom_data_n <= 16'h5480;  
//        8'h75 :
//            rom_data_n <= 16'h0903;
//        8'h76 :
//            rom_data_n <= 16'h6e11;
//        8'h77 :
//            rom_data_n <= 16'h6f9f;
//        8'h78 :
//            rom_data_n <= 16'h5500;
//        8'h79 :
//            rom_data_n <= 16'h5640;
//        8'h7A :
//            rom_data_n <= 16'h5740;
//        8'h7B :
//            rom_data_n <= 16'h4c00;               
//        default 	  rom_data_n <= 16'hb80a;
      endcase
    end
    
endmodule
