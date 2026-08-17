TARGET  ?= Bebis64

SRC_DIR   := src
INC_DIR   := inc
BUILD_DIR := build
BIN_DIR   := bin

RAYLIB_DIR := vendor/raylib/src
RAYLIB_LIB := $(RAYLIB_DIR)/libraylib.a

INC_FLAGS_VENDOR := -I$(RAYLIB_DIR)

VENDOR_LIBS := -L$(RAYLIB_DIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

CC ?= cc
CSTD := -std=c99

WARN_FLAGS := -Wall -Wextra -Wpedantic
FEATURE_FLAGS := -D_POSIX_C_SOURCE=200809L
INC_FLAGS := -I$(INC_DIR) $(INC_FLAGS_VENDOR)
DEP_FLAGS := -MMD -MP

CFLAGS  ?= $(CSTD) $(WARN_FLAGS) $(FEATURE_FLAGS) $(INC_FLAGS) $(DEP_FLAGS)
LDFLAGS ?=
LDLIBS  ?= $(VENDOR_LIBS)

BUILD ?= release

ifeq ($(BUILD),debug)
    CFLAGS  += -O0 -g3 -DDEBUG -fsanitize=address,undefined
    LDFLAGS += -fsanitize=address,undefined
else ifeq ($(BUILD),release)
    CFLAGS  += -O2 -DNDEBUG
else
    $(error Gecersiz BUILD degeri: '$(BUILD)' (debug|release olmali))
endif

OBJ_DIR := $(BUILD_DIR)/$(BUILD)

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

BIN := $(BIN_DIR)/$(TARGET)

.PHONY: all clean clean-vendor run debug release install uninstall

all: $(BIN)

$(BIN): $(OBJS) $(RAYLIB_LIB) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)
	@echo "==> Derlendi: $@ (profil: $(BUILD))"

$(RAYLIB_LIB):
	$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

-include $(DEPS)

debug:
	$(MAKE) BUILD=debug

release:
	$(MAKE) BUILD=release

run: all
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

clean-vendor:
	$(MAKE) -C $(RAYLIB_DIR) clean

PREFIX ?= /usr/local

install: all
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 0755 $(BIN) $(DESTDIR)$(PREFIX)/bin/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)

