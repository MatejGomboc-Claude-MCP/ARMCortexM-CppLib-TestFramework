#include "cortexm0/systick.hpp"
#include "../common/test_framework.hpp"

volatile uint32_t systick_count = 0;

extern "C" void SysTick_Handler() {
    systick_count++;
}

void test_systick_basic() {
    TestFramework::init();
    
    // Configure SysTick for 1ms @ 8MHz
    const uint32_t ticks = 8000 - 1;
    
    CortexM0::SysTick::setReload(ticks);
    TEST_ASSERT(CortexM0::SysTick::getReload() == ticks);
    
    CortexM0::SysTick::setCurrent(0);
    CortexM0::SysTick::enableInterrupt();
    CortexM0::SysTick::enable();
    
    // Wait for a few ticks
    systick_count = 0;
    while (systick_count < 5) {
        __asm volatile("wfi");
    }
    
    CortexM0::SysTick::disable();
    
    TEST_ASSERT(systick_count >= 5);
    TestFramework::pass("SysTick basic test passed");
}

void test_systick_reload() {
    TestFramework::init();
    
    // Test various reload values
    uint32_t test_values[] = {0, 100, 1000, 0xFFFFFF};
    
    for (auto value : test_values) {
        CortexM0::SysTick::setReload(value);
        TEST_ASSERT(CortexM0::SysTick::getReload() == (value & 0xFFFFFF));
    }
    
    TestFramework::pass("SysTick reload test passed");
}
