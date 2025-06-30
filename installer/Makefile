LIBPS4  := $(PS4SDK)/libPS4

CC	:= gcc
OBJCOPY	:= objcopy
RM	:= rm
ODIR	:= build
SDIR	:= source
IDIR	:= include
IDIRS	:= -I$(LIBPS4)/include -I$(IDIR)
LDIRS	:= -L$(LIBPS4)
MAPFILE := $(shell basename $(CURDIR)).map
TARGET  := $(shell basename $(CURDIR)).bin

# Compiler flags
OPTIMIZATION := -Os
STANDARDS    := -std=c11 -fno-builtin -nostartfiles -nostdlib
WARNINGS     := -Wno-unused-const-variable -Wall -Wextra # -Werror
ARCH_FLAGS   := -masm=intel -march=btver2 -mtune=btver2 -m64 -mabi=sysv -mcmodel=small -fpie
CFLAGS       := $(IDIRS) $(OPTIMIZATION) $(STANDARDS) $(WARNINGS) $(ARCH_FLAGS) -ffunction-sections -fdata-sections

# Linker flags
LFLAGS	:= $(LDIRS) -Xlinker -T $(LIBPS4)/linker.x -Xlinker -Map=$(MAPFILE) -Wl,--build-id=none -Wl,--gc-sections -Wl,-z,noexecstack

# Source files discovery
CFILES	:= $(wildcard $(SDIR)/*.c)
SFILES	:= $(wildcard $(SDIR)/*.s)
OBJS	:= $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(CFILES)) $(patsubst $(SDIR)/%.s, $(ODIR)/%.o, $(SFILES))
DEPS	:= $(OBJS:.o=.d)

# Libraries
LIBS	:= -lPS4

# Include dependency files
-include $(DEPS)

# Main targets
.PHONY: all
all: $(TARGET)

# Main build target
$(TARGET): $(ODIR) $(OBJS)
	@echo "Linking $(TARGET)..."
	@$(CC) $(LIBPS4)/crt0.s $(ODIR)/*.o -o temp.t $(CFLAGS) $(LFLAGS) $(LIBS)
	@$(OBJCOPY) -O binary temp.t $(TARGET)
	@$(RM) -f temp.t
	@echo "Build complete: $(TARGET)"

# Compile source files with dependency generation
$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@echo "Compiling $<..."
	@$(CC) -MMD -MP -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.s | $(ODIR)
	@echo "Assembling $<..."
	@$(CC) -MMD -MP -c -o $@ $< $(CFLAGS)

# Create build directory
$(ODIR):
	@mkdir -p $@

# Utility targets
.PHONY: clean info help

clean:
	@echo "Cleaning build artifacts..."
	@$(RM) -rf $(TARGET) $(MAPFILE) $(ODIR) temp.t

info:
	@echo "Build Configuration:"
	@echo "  Target: $(TARGET)"
	@echo "  CC: $(CC)"
	@echo "  CFLAGS: $(CFLAGS)"
	@echo "  Source files: $(words $(CFILES)) C files, $(words $(SFILES)) assembly files"
	@echo "  Object files: $(words $(OBJS)) files"

help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  info    - Show build configuration"
	@echo "  help    - Show this help message"

.INTERMEDIATE: temp.t
