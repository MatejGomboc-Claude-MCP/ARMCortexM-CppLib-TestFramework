#pragma once

#include <cstdint>
#include <cstring>

// Simple test framework for embedded systems
class TestFramework {
private:
    static constexpr uint32_t TEST_RESULT_ADDR = 0x20000000;
    static constexpr uint32_t TEST_STATUS_ADDR = 0x20000004;
    static constexpr uint32_t TEST_MESSAGE_ADDR = 0x20000008;
    static constexpr uint32_t MAX_MESSAGE_LEN = 256;

public:
    enum Status : uint32_t {
        RUNNING = 0x00000000,
        PASSED = 0x00000001,
        FAILED = 0x00000002,
        ERROR = 0x00000003
    };

    static void init() {
        setStatus(RUNNING);
        setResult(0);
    }

    static void setResult(uint32_t result) {
        *reinterpret_cast<volatile uint32_t*>(TEST_RESULT_ADDR) = result;
    }

    static void setStatus(Status status) {
        *reinterpret_cast<volatile uint32_t*>(TEST_STATUS_ADDR) = status;
    }

    static void setMessage(const char* msg) {
        volatile char* msgAddr = reinterpret_cast<volatile char*>(TEST_MESSAGE_ADDR);
        size_t len = strlen(msg);
        if (len > MAX_MESSAGE_LEN - 1) {
            len = MAX_MESSAGE_LEN - 1;
        }
        for (size_t i = 0; i < len; i++) {
            msgAddr[i] = msg[i];
        }
        msgAddr[len] = '\0';
    }

    static void pass(const char* msg = "") {
        setMessage(msg);
        setStatus(PASSED);
    }

    static void fail(const char* msg = "") {
        setMessage(msg);
        setStatus(FAILED);
    }

    static void assert(bool condition, const char* msg = "Assertion failed") {
        if (!condition) {
            fail(msg);
            while (1) {} // Halt on failure
        }
    }
};

#define TEST_ASSERT(condition) TestFramework::assert(condition, #condition " failed at " __FILE__ ":" __STR__(__LINE__))
#define __STR__(x) #x
