WS_ROOT := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
TARGET := hello_world

ifeq ($(OS),Windows_NT)
    MKDIR := mkdir
	CP := copy
	RM := rd /s /q
	SEP := \\
else
    MKDIR := mkdir -p
	CP := cp
	RM := rm -rf
	SEP := /
endif

build:
	$(MKDIR) $(WS_ROOT)$(SEP)build
	cd $(WS_ROOT)$(SEP)build && cmake .. && $(MAKE) -j

run:
	$(WS_ROOT)$(SEP)build$(SEP)$(TARGET)

clean:
	$(RM) $(WS_ROOT)$(SEP)build
