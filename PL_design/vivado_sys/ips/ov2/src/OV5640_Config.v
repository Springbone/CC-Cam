`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Shanghai Jiaotong University
// Engineer: Wu Yingnan
// 
// Create Date: 04/08/2017 07:16:59 PM
// Design Name: 
// Module Name: OV5640_Config
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

module OV5640_Config
    #(parameter [15:0]DVPHO = 640, parameter [15:0]DVPVO=480)(
    input   [15:0] rom_addr,
    output reg [23:0] rom_data_n
    );
    localparam [7:0]DVPHO_H = DVPHO[15:8];
    localparam [7:0]DVPHO_L = DVPHO[7:0];
    localparam [7:0]DVPVO_H = DVPVO[15:8];
    localparam [7:0]DVPVO_L = DVPVO[7:0];   
    always @(*) begin
      case(rom_addr)
           0  :    rom_data_n  =   {24'h300842}; // software power down
              1  :    rom_data_n  =   {24'h310303}; // sysclk from pll
              2  :    rom_data_n  =   {24'h3017ff}; // Frex, Vsync, Href, PCLK, D[9:6] output
              3  :    rom_data_n  =   {24'h3018ff}; // D[5:0], GPIO[1:0] output
              4  :    rom_data_n  =   {24'h30341a}; // PLL, MIPI 10-bit
              5  :    rom_data_n  =   {24'h303713}; // PLL
              6  :    rom_data_n  =   {24'h310801}; // clock divider
              7  :    rom_data_n  =   {24'h363036};
              8  :    rom_data_n  =   {24'h36310e};
              9  :    rom_data_n  =   {24'h3632e2};
             10  :    rom_data_n  =   {24'h363312};
             11  :    rom_data_n  =   {24'h3621e0};
             12  :    rom_data_n  =   {24'h3704a0};
             13  :    rom_data_n  =   {24'h37035a};
             14  :    rom_data_n  =   {24'h371578};
             15  :    rom_data_n  =   {24'h371701};
             16  :    rom_data_n  =   {24'h370b60};
             17  :    rom_data_n  =   {24'h37051a};
             18  :    rom_data_n  =   {24'h390502};
             19  :    rom_data_n  =   {24'h390610};
             20  :    rom_data_n  =   {24'h39010a};
             21  :    rom_data_n  =   {24'h373112};
             22  :    rom_data_n  =   {24'h360008}; // VCM debug
             23  :    rom_data_n  =   {24'h360133}; // VCM debug
             24  :    rom_data_n  =   {24'h302d60}; // system control
             25  :    rom_data_n  =   {24'h362052};
             26  :    rom_data_n  =   {24'h371b20};
             27  :    rom_data_n  =   {24'h471c50};
             28  :    rom_data_n  =   {24'h3a1343}; // pre-gain = 1.05x
             29  :    rom_data_n  =   {24'h3a1800}; // AEC gain ceiling = 7.75x
             30  :    rom_data_n  =   {24'h3a19f8}; // AEC gain ceiling//7c //***********!!!!!!!!!!!!!!!
             31  :    rom_data_n  =   {24'h363513};
             32  :    rom_data_n  =   {24'h363603};
             33  :    rom_data_n  =   {24'h363440};
             34  :    rom_data_n  =   {24'h362201};
        //50/60Hz detection
             35  :    rom_data_n  =   {24'h3c0134}; // sum auto, band counter enable, threshold = 4//34
             36  :    rom_data_n  =   {24'h3c0428}; // threshold low sum
             37  :    rom_data_n  =   {24'h3c0598}; // threshold high sum
             38  :    rom_data_n  =   {24'h3c0600}; // light meter 1 threshold H
        
             39  :    rom_data_n  =   {24'h3c0708}; // light meter 1 threshold L//3c0707
        
             40  :    rom_data_n  =   {24'h3c0800}; // light meter 2 threshold H
        
             41  :    rom_data_n  =   {24'h3c091c}; // light meter 2 threshold L
        
             42  :    rom_data_n  =   {24'h3c0a9c}; // sample number H
             43  :    rom_data_n  =   {24'h3c0b40}; // sample number L
             44  :    rom_data_n  =   {24'h381000}; // X offset
             45  :    rom_data_n  =   {24'h381110}; // X offset
             46  :    rom_data_n  =   {24'h381200}; // Y offset
             47  :    rom_data_n  =   {24'h370864};
             48  :    rom_data_n  =   {24'h400102}; // BLC start line
             49  :    rom_data_n  =   {24'h40051a}; // BLC always update
             50  :    rom_data_n  =   {24'h300000}; // enable MCU, OTP
             51  :    rom_data_n  =   {24'h3004ff}; // enable BIST, MCU memory, MCU, OTP, STROBE, D5060, timing, array clock
             52  :    rom_data_n  =   {24'h300e58}; // MIPI 2 lane? power down PHY HS TX, PHY LP RX, DVP enable
             53  :    rom_data_n  =   {24'h302e00};
             54  :    rom_data_n  =   {24'h430060}; // rgb565
             55  :    rom_data_n  =   {24'h501f01}; // rgb565
             56  :    rom_data_n  =   {24'h440e00};
             57  :    rom_data_n  =   {24'h5000a7}; // LENC on, raw gamma on, BPC on, WPC on, CIP on
        //AEC target
//             58  :    rom_data_n  =   {24'h3a0f30}; // stable in high
//             59  :    rom_data_n  =   {24'h3a1028}; // stable in low
//             60  :    rom_data_n  =   {24'h3a1b30}; // stable out high
//             61  :    rom_data_n  =   {24'h3a1e26}; // stable out low
//             62  :    rom_data_n  =   {24'h3a1160}; // fast zone high
//             63  :    rom_data_n  =   {24'h3a1f14}; // fast zone low
             58  :    rom_data_n  =   {24'h3a0f60}; // stable in high
             59  :    rom_data_n  =   {24'h3a1058}; // stable in low
             60  :    rom_data_n  =   {24'h3a1b60}; // stable out high
             61  :    rom_data_n  =   {24'h3a1e58}; // stable out low
             62  :    rom_data_n  =   {24'h3a11a0}; // fast zone high
             63  :    rom_data_n  =   {24'h3a1f20}; // fast zone low
        //LENC
             64  :    rom_data_n  =   {24'h580023};
             65  :    rom_data_n  =   {24'h580114};
             66  :    rom_data_n  =   {24'h58020f};
             67  :    rom_data_n  =   {24'h58030f};
             68  :    rom_data_n  =   {24'h580412};
             69  :    rom_data_n  =   {24'h580526};
             70  :    rom_data_n  =   {24'h58060c};
             71  :    rom_data_n  =   {24'h580708};
             72  :    rom_data_n  =   {24'h580805};
             73  :    rom_data_n  =   {24'h580905};
             74  :    rom_data_n  =   {24'h580a08};
             75  :    rom_data_n  =   {24'h580b0d};
             76  :    rom_data_n  =   {24'h580c08};
             77  :    rom_data_n  =   {24'h580d03};
             78  :    rom_data_n  =   {24'h580e00};
             79  :    rom_data_n  =   {24'h580f00};
             80  :    rom_data_n  =   {24'h581003};
             81  :    rom_data_n  =   {24'h581109};
             82  :    rom_data_n  =   {24'h581207};
             83  :    rom_data_n  =   {24'h581303};
             84  :    rom_data_n  =   {24'h581400};
             85  :    rom_data_n  =   {24'h581501};
             86  :    rom_data_n  =   {24'h581603};
             87  :    rom_data_n  =   {24'h581708};
             88  :    rom_data_n  =   {24'h58180d};
             89  :    rom_data_n  =   {24'h581908};
             90  :    rom_data_n  =   {24'h581a05};
             91  :    rom_data_n  =   {24'h581b06};
             92  :    rom_data_n  =   {24'h581c08};
             93  :    rom_data_n  =   {24'h581d0e};
             94  :    rom_data_n  =   {24'h581e29};
             95  :    rom_data_n  =   {24'h581f17};
             96  :    rom_data_n  =   {24'h582011};
             97  :    rom_data_n  =   {24'h582111};
             98  :    rom_data_n  =   {24'h582215};
             99  :    rom_data_n  =   {24'h582328};
            100  :    rom_data_n  =   {24'h582446};
            101  :    rom_data_n  =   {24'h582526};
            102  :    rom_data_n  =   {24'h582608};
            103  :    rom_data_n  =   {24'h582726};
            104  :    rom_data_n  =   {24'h582864};
            105  :    rom_data_n  =   {24'h582926};
            106  :    rom_data_n  =   {24'h582a24};
            107  :    rom_data_n  =   {24'h582b22};
            108  :    rom_data_n  =   {24'h582c24};
            109  :    rom_data_n  =   {24'h582d24};
            110  :    rom_data_n  =   {24'h582e06};
            111  :    rom_data_n  =   {24'h582f22};
            112  :    rom_data_n  =   {24'h583040};
            113  :    rom_data_n  =   {24'h583142};
            114  :    rom_data_n  =   {24'h583224};
            115  :    rom_data_n  =   {24'h583326};
            116  :    rom_data_n  =   {24'h583424};
            117  :    rom_data_n  =   {24'h583522};
            118  :    rom_data_n  =   {24'h583622};
            119  :    rom_data_n  =   {24'h583726};
            120  :    rom_data_n  =   {24'h583844};
            121  :    rom_data_n  =   {24'h583924};
            122  :    rom_data_n  =   {24'h583a26};
            123  :    rom_data_n  =   {24'h583b28};
            124  :    rom_data_n  =   {24'h583c42};
            125  :    rom_data_n  =   {24'h583dce}; // LENC BR offset
        //AWB
            126  :    rom_data_n  =   {24'h5180ff}; // AWB B block
            127  :    rom_data_n  =   {24'h5181f2}; // AWB control
            128  :    rom_data_n  =   {24'h518200}; // [7:4] max local counter, [3:0] max fast counter
            129  :    rom_data_n  =   {24'h518314}; // AWB advance
            130  :    rom_data_n  =   {24'h518425};
            131  :    rom_data_n  =   {24'h518524};
            132  :    rom_data_n  =   {24'h518609};
            133  :    rom_data_n  =   {24'h518709};
            134  :    rom_data_n  =   {24'h518809};
            135  :    rom_data_n  =   {24'h518975};
            136  :    rom_data_n  =   {24'h518a54};
            137  :    rom_data_n  =   {24'h518be0};
            138  :    rom_data_n  =   {24'h518cb2};
            139  :    rom_data_n  =   {24'h518d42};
            140  :    rom_data_n  =   {24'h518e3d};
            141  :    rom_data_n  =   {24'h518f56};
            142  :    rom_data_n  =   {24'h519046};
            143  :    rom_data_n  =   {24'h5191f8}; // AWB top limit
            144  :    rom_data_n  =   {24'h519204}; // AWB botton limit
            145  :    rom_data_n  =   {24'h519370}; // Red limit
            146  :    rom_data_n  =   {24'h5194f0}; // Green Limit
            147  :    rom_data_n  =   {24'h5195f0}; // Blue limit
            148  :    rom_data_n  =   {24'h519603}; // AWB control
            149  :    rom_data_n  =   {24'h519701}; // local limit
            150  :    rom_data_n  =   {24'h519804};
            151  :    rom_data_n  =   {24'h519912};
            152  :    rom_data_n  =   {24'h519a04};
            153  :    rom_data_n  =   {24'h519b00};
            154  :    rom_data_n  =   {24'h519c06};
            155  :    rom_data_n  =   {24'h519d82};
            156  :    rom_data_n  =   {24'h519e38}; // AWB control
        //Gamma
            157  :    rom_data_n  =   {24'h548001}; // BIAS plus on
            158  :    rom_data_n  =   {24'h548108};
            159  :    rom_data_n  =   {24'h548214};
            160  :    rom_data_n  =   {24'h548328};
            161  :    rom_data_n  =   {24'h548451};
            162  :    rom_data_n  =   {24'h548565};
            163  :    rom_data_n  =   {24'h548671};
            164  :    rom_data_n  =   {24'h54877d};
            165  :    rom_data_n  =   {24'h548887};
            166  :    rom_data_n  =   {24'h548991};
            167  :    rom_data_n  =   {24'h548a9a};
            168  :    rom_data_n  =   {24'h548baa};
            169  :    rom_data_n  =   {24'h548cb8};
            170  :    rom_data_n  =   {24'h548dcd};
            171  :    rom_data_n  =   {24'h548edd};
            172  :    rom_data_n  =   {24'h548fea};
            173  :    rom_data_n  =   {24'h54901d};
        //color matrix
            174  :    rom_data_n  =   {24'h53811e}; // CMX1 for Y
            175  :    rom_data_n  =   {24'h53825b}; // CMX2 for Y
            176  :    rom_data_n  =   {24'h538308}; // CMX3 for Y
            177  :    rom_data_n  =   {24'h53840a}; // CMX4 for U
            178  :    rom_data_n  =   {24'h53857e}; // CMX5 for U
            179  :    rom_data_n  =   {24'h538688}; // CMX6 for U
            180  :    rom_data_n  =   {24'h53877c}; // CMX7 for V
            181  :    rom_data_n  =   {24'h53886c}; // CMX8 for V
            182  :    rom_data_n  =   {24'h538910}; // CMX9 for V
            183  :    rom_data_n  =   {24'h538a01}; // sign[9]
            184  :    rom_data_n  =   {24'h538b98}; // sign[8:1]
        //UV adjust
            185  :    rom_data_n  =   {24'h558006}; // brightness on, saturation on
            186  :    rom_data_n  =   {24'h558340}; // Sat U
            187  :    rom_data_n  =   {24'h558410}; // Sat V
            188  :    rom_data_n  =   {24'h558910}; // UV adjust th1
            189  :    rom_data_n  =   {24'h558a00}; // UV adjust th2[8]
            190  :    rom_data_n  =   {24'h558bf8}; // UV adjust th2[7:0]
            191  :    rom_data_n  =   {24'h501d40}; // enable manual offset in contrast
        //CIP
            192  :    rom_data_n  =   {24'h530008}; // sharpen-MT th1
            193  :    rom_data_n  =   {24'h530130}; // sharpen-MT th2
            194  :    rom_data_n  =   {24'h530210}; // sharpen-MT off1
            195  :    rom_data_n  =   {24'h530300}; // sharpen-MT off2
            196  :    rom_data_n  =   {24'h530408}; // De-noise th1
            197  :    rom_data_n  =   {24'h530530}; // De-noise th2
            198  :    rom_data_n  =   {24'h530608}; // De-noise off1
            199  :    rom_data_n  =   {24'h530716}; // De-noise off2
            200  :    rom_data_n  =   {24'h530908}; // sharpen-TH th1
            201  :    rom_data_n  =   {24'h530a30}; // sharpen-TH th2
            202  :    rom_data_n  =   {24'h530b04}; // sharpen-TH off1
            203  :    rom_data_n  =   {24'h530c06}; // sharpen-TH off2
            204  :    rom_data_n  =   {24'h502500};
        //              {0x3008, 0x02}, // wake up from software power down
            205  :    rom_data_n  =   {24'h300802};// wake up from software power down
        // RGB VGA 30fps, night mode 5fps
        // Input Clock = 24Mhz, PCLK = 56MHz
//            //205  :    rom_data_n  =   {24'h303511}; // PLL
//            205  :    rom_data_n  =   {24'h303511}; // PLL
//            206  :    rom_data_n  =   {24'h303646}; // PLL
//            207  :    rom_data_n  =   {24'h3c0708}; // light meter 1 threshold [7:0]
//            208  :    rom_data_n  =   {24'h382042}; // Sensor flip off, ISP flip off
//            209  :    rom_data_n  =   {24'h382105}; // Sensor mirror off, ISP mirror on, H binning on
//            210  :    rom_data_n  =   {24'h381431}; // X INC
//            211  :    rom_data_n  =   {24'h381531}; // Y INC
//            212  :    rom_data_n  =   {24'h380000}; // HS
//            213  :    rom_data_n  =   {24'h380100}; // HS
//            214  :    rom_data_n  =   {24'h380200}; // VS
//            215  :    rom_data_n  =   {24'h380304}; // VS
//            216  :    rom_data_n  =   {24'h38040a}; // HW (HE)
//            217  :    rom_data_n  =   {24'h38053f}; // HW (HE)
//            218  :    rom_data_n  =   {24'h380607}; // VH (VE)
//            219  :    rom_data_n  =   {24'h38079b}; // VH (VE)
//            220  :    rom_data_n  =   {24'h380802}; // DVPHO//01
//            221  :    rom_data_n  =   {24'h380980}; // DVPHO//40
//            222  :    rom_data_n  =   {24'h380a01}; // DVPVO//0
//            223  :    rom_data_n  =   {24'h380be0}; // DVPVO//f0
//            224  :    rom_data_n  =   {24'h380c07}; // HTS
//            225  :    rom_data_n  =   {24'h380d68}; // HTS
//            226  :    rom_data_n  =   {24'h380e03}; // VTS
//            227  :    rom_data_n  =   {24'h380fd8}; // VTS
//            228  :    rom_data_n  =   {24'h381306}; // Timing Voffset
//            229  :    rom_data_n  =   {24'h361800};
//            230  :    rom_data_n  =   {24'h361229};
//            231  :    rom_data_n  =   {24'h370952};
//            232  :    rom_data_n  =   {24'h370c03};
//            233  :    rom_data_n  =   {24'h3a0217}; // 60Hz max exposure, night mode 5fps
//            234  :    rom_data_n  =   {24'h3a0310}; // 60Hz max exposure
//        // banding filters are calculated automatically in camera driver
//        //{0x3a08, 0x01}, // B50 step
//        //{0x3a09, 0x27}, // B50 step
//        //{0x3a0a, 0x00}, // B60 step
//        //{0x3a0b, 0xf6}, // B60 step
//        //{0x3a0e, 0x03}, // 50Hz max band
//        //{0x3a0d, 0x04}, // 60Hz max band
//            235  :    rom_data_n  =   {24'h3a1417}; // 50Hz max exposure, night mode 5fps
//            236  :    rom_data_n  =   {24'h3a1510}; // 50Hz max exposure
//            237  :    rom_data_n  =   {24'h400402}; // BLC 2 lines
//            238  :    rom_data_n  =   {24'h30021c}; // reset JFIFO, SFIFO, JPEG
//            239  :    rom_data_n  =   {24'h3006c3}; // disable clock of JPEG2x, JPEG
//            240  :    rom_data_n  =   {24'h471303}; // JPEG mode 3
//            241  :    rom_data_n  =   {24'h440704}; // Quantization scale
//            242  :    rom_data_n  =   {24'h460b35};
//            243  :    rom_data_n  =   {24'h460c22};
//            244  :    rom_data_n  =   {24'h483722}; // DVP CLK divider
//            245  :    rom_data_n  =   {24'h382402}; // DVP CLK divider
//            246  :    rom_data_n  =   {24'h5001a3}; // SDE off, scale on, UV average on, color matrix on, AWB on
//            247  :    rom_data_n  =   {24'h350300}; // AEC/AGC on
        
////            248  :    rom_data_n  =   {24'h503d80};//test color bar
////            249  :    rom_data_n  =   {24'h474100};//test pattern enable, Test pattern 8-bit
//            248  :    rom_data_n  =   {24'h300802};// wake up from software power down
         206  :    rom_data_n  =   {24'h303541};  //PLL//11//41
         207  :    rom_data_n  =   {24'h303669};  //PLL//46
         208  :    rom_data_n  =   {24'h3C0707};  //ligntmeter threshold ?
         209  :    rom_data_n  =   {24'h382046};  //Sensor flip off, ISP flip on//41
         210  :    rom_data_n  =   {24'h382100};  //Sensor mirror on, ISP mirror on, H binning on//07
         
         211  :    rom_data_n  =   {24'h381431};  //X inc
         212  :    rom_data_n  =   {24'h381531};  //Y inc
         213  :    rom_data_n  =   {24'h380000}; // HS
         214  :    rom_data_n  =   {24'h380100}; // HS
         215  :    rom_data_n  =   {24'h380200}; // VS
        216  :    rom_data_n  =   {24'h380300}; // VS//04
        217  :    rom_data_n  =   {24'h38040a}; // HW (HE)
        218  :    rom_data_n  =   {24'h38053f}; // HW (HE)
        219  :    rom_data_n  =   {24'h380606}; // VH (VE)//07
        220  :    rom_data_n  =   {24'h3807a9}; // VH (VE)//9b
        221  :    rom_data_n  =   {16'h3808,DVPHO_H}; // DVPHO                      //02
        222  :    rom_data_n  =   {16'h3809,DVPHO_L}; // DVPHO 640                  //80
        223  :    rom_data_n  =   {16'h380a,DVPVO_H}; // DVPVO                            //01
        224  :    rom_data_n  =   {16'h380b,DVPVO_L}; // DVPVO 480                          //e0
        225  :    rom_data_n  =   {24'h380c05}; // HTS//07
        226  :    rom_data_n  =   {24'h380df8}; // HTS//68
        227  :    rom_data_n  =   {24'h380e03}; // VTS
        228  :    rom_data_n  =   {24'h380f84}; // VTS//d8
        229  :    rom_data_n  =   {24'h381304}; // Timing Voffset//06
        
//        Mysteris
        230  :    rom_data_n  =   {24'h361800};
        231  :    rom_data_n  =   {24'h361229};
        232  :    rom_data_n  =   {24'h370952};
        233  :    rom_data_n  =   {24'h370C03};
        
        234  :    rom_data_n  =   {24'h3A0202}; // 60Hz max exposure, night mode 5fps//17
        235  :    rom_data_n  =   {24'h3A03e0}; // 60Hz max exposure//10
        236  :    rom_data_n  =   {24'h3A1402}; // 50Hz max exposure, night mode 5fps//17
        237  :    rom_data_n  =   {24'h3A15e0}; // 50Hz max exposure//10
        
        238  :    rom_data_n  =   {24'h400402}; //Black Level Calibration 2 lines
        239  :    rom_data_n  =   {24'h30021c}; // reset JFIFO, SFIFO, JPEG
        240  :    rom_data_n  =   {24'h3006c3}; // disable clock of JPEG2x, JPEG
        241  :    rom_data_n  =   {24'h471303}; // JPEG mode 3 ?
        242  :    rom_data_n  =   {24'h440704}; // Quantization scale ?
        243  :    rom_data_n  =   {24'h460b37};//35!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        244  :    rom_data_n  =   {24'h460c20}; // DVP PCLK manual enable//22
        245  :    rom_data_n  =   {24'h483716}; // DVP CLK divider//22
        246  :    rom_data_n  =   {24'h382404}; // DVP CLK divider//02
//        247  :    rom_data_n  =   {24'h5001a3}; // SDE on, scale on, UV average off, color matrix on, AWB on
        247  :    rom_data_n  =   {24'h5001a2}; // SDE on, scale on, UV average off, color matrix on, AWB off
//        248  :    rom_data_n  =   {24'h350300}; // AEC/AGC on
        248  :    rom_data_n  =   {24'h350302}; // AEC/AGC off

        249  :    rom_data_n  =   {24'h340601}; // 249 - 255white balance manual day mode
        250  :    rom_data_n  =   {24'h340006}; // 
        251  :    rom_data_n  =   {24'h34011c}; // 
        252  :    rom_data_n  =   {24'h340204};
        253  :    rom_data_n  =   {24'h340300}; //
        254  :    rom_data_n  =   {24'h340404}; // 
        255  :    rom_data_n  =   {24'h3405f3};        
 // status below are for configuring the AGC/AEC registers from 0x3500-0x3502, 0x350A-0x350B, respectively.        
        256  :    rom_data_n  =   {24'h350000};
        257  :    rom_data_n  =   {24'h350107};
		258  :    rom_data_n  =   {24'h3502b0};       
        
//        249  :    rom_data_n  =   {24'h300000}; // enable blocks
//        250  :    rom_data_n  =   {24'h3004ff}; // enable clocks 
//        251  :    rom_data_n  =   {24'h300e58}; // MIPI power down, DVP enable
//        252  :    rom_data_n  =   {24'h302e00};
//        253  :    rom_data_n  =   {24'h430060}; // RGB565
//        254  :    rom_data_n  =   {24'h501f01}; // ISP RGB 
//        255  :    rom_data_n  =   {24'h440e00};
        
//        256  :    rom_data_n  =   {24'h310816}; //PCLK = pll_clki/2
//        257  :    rom_data_n  =   {24'h474023}; //PCLK,HREF,VSYNC active high//zdyz: 21

//        258  :    rom_data_n  =   {24'h503d80}; //rom_data_n=24'h503d80; test pattern selection control, 80:color bar,00: test disable
//        259  :    rom_data_n  =   {24'h474101}; //rom_data_n=24'h474101; test pattern enable, Test pattern 8-bit
        
        default :    rom_data_n  =   {24'h000000};
      endcase
    end
 endmodule