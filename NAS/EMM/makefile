include make.inc

#子目录的Makefile直接读取其子目录就行
SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')

SUBDIRS := $(subst $(RMDIR), , $(SUBDIRS))


#以下同根目录下的makefile的相同代码的解释
#C_SOURCE=${wildcard *.c}
#C_OBJS=${patsubst %.c, %.o, $(C_SOURCE)}
#CXX_SOURCE=${wildcard *.cpp}
#CXX_OBJS=${patsubst %.cpp, %.o, $(CXX_SOURCE)}
#
#CUR_OBJS := $(C_OBJS) $(CXX_OBJS)
#
#OBJS += $(CUR_OBJS)

C_SOURCE=${wildcard *.c}
C_OBJS=${patsubst %.c, %.o, $(C_SOURCE)}

CXX_SOURCE=${wildcard *.cpp}
CXX_OBJS=${patsubst %.cpp, %.o, $(CXX_SOURCE)}

all:$(SUBDIRS) $(C_OBJS) $(CXX_OBJS)

$(SUBDIRS):ECHO
	make -C $@
	
$(C_OBJS):%.o:%.c
	$(CC) -g -c $(CFLAGS) $(CC_OPTS) $^ -o $(OUTPUTDIR)/$@

$(CXX_OBJS):%.o:%.cpp
	$(CXX) -c $(CFLAGS) $(CC_OPTS) $(DEFS) $(LIBS) $^ -o $(OUTPUTDIR)/$@

ECHO:
	@echo $(SUBDIRS)
	@echo $(OBJS)