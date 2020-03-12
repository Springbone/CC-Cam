#!/usr/bin/python3.6
from pynq.lib import Wifi

port = Wifi()

# ssid = input("Type in the SSID:")
# pwd = input("Type in the password:")
ssid = 'LabVIEW-WLAN'
pwd = '00000000'
port.connect(ssid, pwd)