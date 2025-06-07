*** Settings ***
Resource    common_keywords.robot
Suite Setup    Start Renode
Suite Teardown    Stop Renode
Test Timeout    ${TEST_TIMEOUT}

*** Variables ***
${PLATFORM}    ${CURDIR}/../platforms/cortexm0plus.repl
${ELF_FILE}    ${CURDIR}/../build/test_firmware_cortexm0plus.elf

*** Keywords ***
Start Renode
    Start Process    ${RENODE}    --disable-xwt    --console
    Sleep    2s

Stop Renode
    Terminate All Processes

*** Test Cases ***
Test NVIC Enable Disable
    [Documentation]    Test NVIC interrupt enable/disable functionality
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    0    nvic_enable_disable

Test NVIC Pending
    [Documentation]    Test NVIC pending interrupt functionality
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    1    nvic_pending

Test NVIC Priority
    [Documentation]    Test NVIC interrupt priority functionality
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    2    nvic_priority

Test SysTick Basic
    [Documentation]    Test basic SysTick timer functionality
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    3    systick_basic

Test MPU Configuration
    [Documentation]    Test MPU configuration for Cortex-M0+
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    8    mpu_config

Test MPU Regions
    [Documentation]    Test MPU region setup
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    9    mpu_regions
