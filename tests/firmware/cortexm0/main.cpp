#include "../common/test_framework.hpp"

// Test function declarations
void test_nvic_enable_disable();
void test_nvic_pending();
void test_nvic_priority();
void test_systick_basic();
void test_systick_reload();
void test_scb_cpuid();
void test_scb_vtor();
void test_scb_aircr();

// Simple test runner
typedef void (*TestFunc)();

struct Test {
    const char* name;
    TestFunc func;
};

const Test tests[] = {
    {"nvic_enable_disable", test_nvic_enable_disable},
    {"nvic_pending", test_nvic_pending},
    {"nvic_priority", test_nvic_priority},
    {"systick_basic", test_systick_basic},
    {"systick_reload", test_systick_reload},
    {"scb_cpuid", test_scb_cpuid},
    {"scb_vtor", test_scb_vtor},
    {"scb_aircr", test_scb_aircr},
};

int main() {
    // Get test to run from test selector (set by Renode)
    volatile uint32_t* test_selector = reinterpret_cast<volatile uint32_t*>(0x20001000);
    uint32_t test_index = *test_selector;
    
    if (test_index < sizeof(tests) / sizeof(tests[0])) {
        tests[test_index].func();
    } else {
        TestFramework::fail("Invalid test index");
    }
    
    // Infinite loop to keep the test running
    while (1) {
        __asm volatile("wfi");
    }
    
    return 0;
}
