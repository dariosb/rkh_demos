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
#  \brief      RKH Application Make file
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
# RKH Makefile Path definition
RKH_APP_INC_PATH     = $(RKH_APP_PATH)
RKH_APP_SRC_FILES	 = $(wildcard $(RKH_APP_PATH)$(DS)*.c)

CFLAGS += -D$(RKH_PLATFORM)

###############################################################################
# RKH Makefile Path definition
RKH_PATH		?= $(RKH_APP_PATH)$(DS)..$(DS)..$(DS)..$(DS)..$(DS)rkh
RKH_PLATFORM	?= __CIAA_OSEK__

include $(RKH_PATH)$(DS)Makefile

# Add RKH source files and includes
SRC_FILES		+= $(RKH_SRC_FILES)
INC_FILES		+= $(RKH_INC_PATH)


###############################################################################
# Rule to compile RKH Application sources
%.o : $(RKH_APP_PATH)$(DS)%.c 
	@echo ' '
	@echo =====================================================================
	@echo Compiling RKH APP Source 'c' file: $<
	@echo ' '
	$(CC) $(CFLAGS) $(call cp4c,$<) -o $(OBJ_DIR)$(DS)$@
ifeq ($(MAKE_DEPENDENCIES),1)
	@echo ' '
	@echo Generating dependencies...
	$(CC) -MM $(CFLAGS) $(call cp4c,$<) > $(OBJ_DIR)$(DS)$(@:.o=.d)
else
	@echo ' '
	@echo Skipping make dependencies...
endif


	 	
