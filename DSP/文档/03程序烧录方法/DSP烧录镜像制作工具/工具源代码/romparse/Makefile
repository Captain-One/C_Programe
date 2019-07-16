#/*
# *
# * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
# * 
# * 
# *  Redistribution and use in source and binary forms, with or without 
# *  modification, are permitted provided that the following conditions 
# *  are met:
# *
# *    Redistributions of source code must retain the above copyright 
# *    notice, this list of conditions and the following disclaimer.
# *
# *    Redistributions in binary form must reproduce the above copyright
# *    notice, this list of conditions and the following disclaimer in the 
# *    documentation and/or other materials provided with the   
# *    distribution.
# *
# *    Neither the name of Texas Instruments Incorporated nor the names of
# *    its contributors may be used to endorse or promote products derived
# *    from this software without specific prior written permission.
# *
# *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
# *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
# *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
# *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
# *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
# *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
# *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
# *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# *
#*/

ifeq ($(BISON_SKEL),yes)
  BSKEL= -S $(BISON_SKEL)
endif

#romparse: rparse.tab.o lex.yy.o romparse.c secutil
#	gcc -g -o romparse romparse.c ../seccvt/secutil.o rparse.tab.o lex.yy.o -I../.. -I. -I../seccvt

romparse: rparse.tab.o lex.yy.o romparse.c
	gcc -g -o romparse romparse.c rparse.tab.o lex.yy.o -I../.. -I. -I../seccvt

rparse.tab.o: rparse.y
	bison -d $(BSKEL) rparse.y
	gcc -g -c rparse.tab.c

lex.yy.o: rparse.flex
	flex rparse.flex
	gcc -g -c lex.yy.c


secutil:
	make -C ../seccvt util









