# Default target
default: all


#==============================================================================#
# Build Options                                                                #
#==============================================================================#

TARGET := tnt-allegro
TNT_SPLAT_DIR := ../tnt-splat

TNT_SPLAT_C_FILES := 003E40.c 006B30.c 0073F0.c 0074E0.c 026900.c 026C80.c sprite.c color.c contq.c piecedefs.c playervars.c gamevars.c 033310.c mobilepiece.c ghostpiece.c currentpiece.c piecehold.c boardinfo.c frameact.c cube.c ids.c boardpieces.c bag63.c nextpieces.c fallingcubes.c mobilecubes.c board.c multisquare.c linescan.c gamestats.c dbgprntrrl.c tetris.c setplayer.c gamefinish.c pfgfx.c lineeffect.c


#==============================================================================#
# Target Executable and Sources                                                #
#==============================================================================#

# BUILD_DIR is the location where all build artifacts are placed
BUILD_DIR := build
PROGRAM := $(BUILD_DIR)/$(TARGET)

# Directories containing source files
SRC_DIRS := src

# Source code files
C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(TNT_SPLAT_C_FILES),$(BUILD_DIR)/tnt-splat/src/newtetris/$(file:.c=.o))


#==============================================================================#
# Compiler Options                                                             #
#==============================================================================#

CC := gcc

INCLUDE_DIRS := include $(TNT_SPLAT_DIR)/include

CFLAGS := $(foreach i,$(INCLUDE_DIRS),-I$(i))

LDFLAGS := -lallegro_primitives -lallegro_font -lallegro -lm
#LDFLAGS := -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro -lm


#==============================================================================#
# Main Targets                                                                 #
#==============================================================================#

all: $(PROGRAM)

clean:
	$(RM) -r $(BUILD_DIR)

ALL_DIRS := $(addprefix $(BUILD_DIR)/,$(SRC_DIRS)) \
            $(BUILD_DIR)/tnt-splat/src/newtetris

# Make sure build directory exists before compiling anything
$(shell mkdir -p $(ALL_DIRS))


#==============================================================================#
# Compilation Recipes                                                          #
#==============================================================================#

# Compile C code
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/tnt-splat/%.o: $(TNT_SPLAT_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(PROGRAM): $(O_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)



.PHONY: all clean default
# with no prerequisites, .SECONDARY causes no intermediate target to be removed
.SECONDARY:

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules

# --- Debugging
# run `make print-VARIABLE` to debug that variable
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
