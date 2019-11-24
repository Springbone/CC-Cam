##Switches
#set_property -dict { PACKAGE_PIN M20   IOSTANDARD LVCMOS33 } [get_ports { AWB }]; #IO_L7N_T1_AD2N_35 Sch=sw[0]

##LEDs

#set_property -dict { PACKAGE_PIN R14   IOSTANDARD LVCMOS33 } [get_ports { led[0] }]; #IO_L6N_T0_VREF_34 Sch=led[0]
#set_property -dict { PACKAGE_PIN P14   IOSTANDARD LVCMOS33 } [get_ports { led[1] }]; #IO_L6P_T0_34 Sch=led[1]
#set_property -dict { PACKAGE_PIN N16   IOSTANDARD LVCMOS33 } [get_ports { led[2] }]; #IO_L21N_T3_DQS_AD14N_35 Sch=led[2]
#set_property -dict { PACKAGE_PIN M14   IOSTANDARD LVCMOS33 } [get_ports { led[3] }]; #IO_L23P_T3_35 Sch=led[3]

###############################5640#####################################3
#Camera specific constraints
set_property PULLUP true [get_ports ov_cam_iic_scl_io]
set_property PULLUP true [get_ports ov_cam_iic_sda_io]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets ov_cam_iic_pclk_IBUF]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets ov_cam_iic_pclk_IBUF_BUFG]

#Digital I/O Low

set_property -dict {PACKAGE_PIN T10 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_scl_io]
set_property -dict {PACKAGE_PIN T11 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_sda_io]
set_property -dict {PACKAGE_PIN V12 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_href]
set_property -dict {PACKAGE_PIN W13 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_vsync]
set_property -dict {PACKAGE_PIN W16 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_resetn]
#set_property -dict {PACKAGE_PIN U18 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_xclk]
set_property -dict {PACKAGE_PIN Y19 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_pclk]
set_property -dict {PACKAGE_PIN Y18 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_pwdn]

set_property -dict {PACKAGE_PIN Y14 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[0]}]
set_property -dict {PACKAGE_PIN V16 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[1]}]
set_property -dict {PACKAGE_PIN W14 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[2]}]
set_property -dict {PACKAGE_PIN W19 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[3]}]
set_property -dict {PACKAGE_PIN Y17 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[4]}]
set_property -dict {PACKAGE_PIN W18 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[5]}]
set_property -dict {PACKAGE_PIN Y16 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[6]}]
set_property -dict {PACKAGE_PIN U19 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[7]}]

###############################7670##################################
##Camera specific constraints
#set_property PULLUP true [get_ports ov_cam_iic_scl_io]
#set_property PULLUP true [get_ports ov_cam_iic_sda_io]
#set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets ov_cam_iic_pclk_IBUF]
#set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets ov_cam_iic_pclk_IBUF_BUFG]

##Digital I/O Low

#set_property -dict {PACKAGE_PIN W13 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_scl_io]
#set_property -dict {PACKAGE_PIN T10 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_sda_io]
#set_property -dict {PACKAGE_PIN T11 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_href]
#set_property -dict {PACKAGE_PIN V12 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_vsync]
#set_property -dict {PACKAGE_PIN U18 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_resetn]
#set_property -dict {PACKAGE_PIN Y14 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_xclk]
#set_property -dict {PACKAGE_PIN W16 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_pclk]
#set_property -dict {PACKAGE_PIN Y18 IOSTANDARD LVCMOS33} [get_ports ov_cam_iic_pwdn]

#set_property -dict {PACKAGE_PIN Y19 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[0]}]
#set_property -dict {PACKAGE_PIN U19 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[1]}]
#set_property -dict {PACKAGE_PIN Y16 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[2]}]
#set_property -dict {PACKAGE_PIN W18 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[3]}]
#set_property -dict {PACKAGE_PIN Y17 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[4]}]
#set_property -dict {PACKAGE_PIN W19 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[5]}]
#set_property -dict {PACKAGE_PIN W14 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[6]}]
#set_property -dict {PACKAGE_PIN V16 IOSTANDARD LVCMOS33} [get_ports {ov_cam_iic_d[7]}]

##HDMI Tx

