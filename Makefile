# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/) for showing how write a makefile like this
# Thanks to theicfire for writing a guide on how to use Make (https://makefiletutorial.com/)

TARGET_EXEC := LowResGladiator

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all C++ files I want to compile
# Note: ' around *.cpp ensures the * is passed directly to the "find" command in shell
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

# Prepends BUILD_DIR and appends .o to every src file
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %)
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImodeuleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# -MMD and -MP flags together generate MakeFiles!
#  These files will have .d instead of .o as the output
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# final build step
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# running "make clean" in shell runs command in "clean" target
# .PHONY ensures this command is run even if there is a file named "clean"
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)


# Include the .d makefiles
# '-' at front suppresses the errors of missing Makefiles
# Initially, all .d files will be missing, this avoids errors for that showing up
-include $(DEPS)
