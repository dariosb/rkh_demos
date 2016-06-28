###############################################################################
#
# Copyright 2014, ACSE & CADIEEL
#    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
#    CADIEEL: http://www.cadieel.org.ar
#
# This file is part of CIAA Firmware.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################

# Project path
# Defined $(PROJECT_PATH) in eclipse environment
PRJ_MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
ECLIPSE_PATH = $(PWD)
FIX_PATH = $(subst \,/,$(ECLIPSE_PATH))..
FIX1_PATH = $(subst H:,/cygdrive/h,$(FIX_PATH))
#override PROJECT_PATH := $(FIX1_PATH)

# Project Name: based on Project Path and used to define OSEK configuration file
#PROJECT_NAME = $(lastword $(subst $(DS), , $(PROJECT_PATH)))
PROJECT_NAME = blinky

# source path
$(PROJECT_NAME)_SRC_PATH  += $(PROJECT_PATH)$(DS)src

# include path
INC_FILES            += $(PROJECT_PATH)$(DS)inc

# project source files
SRC_FILES            += $(wildcard $($(PROJECT_NAME)_SRC_PATH)$(DS)*.c)

###############################################################################
# configuration for OSEK-OS
OIL_FILES            += $(PROJECT_PATH)$(DS)etc$(DS)$(PROJECT_NAME).oil
# Modules needed for this example
MODS ?= modules$(DS)posix           \
        modules$(DS)ciaak           \
        modules$(DS)drivers         \
        modules$(DS)rtos            \
        modules$(DS)libs

###############################################################################
# RKH variables definition
#RKH_PATH  		 ?= /cygdrive$(DS)h$(DS)vortex$(DS)RKH
RKH_PATH  		 ?= $(PROJECT_PATH)$(DS)..$(DS)..$(DS)rkh
RKH_PLATFORM     ?= __CIAA_OSEK__

include $(RKH_PATH)$(DS)Makefile

# Add RKH source files and includes
SRC_FILES           += $(RKH_SRC_FILES)
INC_FILES			+= $(RKH_INC_PATH)

print:
	@echo $(RKH_SRC_PATH)
	@echo $(RKH_SRC_FILES)
	@echo $(RKH_PORT_PATH)
	@echo $(SRC_FILES)
	@echo $(INC_FILES)
	@echo $(ECLIPSE_PATH)
	@echo $(FIX_PATH)
	@echo $(FIX1_PATH)
	@echo $(PROJECT_PATH)
	@echo $(OIL_FILES)

