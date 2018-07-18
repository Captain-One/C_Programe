VPATH = ./code 
VPATH +=./code/asn1c 

OBJDIR = ./objects

SRCS = $(wildcard *.c) 
SRCS +=$(wildcard code/*.c)
SRCS +=$(wildcard code/asn1c/*.c)

DIR = $(notdir $(SRCS))

OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(DIR))

CC = gcc

#INCLUDES = -I. \
		   -I ./code \
		   -I ./code/asn1c

CCFLAGS = -g -Wall -O0
CCFLAGS += -D RRC_API_TEST_CASE
CCFLAGS += -D RRC_API_TEST_CASE_XML_PRINT
#CCFLAGS += -D ASN_DEBUG

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
	$(CC) $^ -o $@ 

$(OBJDIR)/%.o:%.c
	$(CC) -c $< -o $@ $(CCFLAGS) 

clean:
	rm -rf $(OBJDIR) $(OUTPUT)

.PHONY:clean

