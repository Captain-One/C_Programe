VPATH = ./EMM 
VPATH +=./EMM/MSG 
VPATH +=./ESM/MSG
VPATH +=./ESM
VPATH +=./IES
VPATH +=./UTIL
#VPATH +=./SECURITY
#VPATH +=../../SECURITY/Algorithm
#VPATH +=../../SECURITY/AUTH
#VPATH +=../../SECURITY/KDF

OBJDIR = ./objects

SRCS = $(wildcard *.c) 
SRCS +=$(wildcard EMM/MSG/*.c)
SRCS +=$(wildcard ESM/MSG/*.c)
SRCS +=$(wildcard IES/*.c)
SRCS +=$(wildcard UTIL/*.c)
#SRCS +=$(wildcard ../../SECURITY/Algorithm/*.c)
#SRCS +=$(wildcard ../../SECURITY/AUTH/*.c)
#SRCS +=$(wildcard ../../SECURITY/KDF/*.c)


DIR = $(notdir $(SRCS))

OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(DIR))

CC = gcc

INCLUDES = -I. \
		   -I ./EMM \
		   -I ./EMM/MSG \
		   -I ./ESM/MSG \
		   -I ./ESM \
		   -I ./IES \
		   -I ./UTIL \
		   -I ../../SECURITY/Algorithm \
		   -I ../../SECURITY/AUTH \
		   -I ../../SECURITY/KDF
		   
LDFLAGS = -lrt
		   
CCFLAGS = -g -Wall -O0 
#CCFLAGS += -D RRC_API_TEST_CASE
CCFLAGS += -D HAVE_UINT128_T
CCFLAGS += -D NAS_DEBUG

OUTPUT = main

all:$(OBJDIR) $(OUTPUT)

$(OBJDIR):
	@echo create objects dir
	mkdir -p $(OBJDIR)

#ppp:
#	@echo $(SRCS)
#	@echo $(DIR)
#	@echo $(OBJS)

$(OUTPUT):$(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o:%.c
	$(CC) -c $< -o $@ $(CCFLAGS) $(INCLUDES) 

clean:
	rm -rf $(OBJDIR) $(OUTPUT)

.PHONY:clean

