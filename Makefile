SRC_DIR = ./src
INCLUDE_DIR += .
BUILD_DIR = build
TARGET = $(notdir $(CURDIR))
CC := gcc
LD := $(CC)
CFLAGS	:= -g -ggdb -g3 -Wall -Wextra -Wpedantic -std=c11 -Wfloat-equal -Wshadow -Wswitch-enum -Wcast-qual -Wbad-function-cast -Wconversion -Wundef -Wunused-macros -Wduplicated-cond -Wduplicated-branches -Wreturn-local-addr
LDFLAGS := -lm

ifeq ($(CC), g++)
		TYPE = cpp
		SRCS += $(wildcard $(SRC_DIR)/*.$(TYPE))
		OBJS += $(patsubst %.$(TYPE), %.o, $(SRCS))
else
		TYPE = c
		SRCS += $(wildcard $(SRC_DIR)/*.$(TYPE))
		OBJS += $(patsubst %.$(TYPE), %.o, $(SRCS))
endif


lib: src/arrays.c src/arrays.h
	@mkdir -p $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $^ -o $(BUILD_DIR)/libossu-arrays.so
	# mv arrays.o build
	# ar rcs $(BUILD_DIR)/lib-ossu-arrays.a build/*.o

$(basename $(TARGET)) : $(OBJS)
		@echo "Linking" $@ "from" $^ "..."
		$(LD) -o $@ $^ $(LDFLAGS) $(LD_LIBS)
		@echo "Link finished\n"

$(OBJS) : %.o:%.$(TYPE)
		@echo "Compiling" $@ "from" $< "..."
		$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)
		@echo "Compiled finished\n"

.PHONY : clean cleanobj
clean : cleanobj
		@echo "Remove all executable file"
		rm -f $(TARGET)

cleanobj :
		@echo "Remove binary files"
		rm -f *.o

strace:
	@strace ./$(TARGET)
