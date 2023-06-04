WS_ROOT := .
TARGET := hello_world
CONFIG := Release

ifeq ($(OS),Windows_NT)
	SHELL := cmd.exe
    MKDIR := mkdir
	CP := copy
	RM := rd /s /q
	SEP := \\
	CMAKEFLAG := -DSQLITECPP_RUN_CPPLINT=OFF
ifdef MINGW
	CMAKEFLAG += -DCMAKE_EXE_LINKER_FLAGS="-static" -DSQLITECPP_USE_GCOV=OFF -DSQLITECPP_BUILD_EXAMPLES=OFF -DSQLITECPP_BUILD_TESTS=OFF -G "MinGW Makefiles"
	BUILD = $(MAKE) -j
else
	BUILD = cmake --build . --config $(CONFIG) -j %NUMBER_OF_PROCESSORS%
	POST_BUILD = $(CP) $(WS_ROOT)$(SEP)build$(SEP)$(CONFIG)$(SEP)$(TARGET).exe $(WS_ROOT)$(SEP)build$(SEP)$(TARGET).exe
endif
else
    MKDIR := mkdir -p
	CP := cp
	RM := rm -rf
	SEP := /
	BUILD = $(MAKE) -j
endif

build:
	$(MKDIR) $(WS_ROOT)$(SEP)build
	cd $(WS_ROOT)$(SEP)build && cmake $(CMAKEFLAG) .. && $(BUILD)
	$(POST_BUILD)

run:
	$(WS_ROOT)$(SEP)build$(SEP)$(TARGET)

clean:
	$(RM) $(WS_ROOT)$(SEP)build