set_property -dict {PACKAGE_PIN L17 IOSTANDARD TMDS_33} [get_ports hdmi_out_clk_n]
set_property -dict {PACKAGE_PIN L16 IOSTANDARD TMDS_33} [get_ports hdmi_out_clk_p]
set_property -dict {PACKAGE_PIN K18 IOSTANDARD TMDS_33} [get_ports {hdmi_out_data_n[0]}]
set_property -dict {PACKAGE_PIN K17 IOSTANDARD TMDS_33} [get_ports {hdmi_out_data_p[0]}]
set_property -dict {PACKAGE_PIN J19 IOSTANDARD TMDS_33} [get_ports {hdmi_out_data_n[1]}]
set_property -dict {PACKAGE_PIN K19 IOSTANDARD TMDS_33} [get_ports {hdmi_out_data_p[1]}]
set_property -dict {PACKAGE_PIN H18 IOSTANDARD TMDS_33} [get_ports {hdmi_out_data_n[2]}]
set_property -dict {PACKAGE_PIN J18 IOSTANDARD TMDS_33} [get_ports {hdmi_out_data_p[2]}]

#Switches

set_property -dict { PACKAGE_PIN M20   IOSTANDARD LVCMOS33 } [get_ports { sw0_1bit_tri_i[0] }]; #IO_L7N_T1_AD2N_35 Sch=sw[0]
set_property -dict { PACKAGE_PIN M19   IOSTANDARD LVCMOS33 } [get_ports { sw1_1bit_reset }]; #IO_L7P_T1_AD2P_35 Sch=sw[1]

#RGB LEDs

set_property -dict { PACKAGE_PIN L15   IOSTANDARD LVCMOS33 } [get_ports { rgb_led[0] }]; #IO_L22N_T3_AD7N_35 Sch=led4_b
set_property -dict { PACKAGE_PIN G17   IOSTANDARD LVCMOS33 } [get_ports { rgb_led[1] }]; #IO_L16P_T2_35 Sch=led4_g
set_property -dict { PACKAGE_PIN N15   IOSTANDARD LVCMOS33 } [get_ports { rgb_led[2] }]; #IO_L21P_T3_DQS_AD14P_35 Sch=led4_r
set_property -dict { PACKAGE_PIN G14   IOSTANDARD LVCMOS33 } [get_ports { rgb_led[3] }]; #IO_0_35 Sch=led5_b
set_property -dict { PACKAGE_PIN L14   IOSTANDARD LVCMOS33 } [get_ports { rgb_led[4] }]; #IO_L22P_T3_AD7P_35 Sch=led5_g
set_property -dict { PACKAGE_PIN M15   IOSTANDARD LVCMOS33 } [get_ports { rgb_led[5] }]; #IO_L23N_T3_35 Sch=led5_r

#LEDs

set_property -dict { PACKAGE_PIN R14   IOSTANDARD LVCMOS33 } [get_ports { leds_4bits[0] }]; #IO_L6N_T0_VREF_34 Sch=led[0]
set_property -dict { PACKAGE_PIN P14   IOSTANDARD LVCMOS33 } [get_ports { leds_4bits[1] }]; #IO_L6P_T0_34 Sch=led[1]
set_property -dict { PACKAGE_PIN N16   IOSTANDARD LVCMOS33 } [get_ports { leds_4bits[2] }]; #IO_L21N_T3_DQS_AD14N_35 Sch=led[2]
set_property -dict { PACKAGE_PIN M14   IOSTANDARD LVCMOS33 } [get_ports { leds_4bits[3] }]; #IO_L23P_T3_35 Sch=led[3]

#Buttons

set_property -dict { PACKAGE_PIN D19   IOSTANDARD LVCMOS33 } [get_ports { btns_4bits[0] }]; #IO_L4P_T0_35 Sch=btn[0]
set_property -dict { PACKAGE_PIN D20   IOSTANDARD LVCMOS33 } [get_ports { btns_4bits[1] }]; #IO_L4N_T0_35 Sch=btn[1]
set_property -dict { PACKAGE_PIN L20   IOSTANDARD LVCMOS33 } [get_ports { btns_4bits[2] }]; #IO_L9N_T1_DQS_AD3N_35 Sch=btn[2]
set_property -dict { PACKAGE_PIN L19   IOSTANDARD LVCMOS33 } [get_ports { btns_4bits[3] }]; #IO_L9P_T1_DQS_AD3P_35 Sch=btn[3]