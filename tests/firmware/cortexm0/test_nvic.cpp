#include "cortexm0/nvic.hpp"
#include "../common/test_framework.hpp"

void test_nvic_enable_disable() {
    TestFramework::init();
    
    // Test enabling IRQ 0
    CortexM0::Nvic::enableIrq(0);
    TEST_ASSERT(CortexM0::Nvic::isIrqEnabled(0));
    
    // Test disabling IRQ 0
    CortexM0::Nvic::disableIrq(0);
    TEST_ASSERT(!CortexM0::Nvic::isIrqEnabled(0));
    
    // Test multiple IRQs
    for (uint8_t i = 0; i < 32; i++) {
        CortexM0::Nvic::enableIrq(i);
        TEST_ASSERT(CortexM0::Nvic::isIrqEnabled(i));
    }
    
    TestFramework::pass("NVIC enable/disable test passed");
}

void test_nvic_pending() {
    TestFramework::init();
    
    // Clear any pending interrupts
    for (uint8_t i = 0; i < 32; i++) {
        CortexM0::Nvic::clearPendingIrq(i);
    }
    
    // Test setting pending
    CortexM0::Nvic::setPendingIrq(5);
    TEST_ASSERT(CortexM0::Nvic::isIrqPending(5));
    
    // Test clearing pending
    CortexM0::Nvic::clearPendingIrq(5);
    TEST_ASSERT(!CortexM0::Nvic::isIrqPending(5));
    
    TestFramework::pass("NVIC pending test passed");
}

void test_nvic_priority() {
    TestFramework::init();
    
    // Test setting and getting priority
    for (uint8_t irq = 0; irq < 32; irq++) {
        uint8_t priority = (irq * 0x40) & 0xC0; // Cortex-M0 only uses top 2 bits
        CortexM0::Nvic::setIrqPriority(irq, priority);
        TEST_ASSERT(CortexM0::Nvic::getIrqPriority(irq) == priority);
    }
    
    TestFramework::pass("NVIC priority test passed");
}
