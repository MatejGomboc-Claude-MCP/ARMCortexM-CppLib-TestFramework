#!/bin/bash
# Run all test variants

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BUILD_DIR="${SCRIPT_DIR}/../../build"
ROBOT_DIR="${SCRIPT_DIR}/../robot"

echo "Running ARM Cortex-M Library Tests with Renode"
echo "============================================="

# Run tests for each variant
for variant in m0 m0plus m1 m3; do
    echo ""
    echo "Testing Cortex-${variant^^}..."
    echo "-------------------------"
    
    # Check if firmware exists
    if [ ! -f "${BUILD_DIR}/tests/test_firmware_cortex${variant}.elf" ]; then
        echo "Error: Test firmware for Cortex-${variant^^} not found!"
        echo "Skipping..."
        continue
    fi
    
    # Run Robot Framework tests
    cd "${ROBOT_DIR}"
    robot --variable VARIANT:${variant} \
          --outputdir "${BUILD_DIR}/robot_results_${variant}" \
          "cortex${variant}_tests.robot" || true
done

echo ""
echo "All tests completed!"
echo "Results available in: ${BUILD_DIR}/robot_results_*/"
