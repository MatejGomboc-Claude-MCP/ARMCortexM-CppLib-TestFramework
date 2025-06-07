#!/bin/bash
# Run a single test variant

set -e

if [ $# -ne 1 ]; then
    echo "Usage: $0 <variant>"
    echo "  variant: m0, m0plus, m1, or m3"
    exit 1
fi

VARIANT=$1
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROBOT_DIR="${SCRIPT_DIR}/../robot"
BUILD_DIR="${SCRIPT_DIR}/../../build"

# Check if test firmware exists
if [ ! -f "${BUILD_DIR}/tests/test_firmware_cortex${VARIANT}.elf" ]; then
    echo "Error: Test firmware for Cortex-${VARIANT^^} not found!"
    echo "Please build the firmware first."
    exit 1
fi

# Run Robot Framework tests
cd "${ROBOT_DIR}"
robot --variable VARIANT:${VARIANT} \
      --outputdir "${BUILD_DIR}/robot_results_${VARIANT}" \
      "cortex${VARIANT}_tests.robot"
