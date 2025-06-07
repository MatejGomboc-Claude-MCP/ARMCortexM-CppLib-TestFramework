# Makefile for building and running ARM Cortex-M library tests

# Toolchain
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Directories
ROOT_DIR = ..
BUILD_DIR = build
FIRMWARE_DIR = firmware
ROBOT_DIR = robot
PLATFORM_DIR = platforms

# Common flags
COMMON_FLAGS = -Wall -Wextra -Os -ffunction-sections -fdata-sections -ffreestanding
CXXFLAGS = $(COMMON_FLAGS) -fno-exceptions -fno-rtti -std=c++17
LDFLAGS = -nostartfiles -Wl,--gc-sections

# Include paths
INCLUDES = -I$(ROOT_DIR)/lib -I$(FIRMWARE_DIR)

# Cortex variants
VARIANTS = m0 m0plus m1 m3

# Define variant-specific flags
CORTEXM0_FLAGS = -mcpu=cortex-m0 -mthumb
CORTEXM0PLUS_FLAGS = -mcpu=cortex-m0plus -mthumb
CORTEXM1_FLAGS = -mcpu=cortex-m1 -mthumb
CORTEXM3_FLAGS = -mcpu=cortex-m3 -mthumb

# Test source files (common)
COMMON_SRCS = \
    $(FIRMWARE_DIR)/common/startup.cpp

# Variant-specific sources
define VARIANT_SRCS
$(FIRMWARE_DIR)/cortex$(1)/main.cpp \
$(FIRMWARE_DIR)/cortex$(1)/test_nvic.cpp \
$(FIRMWARE_DIR)/cortex$(1)/test_systick.cpp \
$(FIRMWARE_DIR)/cortex$(1)/test_scb.cpp
endef

# Default target
.PHONY: all
all: $(foreach v,$(VARIANTS),$(BUILD_DIR)/test_cortex$(v).elf)

# Create build directory
$(BUILD_DIR):
	@mkdir -p $@

# Build rules for each variant
define BUILD_VARIANT
$(BUILD_DIR)/test_cortex$(1).elf: $$(call VARIANT_SRCS,$(1)) $$(COMMON_SRCS) | $(BUILD_DIR)
	@echo "Building Cortex-$(shell echo $(1) | tr a-z A-Z) test firmware..."
	$$(CXX) $$(CORTEX$(shell echo $(1) | tr a-z A-Z)_FLAGS) $$(CXXFLAGS) $$(INCLUDES) \
		$$^ -o $$@ \
		$$(LDFLAGS) -T$(FIRMWARE_DIR)/cortex$(1)/linker.ld
	$$(SIZE) $$@
	$$(OBJCOPY) -O binary $$@ $$(BUILD_DIR)/test_cortex$(1).bin
	$$(OBJCOPY) -O ihex $$@ $$(BUILD_DIR)/test_cortex$(1).hex
endef

# Generate build rules for all variants
$(foreach v,$(VARIANTS),$(eval $(call BUILD_VARIANT,$(v))))

# Run tests with Robot Framework
.PHONY: test
test: all
	@echo "Running tests with Robot Framework..."
	@for variant in $(VARIANTS); do \
		echo "Testing Cortex-$$variant..."; \
		robot --variable VARIANT:$$variant \
		      --outputdir $(BUILD_DIR)/results_$$variant \
		      $(ROBOT_DIR)/cortex$${variant}_tests.robot; \
	done

# Run specific variant test
.PHONY: test-%
test-%: $(BUILD_DIR)/test_cortex%.elf
	@echo "Running Cortex-$* tests..."
	robot --variable VARIANT:$* \
	      --outputdir $(BUILD_DIR)/results_$* \
	      $(ROBOT_DIR)/cortex$*_tests.robot

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)

# Help
.PHONY: help
help:
	@echo "ARM Cortex-M Library Test Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  all              - Build all test firmware"
	@echo "  test             - Run all tests with Robot Framework"
	@echo "  test-m0          - Run Cortex-M0 tests only"
	@echo "  test-m0plus      - Run Cortex-M0+ tests only"
	@echo "  test-m1          - Run Cortex-M1 tests only"
	@echo "  test-m3          - Run Cortex-M3 tests only"
	@echo "  clean            - Remove build artifacts"
	@echo "  help             - Show this help message"

.DEFAULT_GOAL := help
