#!/bin/bash

echo "Project $1"

export PATH=$PATH:/home/jimbo/renesas/ra/toolchains/llvm_arm/LLVM-ET-Arm-18.1.3-Linux-x86_64/bin

rm $1.hex
rm $1_no_OSPI_Data.srec
rm OSPI_Data.srec
rm OSPI_Data_swapped.srec


llvm-objcopy $1.elf -O srec -R __ospi0_cs1_readonly\$\$  $1_no_OSPI_Data.srec
llvm-objcopy -O srec -j __ospi0_cs1_readonly\$\$ $1.elf "OSPI_Data.srec"
srec_cat "OSPI_Data.srec" -byte_swap -o "OSPI_Data_swapped.srec"

rm OSPI_Data.srec
