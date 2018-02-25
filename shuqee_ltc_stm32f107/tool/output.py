#!/usr/bin/env python3

import sys
import shutil  
import os  
import os.path
import binascii

path_output = "..\\output\\"

if os.path.exists(path_output) == False:
	os.mkdir(path_output)

name_app_bin = "app.bin"
path_app_bin = "..\\shuqee_ltc\\MDK-ARM\\udp_demo\\" + name_app_bin
path_output_app_bin = path_output + name_app_bin

if os.path.exists(path_app_bin) == False:
	sys.exit(0)

shutil.copyfile(path_app_bin,path_output_app_bin)

name_app_hex = "udp_demo.hex"
path_app_hex = "..\\shuqee_ltc\\MDK-ARM\\udp_demo\\" + name_app_hex
path_output_app_hex = path_output + name_app_hex

if os.path.exists(path_app_hex) == False:
	sys.exit(0)
	
shutil.copyfile(path_app_hex,path_output_app_hex)
