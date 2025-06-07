// Minimal startup code for Cortex-M test firmware

#include <cstdint>

extern "C" {
    // Defined by linker script
    extern uint32_t _sdata;
    extern uint32_t _edata;
    extern uint32_t _sbss;
    extern uint32_t _ebss;
    extern uint32_t _estack;
    extern uint32_t _sidata;
    
    // Main function
    int main();
    
    // Default interrupt handlers
    void Default_Handler() {
        while (1) {}
    }
    
    // Reset handler
    void Reset_Handler() {
        // Copy initialized data from flash to RAM
        uint32_t* src = &_sidata;
        uint32_t* dst = &_sdata;
        while (dst < &_edata) {
            *dst++ = *src++;
        }
        
        // Zero initialize BSS section
        dst = &_sbss;
        while (dst < &_ebss) {
            *dst++ = 0;
        }
        
        // Call main
        main();
        
        // Infinite loop if main returns
        while (1) {}
    }
    
    // Weak aliases for interrupt handlers
    void NMI_Handler() __attribute__((weak, alias("Default_Handler")));
    void HardFault_Handler() __attribute__((weak, alias("Default_Handler")));
    void SVC_Handler() __attribute__((weak, alias("Default_Handler")));
    void PendSV_Handler() __attribute__((weak, alias("Default_Handler")));
    void SysTick_Handler() __attribute__((weak, alias("Default_Handler")));
    
    // External interrupts (up to 32 for Cortex-M0)
    void IRQ0_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ1_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ2_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ3_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ4_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ5_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ6_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ7_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ8_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ9_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ10_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ11_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ12_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ13_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ14_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ15_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ16_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ17_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ18_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ19_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ20_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ21_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ22_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ23_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ24_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ25_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ26_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ27_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ28_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ29_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ30_Handler() __attribute__((weak, alias("Default_Handler")));
    void IRQ31_Handler() __attribute__((weak, alias("Default_Handler")));
}

// Vector table - must be placed at 0x00000000
__attribute__((section(".vectors"), used))
const uint32_t vector_table[] = {
    reinterpret_cast<uint32_t>(&_estack),           // Initial stack pointer
    reinterpret_cast<uint32_t>(Reset_Handler),      // Reset handler
    reinterpret_cast<uint32_t>(NMI_Handler),        // NMI handler
    reinterpret_cast<uint32_t>(HardFault_Handler),  // Hard fault handler
    0,                                               // Reserved
    0,                                               // Reserved
    0,                                               // Reserved
    0,                                               // Reserved
    0,                                               // Reserved
    0,                                               // Reserved
    0,                                               // Reserved
    reinterpret_cast<uint32_t>(SVC_Handler),        // SVC handler
    0,                                               // Reserved
    0,                                               // Reserved
    reinterpret_cast<uint32_t>(PendSV_Handler),     // PendSV handler
    reinterpret_cast<uint32_t>(SysTick_Handler),    // SysTick handler
    
    // External interrupts
    reinterpret_cast<uint32_t>(IRQ0_Handler),
    reinterpret_cast<uint32_t>(IRQ1_Handler),
    reinterpret_cast<uint32_t>(IRQ2_Handler),
    reinterpret_cast<uint32_t>(IRQ3_Handler),
    reinterpret_cast<uint32_t>(IRQ4_Handler),
    reinterpret_cast<uint32_t>(IRQ5_Handler),
    reinterpret_cast<uint32_t>(IRQ6_Handler),
    reinterpret_cast<uint32_t>(IRQ7_Handler),
    reinterpret_cast<uint32_t>(IRQ8_Handler),
    reinterpret_cast<uint32_t>(IRQ9_Handler),
    reinterpret_cast<uint32_t>(IRQ10_Handler),
    reinterpret_cast<uint32_t>(IRQ11_Handler),
    reinterpret_cast<uint32_t>(IRQ12_Handler),
    reinterpret_cast<uint32_t>(IRQ13_Handler),
    reinterpret_cast<uint32_t>(IRQ14_Handler),
    reinterpret_cast<uint32_t>(IRQ15_Handler),
    reinterpret_cast<uint32_t>(IRQ16_Handler),
    reinterpret_cast<uint32_t>(IRQ17_Handler),
    reinterpret_cast<uint32_t>(IRQ18_Handler),
    reinterpret_cast<uint32_t>(IRQ19_Handler),
    reinterpret_cast<uint32_t>(IRQ20_Handler),
    reinterpret_cast<uint32_t>(IRQ21_Handler),
    reinterpret_cast<uint32_t>(IRQ22_Handler),
    reinterpret_cast<uint32_t>(IRQ23_Handler),
    reinterpret_cast<uint32_t>(IRQ24_Handler),
    reinterpret_cast<uint32_t>(IRQ25_Handler),
    reinterpret_cast<uint32_t>(IRQ26_Handler),
    reinterpret_cast<uint32_t>(IRQ27_Handler),
    reinterpret_cast<uint32_t>(IRQ28_Handler),
    reinterpret_cast<uint32_t>(IRQ29_Handler),
    reinterpret_cast<uint32_t>(IRQ30_Handler),
    reinterpret_cast<uint32_t>(IRQ31_Handler),
};
