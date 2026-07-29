#!/bin/bash

# GDB connect and excute

ELF_FILE="build/MCU_BASIC_STM32F4XX"

if [ ! -f "$ELF_FILE" ]; then
    echo "ERROR $ELF_FILE not found. build again"
    exit 1
fi

echo " GDB Debugger for $ELF_FILE..."
echo " Connect to OpenOCD at localhost:3333..."

gdb-multiarch -x openocd.gdb "$ELF_FILE"
