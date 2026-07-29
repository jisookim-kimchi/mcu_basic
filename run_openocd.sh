#!/bin/bash

# OpenOCD GDB Server excute

echo "OpenOCD Server for STM32F4 ..."

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "bindto 0.0.0.0"
