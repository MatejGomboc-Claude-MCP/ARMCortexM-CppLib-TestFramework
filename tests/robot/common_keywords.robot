*** Settings ***
Library    OperatingSystem
Library    Process
Library    String

*** Variables ***
${RENODE}           renode
${TEST_TIMEOUT}     10s
${SRAM_BASE}        0x20000000
${TEST_RESULT}      ${SRAM_BASE}
${TEST_STATUS}      0x20000004
${TEST_MESSAGE}     0x20000008
${TEST_SELECTOR}    0x20001000

*** Keywords ***
Setup Test Platform
    [Arguments]    ${platform_file}    ${elf_file}
    Execute Command    mach create
    Execute Command    machine LoadPlatformDescription @${platform_file}
    Execute Command    sysbus LoadELF @${elf_file}

Run Test
    [Arguments]    ${test_index}
    Execute Command    sysbus WriteDoubleWord ${TEST_SELECTOR} ${test_index}
    Execute Command    cpu PC 0x0
    Execute Command    start
    
Check Test Passed
    ${status}=    Execute Command    sysbus ReadDoubleWord ${TEST_STATUS}
    Should Be Equal    ${status}    0x00000001    Test did not pass
    ${message}=    Execute Command    sysbus ReadMemory ${TEST_MESSAGE} 256
    Log    Test message: ${message}

Execute Test Case
    [Arguments]    ${platform}    ${elf}    ${test_index}    ${test_name}
    Setup Test Platform    ${platform}    ${elf}
    Run Test    ${test_index}
    Sleep    2s
    Check Test Passed
    Log    Test ${test_name} passed
