TARGET = mian
TARGET2 = ./build

SRCS = $(wildcard *.c)
DIR = $(notdir $(SRCS))
OBJS = $(patsubst %.c,$(TARGET2)/%.o,$(DIR))

CC = gcc

all: $(TARGET2) $(TARGET) 

$(TARGET2):
	mkdir -p $(TARGET2)
	@echo $(OBJS)

$(TARGET):$(OBJS)
	$(CC) $^ -o $@
$(TARGET2)/%.o:%.c
	$(CC) $< -c $@
	
clean:
    rm -rf $(TARGET2) $(TARGET)
.PHONY:clean


	

