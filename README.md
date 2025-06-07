# ARM Cortex-M C++ Library Test Framework

Comprehensive testing framework for [ARM Cortex-M C++ Library](https://github.com/MatejGomboc/ARMCortexM-CppLib) using Renode emulator and Robot Framework for automated testing.

## Features

- 🚀 **Hardware-in-the-loop simulation** using Renode
- 🤖 **Automated testing** with Robot Framework
- 📊 **Performance benchmarking** capabilities
- 🔄 **CI/CD ready** with GitHub Actions
- 🎯 **Support for all Cortex-M variants** (M0, M0+, M1, M3)
- 📈 **Code coverage** analysis support
- 🧪 **Unit and integration tests**

## Repository Structure

```
ARMCortexM-CppLib-TestFramework/
├── lib/                    # Submodule: ARM Cortex-M C++ Library
├── tests/
│   ├── firmware/          # Test firmware source code
│   │   ├── cortexm0/     # Cortex-M0 specific tests
│   │   ├── cortexm0plus/ # Cortex-M0+ specific tests
│   │   ├── cortexm1/     # Cortex-M1 specific tests
│   │   ├── cortexm3/     # Cortex-M3 specific tests
│   │   └── common/       # Common test framework
│   ├── platforms/        # Renode platform descriptions
│   ├── robot/           # Robot Framework test scripts
│   └── scripts/         # Helper scripts
├── cmake/               # CMake toolchain files
├── .github/
│   └── workflows/       # GitHub Actions CI/CD
└── docs/               # Additional documentation
```

## Quick Start

### Prerequisites

1. **ARM GCC Toolchain**:
   ```bash
   sudo apt-get install gcc-arm-none-eabi
   ```

2. **Renode**:
   ```bash
   wget https://github.com/renode/renode/releases/latest/download/renode-1.14.0.linux-portable.tar.gz
   tar -xzf renode-*.tar.gz
   export PATH=$PATH:$(pwd)/renode_portable
   ```

3. **Robot Framework**:
   ```bash
   pip install robotframework robotframework-renodekeywords
   ```

### Clone and Build

```bash
# Clone with submodules
git clone --recursive https://github.com/MatejGomboc-Claude-MCP/ARMCortexM-CppLib-TestFramework.git
cd ARMCortexM-CppLib-TestFramework

# Configure and build
cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
cmake --build build

# Run tests
cd build && ctest
```

### Running Specific Tests

```bash
# Test specific Cortex-M variant
make test-m0      # Test Cortex-M0
make test-m0plus  # Test Cortex-M0+
make test-m1      # Test Cortex-M1
make test-m3      # Test Cortex-M3

# Run performance benchmarks
make benchmark

# Generate test report
make report
```

## Test Categories

### 1. Unit Tests
- **NVIC**: Interrupt controller functionality
- **SysTick**: System timer operations
- **SCB**: System control block features
- **Special Registers**: PRIMASK, CONTROL, etc.
- **MPU**: Memory protection unit (M0+, M3)

### 2. Integration Tests
- Interrupt handling chains
- System reset behavior
- Exception priorities
- Power management

### 3. Performance Tests
- Operation latency measurements
- Memory barrier overhead
- Interrupt response time
- Context switch performance

## CI/CD Integration

This repository includes GitHub Actions workflows that:
- Build test firmware for all variants
- Run automated tests in Renode
- Generate test reports
- Upload artifacts
- Fail on test failures

## Writing New Tests

1. Create test file in `tests/firmware/cortex<variant>/`:
```cpp
#include "../common/test_framework.hpp"

void test_my_feature() {
    TestFramework::init();
    
    // Your test code here
    TEST_ASSERT(condition);
    
    TestFramework::pass("Test passed!");
}
```

2. Add Robot Framework test case:
```robot
*** Test Cases ***
Test My Feature
    [Documentation]    Test description
    Execute Test Case    ${PLATFORM}    ${ELF_FILE}    0    my_feature
```

3. Update test runner in `main.cpp`

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-test`)
3. Commit your changes (`git commit -m 'Add amazing test'`)
4. Push to the branch (`git push origin feature/amazing-test`)
5. Open a Pull Request

## License

This test framework is licensed under the Apache License 2.0, same as the ARM Cortex-M C++ Library.

## Acknowledgments

- [Renode](https://renode.io/) for the amazing emulation platform
- [Robot Framework](https://robotframework.org/) for test automation
- ARM for the Cortex-M architecture documentation
