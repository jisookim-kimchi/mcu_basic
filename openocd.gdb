# GDB Automation Command for OpenOCD
# Usage: gdb-multiarch -x openocd.gdb build/MCU_BASIC_STM32F4XX

# target extended-remote localhost:3333 (Handled dynamically in run_gdb.sh)
monitor reset halt
load
monitor reset halt
break main
continue
