#!/usr/bin/env python3
# Advanced test runner using Renode's Python API

import os
import sys
import time
import subprocess
from dataclasses import dataclass
from typing import List, Dict, Any
import json

@dataclass
class TestResult:
    name: str
    variant: str
    passed: bool
    duration: float
    message: str = ""
    
class RenodeTestRunner:
    def __init__(self, renode_path: str = "renode"):
        self.renode_path = renode_path
        self.results: List[TestResult] = []
        
    def create_renode_script(self, platform: str, elf: str, test_index: int) -> str:
        """Create a Renode script for running a specific test"""
        return f"""
# Create machine
mach create "test_machine"
machine LoadPlatformDescription @{platform}
sysbus LoadELF @{elf}

# Set test selector
sysbus WriteDoubleWord 0x20001000 {test_index}

# Create test monitor
machine CreateNetworkServer "monitor" 3456

# Add hooks for test monitoring
sysbus AddWatchpointHook 0x20000004 DoubleWord Read "python monitor_test_status.py"

# Start simulation
start

# Run for maximum 10 seconds
machine SetRealTimeModeLimitThreshold 10
"""

    def run_test(self, variant: str, test_name: str, test_index: int) -> TestResult:
        """Run a single test case"""
        start_time = time.time()
        
        platform_file = f"tests/platforms/cortex{variant}.repl"
        elf_file = f"build/tests/test_firmware_cortex{variant}.elf"
        
        # Create Renode script
        script_content = self.create_renode_script(platform_file, elf_file, test_index)
        script_path = f"/tmp/test_{variant}_{test_name}.resc"
        
        with open(script_path, 'w') as f:
            f.write(script_content)
        
        try:
            # Run Renode
            cmd = [self.renode_path, "--console", "--disable-xwt", "--execute", script_path]
            process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            
            # Monitor test execution
            timeout = 10  # seconds
            test_passed = False
            test_message = ""
            
            # Poll for results
            for _ in range(timeout * 10):  # Check every 100ms
                # In real implementation, you would monitor the memory locations
                # through Renode's network server or analyze output
                time.sleep(0.1)
                
                if process.poll() is not None:
                    break
            
            # Get results (simplified - in real implementation, read from memory)
            stdout, stderr = process.communicate(timeout=1)
            
            # Parse results
            if b"Test passed" in stdout:
                test_passed = True
                test_message = "Test completed successfully"
            else:
                test_message = stderr.decode('utf-8', errors='ignore')
            
        except Exception as e:
            test_passed = False
            test_message = str(e)
        finally:
            # Cleanup
            if process.poll() is None:
                process.terminate()
            os.unlink(script_path)
        
        duration = time.time() - start_time
        
        return TestResult(
            name=test_name,
            variant=variant,
            passed=test_passed,
            duration=duration,
            message=test_message
        )
    
    def run_all_tests(self, test_config: Dict[str, Any]) -> None:
        """Run all tests defined in configuration"""
        for variant in test_config['variants']:
            print(f"\nTesting Cortex-{variant.upper()}...")
            
            for idx, test in enumerate(test_config['tests']):
                print(f"  Running {test['name']}...", end='', flush=True)
                
                result = self.run_test(variant, test['name'], idx)
                self.results.append(result)
                
                if result.passed:
                    print(f" PASSED ({result.duration:.2f}s)")
                else:
                    print(f" FAILED: {result.message}")
    
    def generate_report(self, output_file: str = "test_report.json") -> None:
        """Generate test report"""
        report = {
            'total_tests': len(self.results),
            'passed': sum(1 for r in self.results if r.passed),
            'failed': sum(1 for r in self.results if not r.passed),
            'results': [
                {
                    'name': r.name,
                    'variant': r.variant,
                    'passed': r.passed,
                    'duration': r.duration,
                    'message': r.message
                }
                for r in self.results
            ]
        }
        
        with open(output_file, 'w') as f:
            json.dump(report, f, indent=2)
        
        # Print summary
        print(f"\n{'='*60}")
        print(f"Test Summary:")
        print(f"  Total:  {report['total_tests']}")
        print(f"  Passed: {report['passed']}")
        print(f"  Failed: {report['failed']}")
        print(f"  Success Rate: {report['passed']/report['total_tests']*100:.1f}%")
        print(f"{'='*60}")

def main():
    # Test configuration
    test_config = {
        'variants': ['m0', 'm0plus', 'm1', 'm3'],
        'tests': [
            {'name': 'nvic_enable_disable', 'description': 'Test NVIC enable/disable'},
            {'name': 'nvic_pending', 'description': 'Test NVIC pending interrupts'},
            {'name': 'nvic_priority', 'description': 'Test NVIC priority'},
            {'name': 'systick_basic', 'description': 'Test SysTick timer'},
            {'name': 'scb_reset', 'description': 'Test system reset'},
            {'name': 'special_regs', 'description': 'Test special registers'},
        ]
    }
    
    # Run tests
    runner = RenodeTestRunner()
    runner.run_all_tests(test_config)
    runner.generate_report()
    
    # Exit with appropriate code
    failed_count = sum(1 for r in runner.results if not r.passed)
    sys.exit(failed_count)

if __name__ == "__main__":
    main()
