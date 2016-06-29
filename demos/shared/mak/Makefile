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
# $(PROJECT_PATH) variable must be defined in environment
ifeq ($(OS),Windows_NT)
# if winOS, convert paths from Windows to cygwin	
U_PROJECT_PATH = $(shell cygpath -u $(PROJECT_PATH))
else
U_PROJECT_PATH = $(PROJECT_PATH)
endif

PRJ_MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))

# Project Name: based on PROJECT_PATH, used to define OSEK configuration file
PROJECT_NAME = $(lastword $(subst $(DS), , $(U_PROJECT_PATH)))

# source path
$(PROJECT_NAME)_SRC_PATH  += $(U_PROJECT_PATH)$(DS)src

# include path
INC_FILES            += $(U_PROJECT_PATH)$(DS)inc

# project source files
SRC_FILES            += $(wildcard $($(PROJECT_NAME)_SRC_PATH)$(DS)*.c)

###############################################################################
# configuration for OSEK-OS
OIL_FILES            += $(U_PROJECT_PATH)$(DS)etc$(DS)$(PROJECT_NAME).oil
# Modules needed for this example
MODS ?= modules$(DS)posix           \
        modules$(DS)ciaak           \
        modules$(DS)drivers         \
        modules$(DS)rtos            \
        modules$(DS)libs

###############################################################################
# RKH Makefile Path and port definition
RKH_PATH		?= $(U_PROJECT_PATH)$(DS)..$(DS)..$(DS)rkh
RKH_PLATFORM	?= __CIAA_OSEK__

include $(RKH_PATH)$(DS)Makefile

# Add RKH source files and includes
SRC_FILES		+= $(RKH_SRC_FILES)
INC_FILES		+= $(RKH_INC_PATH)

###############################################################################
# Rule to debug Path´s definitions
pathdbg:
	@echo $(PROJECT_PATH)
	@echo $(U_PROJECT_PATH)
	@echo $(OIL_FILES)
	@echo $(RKH_SRC_PATH)
	@echo $(RKH_SRC_FILES)
	@echo $(RKH_PORT_PATH)
	@echo $(SRC_FILES)
	@echo $(INC_FILES)

