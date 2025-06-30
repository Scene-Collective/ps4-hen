CC	:= gcc
OBJCOPY	:= objcopy
RM	:= rm
ODIR	:= build
SDIR	:= source
IDIR	:= include
MAPFILE := $(shell basename $(CURDIR)).map
TARGET  := $(shell basename $(CURDIR)).bin

# Compiler flags
OPTIMIZATION := -Os
STANDARDS    := -std=gnu11 -fno-builtin -nostartfiles -nostdlib
WARNINGS     := -Wall # -Wextra # -Werror
ARCH_FLAGS   := -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -fpie
CFLAGS       := -I$(IDIR) $(OPTIMIZATION) $(STANDARDS) $(WARNINGS) $(ARCH_FLAGS)

# Linker flags
LFLAGS	:= -Xlinker -T ./linker.x -Xlinker -Map=$(MAPFILE) -Wl,--build-id=none

# Source files discovery
CFILES	:= $(shell find $(SDIR) -name '*.c' -type f)
OBJS	:= $(CFILES:$(SDIR)/%.c=$(ODIR)/%.o)
DEPS	:= $(OBJS:.o=.d)

# Include dependency files
-include $(DEPS)

# Main targets
.PHONY: all payload
all: payload payload-include

# Main build target
payload: $(ODIR) $(OBJS)
	@echo "Linking $(TARGET)..."
	@$(CC) $(OBJS) -o temp.t $(CFLAGS) $(LFLAGS)
	@$(OBJCOPY) -R .payload_bss temp.t temp.u
	@$(OBJCOPY) -O binary temp.u $(TARGET)
	@$(RM) -f temp.t temp.u
	@echo "Build complete: $(TARGET)"

# Generate payload include file for installer
payload-include: $(TARGET)
	@echo "Generating payload include file..."
	@if command -v xxd >/dev/null 2>&1; then                                                                  \
		xxd -i $(TARGET) | sed 's/^unsigned /static const unsigned /' > ../installer/source/kpayload.inc.c || { \
			echo "Error: xxd command failed while generating payload include file";                               \
			exit 1;                                                                                               \
		};                                                                                                      \
	else                                                                                                      \
		echo "Error: xxd command not found. Please install xxd";                                                \
		exit 1;                                                                                                 \
	fi
	@echo "Payload include file generated: ../installer/source/kpayload.inc.c"

# Compile source files with dependency generation
$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	@$(CC) -MMD -MP -c -o $@ $< $(CFLAGS)

# Create build directory
$(ODIR):
	@mkdir -p $@

# Utility targets
.PHONY: clean info help

clean:
	@echo "Cleaning build artifacts..."
	@$(RM) -rf $(TARGET) $(MAPFILE) $(ODIR) temp.t temp.u

info:
	@echo "Build Configuration:"
	@echo "  Target: $(TARGET)"
	@echo "  CC: $(CC)"
	@echo "  CFLAGS: $(CFLAGS)"
	@echo "  Source files: $(words $(CFILES)) files"
	@echo "  Object files: $(words $(OBJS)) files"

help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  info    - Show build configuration"
	@echo "  help    - Show this help message"

.INTERMEDIATE: temp.t temp.u
