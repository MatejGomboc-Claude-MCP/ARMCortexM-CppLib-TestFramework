*** Settings ***
Resource    common_keywords.robot
Suite Setup    Start Renode
Suite Teardown    Stop Renode
Test Timeout    ${TEST_TIMEOUT}

*** Variables ***
${PLATFORM}    ${CURDIR}/../platforms/cortexm0.repl
${ELF_FILE}    ${CURDIR}/../build/test_firmware_cortexm0.elf

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

Test SysTick Reload
    [Documentation]    Test SysTick reload functionality
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    4    systick_reload

Test SCB CPUID
    [Documentation]    Test SCB CPUID register
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    5    scb_cpuid

Test SCB VTOR
    [Documentation]    Test SCB Vector Table Offset Register
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    6    scb_vtor

Test SCB AIRCR
    [Documentation]    Test SCB Application Interrupt and Reset Control Register
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    7    scb_aircr
