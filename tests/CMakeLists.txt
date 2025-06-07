cmake_minimum_required(VERSION 3.16)

# Test configuration for each Cortex-M variant
set(CORTEX_VARIANTS m0 m0plus m1 m3)

foreach(VARIANT ${CORTEX_VARIANTS})
    set(TARGET_NAME test_firmware_cortex${VARIANT})
    
    # Compiler flags for each variant
    if(${VARIANT} STREQUAL "m0")
        set(CPU_FLAGS "-mcpu=cortex-m0")
    elseif(${VARIANT} STREQUAL "m0plus")
        set(CPU_FLAGS "-mcpu=cortex-m0plus")
    elseif(${VARIANT} STREQUAL "m1")
        set(CPU_FLAGS "-mcpu=cortex-m1")
    elseif(${VARIANT} STREQUAL "m3")
        set(CPU_FLAGS "-mcpu=cortex-m3")
    endif()
    
    # Create test executable
    add_executable(${TARGET_NAME}
        firmware/cortex${VARIANT}/main.cpp
        firmware/cortex${VARIANT}/test_nvic.cpp
        firmware/cortex${VARIANT}/test_systick.cpp
        firmware/cortex${VARIANT}/test_scb.cpp
        firmware/common/startup.cpp
    )
    
    # Set compiler flags
    target_compile_options(${TARGET_NAME} PRIVATE
        ${CPU_FLAGS}
        -mthumb
        -Wall
        -Wextra
        -Os
        -ffunction-sections
        -fdata-sections
        -ffreestanding
        -fno-exceptions
        -fno-rtti
    )
    
    # Set linker flags
    target_link_options(${TARGET_NAME} PRIVATE
        ${CPU_FLAGS}
        -mthumb
        -nostartfiles
        -Wl,--gc-sections
        -Wl,-Map=${TARGET_NAME}.map
        -T${CMAKE_CURRENT_SOURCE_DIR}/firmware/cortex${VARIANT}/linker.ld
    )
    
    # Link with the main library
    target_link_libraries(${TARGET_NAME} PRIVATE
        ARMCortexM::ARMCortexM
    )
    
    # Include directories
    target_include_directories(${TARGET_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/firmware
    )
    
    # Add test
    add_test(
        NAME test_cortex${VARIANT}
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/run_test.sh ${VARIANT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endforeach()

# Add custom target to run all tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${CORTEX_VARIANTS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
