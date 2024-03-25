# Minimal gcc makefile project for STM32F401xE

This contains the absolute bare minimum needed
to compile a blinky example for the STM32F401xE
on the command line with gcc and make and then
flash it to the demo board with OpenOCD. It is
using the original headers provided by STM and
ARM but only those for the core and peripheral
registers, none of the HAL or any other optional
libs.

The startup code has been implemented from scratch
and the linker script has been taken from the gcc
distribution and adapted for this controller and
therefore none of these files have any Atollic
copyright anymore. Startup code and SystemInit
have been implemented in plain C and are together
in one file gcc_startup_system.c.


# Usage

## Prerequisites

* install Linux on your PC
* get a NUCLEO-F401RE demo board from STMicroelectronics
* install the official arm-none-eabi-gcc toolchain from Launchpad
* install OpenOCD
* add this line to your udev rules (permissions for the STLink on the NUCLEO board)<br/>
  `ACTION=="add|change", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374b", MODE="664", GROUP="plugdev"`

## Build and run

* clone this repository
* connect the NUCLEO board
* `$ make install`
* watch the green LED blink while studying the reference manual

---

The files in this folder are the reasonable minimum 
set of files needed to compile bare metal C applications
for the STM32F401xE Microcontrollers. Most of them have
been taken from example projects provided by ST, some of 
them have been written from scratch for this purpose.


Files provided by ARM Ltd.
==========================
cmsis_gcc.h
core_cm4.h
core_cmFunc.h
core_cmInstr.h
core_cmSimd.h

These files are part of every Cortex-M4 project, they contain
all needed declarations and definitions to interact with the
ARM-core, they are the same for all manufacturers.


Files provided by STMicroelectronics
====================================
stm32f401xe.h

These are device specific and contain all declarations and
definitions needed to access the peripherals in this particular
device, most of it are structures and addresses of all peripheral 
device registers mentioned in the reference manual.


Files provided by GCC
=====================
gcc_linker.ld

This is almost the original version from the gcc samples folder,
the only difference is the block with the memory ranges near the
top of the file, ranges have been adjusted for this controller. 


Files written from scratch
==========================
gcc_startup_system.c

This file is provided by the author of this example project.
It contains the vector table, the startup code and all needed 
initialization that is executed before finally entering main(). 
This part is often split into separate files, partially written 
in assembly, but in this example everything is implemented in C 
and has been put into one file for simplicity.

