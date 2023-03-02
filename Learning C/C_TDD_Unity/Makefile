TARGET_EXEC := test_SimpleMath

SRC_DIRS := 
#############################
# ADD YOUR CODE TO TEST HERE:
SRC_DIRS += ./ProductionCode/SimpleMath

# ADD YOUR TEST CODE HERE
SRC_DIRS += ./tests
#############################
SRC_DIRS += ./test_lib

BUILD_DIR := ./build

CFLAGS =
CFLAGS += -O0
CFLAGS += -g
CFLAGS += -fstack-usage
CFLAGS += -fmessage-length=0
CFLAGS += -fdata-sections
CFLAGS += -ffunction-sections
CFLAGS += -pthread

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -std=gnu99
CFLAGS += -Waggregate-return
CFLAGS += -Warray-bounds
CFLAGS += -Wbad-function-cast
CFLAGS += -Wcast-align
CFLAGS += -Wcast-qual
CFLAGS += -Wconversion
CFLAGS += -Wdouble-promotion
CFLAGS += -Wfloat-equal
CFLAGS += -Winit-self
CFLAGS += -Wmissing-declarations
CFLAGS += -Wmissing-include-dirs
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wnested-externs
CFLAGS += -Wparentheses
CFLAGS += -Wpointer-arith
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wswitch-default
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code

# Find all the C we want to compile
SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.s')

# String substitution for every C/C++ file.
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c 
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean test
clean:
	rm -r $(BUILD_DIR)

test:
	./$(BUILD_DIR)/$(TARGET_EXEC)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)