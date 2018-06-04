DIR_OBJ = ./obj
DIR_SRC = ./code

SRC = $(wildcard TestCase.c ${DIR_SRC}/*.c ${DIR_SRC}/asn1c/*.c)
OBJ = $(patsubst %.c, ${DIR_OBJ}/%.o, $(notdir $(SRC))) 
INC = $(patsubst %, -I%, $(shell find code -name '[a-zA-Z0-9]*'.h))

BIN_TARGET = main

CFLAGS = -g -Wall $(INC)

CFLAGS += -D RRC_API_TEST_CASE 
#CFLAGS += -D RRC_API_TEST_CASE_XML_PRINT

${BIN_TARGET}: ${OBJ}
	$(CC) $(OBJ) -o $@

${DIR_OBJ}/%.o: ${DIR_SRC}/asn1c/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
${DIR_OBJ}/%.o: TestCase.c
	$(CC) $(CFLAGS) -c $< -o $@
	

# 防止命名冲突例如有名为clean的文件
.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;