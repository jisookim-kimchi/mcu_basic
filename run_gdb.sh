#!/bin/bash

# GDB connect and execute

ELF_FILE="build/MCU_BASIC_STM32F4XX"

if [ ! -f "$ELF_FILE" ]; then
    echo "ERROR $ELF_FILE not found. build again"
    exit 1
fi

HOST_IP=$(ip route show default | awk '{print $3}')
if [ -z "$HOST_IP" ]; then
    HOST_IP="localhost"
fi

gdb-multiarch -ex "target extended-remote $HOST_IP:3333" -x openocd.gdb "$ELF_FILE"

