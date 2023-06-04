WS_ROOT := .
TARGET := hello_world
CONFIG := Release

ifeq ($(OS),Windows_NT)
    MKDIR := mkdir
	CP := copy
	RM := rd /s /q
	SEP := \\
	CMAKEFLAG := -DSQLITECPP_RUN_CPPLINT=OFF
	BUILD = cmake --build . --config $(CONFIG) -j %NUMBER_OF_PROCESSORS%
ifdef MINGW
	CMAKEFLAG += -DSQLITECPP_USE_GCOV=OFF -DSQLITECPP_BUILD_EXAMPLES=OFF -DSQLITECPP_BUILD_TESTS=OFF -G "MinGW Makefiles"
	BUILD = $(MAKE) -j
endif
else
    MKDIR := mkdir -p
	CP := cp
	RM := rm -rf
	SEP := /
endif

build:
	$(MKDIR) $(WS_ROOT)$(SEP)build
	cd $(WS_ROOT)$(SEP)build && cmake $(CMAKEFLAG) .. && $(BUILD)

run:
	$(WS_ROOT)$(SEP)build$(SEP)$(TARGET)

clean:
	$(RM) $(WS_ROOT)$(SEP)build
