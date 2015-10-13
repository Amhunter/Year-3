# Modified by zhiyb (Yubo Zhi)

PRG	= System_Test_IMatto
SRC	= main.cpp rfm12.c spi.c
LIB	= tft-cpp 
#LIBDIR = ./libtft-cpp ./include 
VERSION	= 0.0.1

PRGER	= usbasp
MCU_TARGET	= atmega644p
OPTIMIZE	= -Os


DEFS	+= -DF_CPU=12000000 -D __PLATFORM_AVR__
LIBS	+= -Wl,-u,vfprintf -lprintf_flt -lm
INCS	+= 

EFUSE	= 0xFF
HFUSE	= 0x9C
LFUSE	= 0xE7

LOG	= ~/.make_avr.log

include Makefile.in

