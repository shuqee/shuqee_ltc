#!/usr/bin/env python3

import sys
import shutil  
import os  
import os.path
import binascii

path_output = "..\\output\\"

if os.path.exists(path_output) == False:
	os.mkdir(path_output)

name_bootloader_hex = "bootloader.hex"
path_output_bootloader_hex = path_output + name_bootloader_hex

if os.path.exists(path_output_bootloader_hex) == False:
	sys.exit(0)
	
name_app_hex = "udp_demo.hex"
path_output_app_hex = path_output + name_app_hex

if os.path.exists(path_output_app_hex) == False:
	sys.exit(0)

name_bootloader_app_hex = "bootloader_app.hex"
path_output_bootloader_app_hex = path_output + name_bootloader_app_hex

file_bootloader_hex = open(path_output_bootloader_hex,"r")  
str_bootloader_hex_lines = file_bootloader_hex.readlines( )
file_bootloader_hex.close()

str_bootdata_hex = ":020000040800F2" + "\n"
str_bootdata_hex = str_bootdata_hex + ":01C00000003F" + "\n"
str_bootdata_hex = str_bootdata_hex + ":04000005080001519D" + "\n"

file_app_hex = open(path_output_app_hex,"r")  
str_app_hex = file_app_hex.read( )
file_app_hex.close()

str_bootloader_app_hex = ""

for line in str_bootloader_hex_lines:
	if ":00000001FF" in line:
		continue
	str_bootloader_app_hex = str_bootloader_app_hex + line
str_bootloader_app_hex = str_bootloader_app_hex + str_bootdata_hex
str_bootloader_app_hex = str_bootloader_app_hex + str_app_hex

file_bootloader_app_hex = open(path_output_bootloader_app_hex,"w")  
file_bootloader_app_hex.write(str_bootloader_app_hex)
file_bootloader_app_hex.close()