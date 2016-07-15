###############################################################################
#
#                                Framework RKH
#                                -------------
#
#            State-machine framework for reactive embedded systems
#
#                      Copyright (C) 2010 Leandro Francucci.
#          All rights reserved. Protected by international copyright laws.
#
#
#  RKH is free software: you can redistribute it and/or modify it under the
#  terms of the GNU General Public License as published by the Free Software
#  Foundation, either version 3 of the License, or (at your option) any
#  later version.
#
#  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
#  WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#  more details.
#
#  You should have received a copy of the GNU General Public License along
#  with RKH, see copying.txt file.
#
#  Contact information:
#  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
#  e-mail:         francuccilea@gmail.com
#
###############################################################################
#
#  \file       Makefile
#
#  \brief      RKH Framework Make file for buildng CIAA Firmware Apps
#
###############################################################################
#
# Development history 
#
#  2016.06.27  DaBa  v0.0.01  Initial version
#
###############################################################################
#
# Autors
#  DaBa  Dario Baliña  dariosb@gmail.com
#
###############################################################################

###############################################################################
# Project source files path´s
# Must export $(PROJECT_PATH) in environment
ifeq ($(OS),Windows_NT)
# if winOS, convert paths from Windows to cygwin	
U_PROJECT_PATH	= $(shell cygpath -u $(PROJECT_PATH))
else
U_PROJECT_PATH	= $(PROJECT_PATH)
endif

PRJ_MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))

# Project Name: based on PROJECT_PATH, used to define OSEK configuration file
ifeq ($(OS),Windows_NT)
TOP_PRJ_PATH	= $(shell cygpath -u $(PROJECT_PATH)$(DS)..$(DS)..$(DS)..)
else
TOP_PRJ_PATH	= $(PROJECT_PATH)$(DS)..$(DS)..$(DS)blinky
endif
PROJECT_NAME	= $(lastword $(subst $(DS), , $(TOP_PRJ_PATH)))

# source path
$(PROJECT_NAME)_SRC_PATH  += $(U_PROJECT_PATH)src

# include path
INC_FILES      += $(U_PROJECT_PATH)inc

# project source files
SRC_FILES      += $(wildcard $($(PROJECT_NAME)_SRC_PATH)$(DS)*.c)

###############################################################################
# configuration for OSEK-OS
OIL_FILES      += $(U_PROJECT_PATH)etc$(DS)$(PROJECT_NAME).oil
# Modules needed for this example
MODS ?= modules$(DS)posix           \
        modules$(DS)ciaak           \
        modules$(DS)drivers         \
        modules$(DS)rtos            \
        modules$(DS)libs

###############################################################################
# RKH Application Makefile Path and port definition
RKH_APP_PATH	?= $(U_PROJECT_PATH)..$(DS)..$(DS)..
RKH_PLATFORM	?= __CIAA_OSEK__

include $(RKH_APP_PATH)$(DS)Makefile

# Add RKH Application source files and includes
SRC_FILES		+= $(RKH_APP_SRC_FILES)
INC_FILES		+= $(RKH_APP_INC_PATH)

pathdbg:
	@echo TOP_PRJ_PATH		: $(TOP_PRJ_PATH)
	@echo PROJECT_PATH		: $(PROJECT_PATH)
	@echo U_PROJECT_PATH	: $(U_PROJECT_PATH)
	@echo OIL_FILES			: $(OIL_FILES)
	@echo RKH_SRC_PATH		: $(RKH_SRC_PATH)
	@echo RKH_SRC_FILES		: $(RKH_SRC_FILES)
	@echo RKH_PORT_PATH		: $(RKH_PORT_PATH)
	@echo SRC_FILES			: $(SRC_FILES)
	@echo INC_FILES			: $(INC_FILES)

