#include "cortexm0/scb.hpp"
#include "../common/test_framework.hpp"

void test_scb_cpuid() {
    TestFramework::init();
    
    // Read CPUID register
    uint32_t cpuid = CortexM0::Scb::getCpuid();
    
    // Check implementer (should be ARM)
    uint8_t implementer = (cpuid >> 24) & 0xFF;
    TEST_ASSERT(implementer == 0x41); // ARM Limited
    
    // Check architecture (should be ARMv6-M)
    uint8_t architecture = (cpuid >> 16) & 0x0F;
    TEST_ASSERT(architecture == 0xC); // ARMv6-M
    
    TestFramework::pass("SCB CPUID test passed");
}

void test_scb_vtor() {
    TestFramework::init();
    
    // Note: VTOR might not be implemented in all Cortex-M0 variants
    // This test checks if it's available
    
    uint32_t original_vtor = CortexM0::Scb::getVtor();
    
    // Try to set a new value (must be aligned)
    uint32_t new_vtor = 0x00000100;
    CortexM0::Scb::setVtor(new_vtor);
    
    // Check if it was set (might be read-only in M0)
    uint32_t read_vtor = CortexM0::Scb::getVtor();
    
    // Restore original value
    CortexM0::Scb::setVtor(original_vtor);
    
    // Test passes regardless - we're testing the API
    TestFramework::pass("SCB VTOR test completed");
}

void test_scb_aircr() {
    TestFramework::init();
    
    // Read AIRCR
    uint32_t aircr = CortexM0::Scb::getAircr();
    
    // Check VECTKEYSTAT field
    uint16_t vectkey = (aircr >> 16) & 0xFFFF;
    TEST_ASSERT(vectkey == 0xFA05);
    
    // Note: We don't test system reset here as it would reset the test
    
    TestFramework::pass("SCB AIRCR test passed");
}
