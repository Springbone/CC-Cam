# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "CAMERA_MODEL" -parent ${Page_0}
  ipgui::add_param $IPINST -name "CLOCK_FREQ" -parent ${Page_0}
  ipgui::add_param $IPINST -name "DVPHO" -parent ${Page_0}
  ipgui::add_param $IPINST -name "DVPVO" -parent ${Page_0}


}

proc update_PARAM_VALUE.CAMERA_MODEL { PARAM_VALUE.CAMERA_MODEL } {
	# Procedure called to update CAMERA_MODEL when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.CAMERA_MODEL { PARAM_VALUE.CAMERA_MODEL } {
	# Procedure called to validate CAMERA_MODEL
	return true
}

proc update_PARAM_VALUE.CLOCK_FREQ { PARAM_VALUE.CLOCK_FREQ } {
	# Procedure called to update CLOCK_FREQ when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.CLOCK_FREQ { PARAM_VALUE.CLOCK_FREQ } {
	# Procedure called to validate CLOCK_FREQ
	return true
}

proc update_PARAM_VALUE.DVPHO { PARAM_VALUE.DVPHO } {
	# Procedure called to update DVPHO when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DVPHO { PARAM_VALUE.DVPHO } {
	# Procedure called to validate DVPHO
	return true
}

proc update_PARAM_VALUE.DVPVO { PARAM_VALUE.DVPVO } {
	# Procedure called to update DVPVO when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DVPVO { PARAM_VALUE.DVPVO } {
	# Procedure called to validate DVPVO
	return true
}


proc update_MODELPARAM_VALUE.CAMERA_MODEL { MODELPARAM_VALUE.CAMERA_MODEL PARAM_VALUE.CAMERA_MODEL } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.CAMERA_MODEL}] ${MODELPARAM_VALUE.CAMERA_MODEL}
}

proc update_MODELPARAM_VALUE.CLOCK_FREQ { MODELPARAM_VALUE.CLOCK_FREQ PARAM_VALUE.CLOCK_FREQ } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.CLOCK_FREQ}] ${MODELPARAM_VALUE.CLOCK_FREQ}
}

proc update_MODELPARAM_VALUE.DVPHO { MODELPARAM_VALUE.DVPHO PARAM_VALUE.DVPHO } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DVPHO}] ${MODELPARAM_VALUE.DVPHO}
}

proc update_MODELPARAM_VALUE.DVPVO { MODELPARAM_VALUE.DVPVO PARAM_VALUE.DVPVO } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DVPVO}] ${MODELPARAM_VALUE.DVPVO}
}

