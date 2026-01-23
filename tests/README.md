# Tests

This directory contains **unit tests** for MediaXray.

All tests are written in **pure C** and executed using **CTest** via CMake.

The goal of this test suite is to validate **domain correctness** and **invariants** without relying on external libraries, FFmpeg, or runtime infrastructure.

---

## Philosophy

MediaXray is a **C-first, systems-level project**.  
Tests follow the same principles as the production code:

- Same language (C)
- Same compiler
- Same ABI
- Minimal dependencies
- Deterministic execution

Each test is a small, standalone executable that returns:
- `0` on success
- non-zero on failure

CTest is used only as a **test runner and reporter**.

---

## Directory Structure

tests/
├── CMakeLists.txt
├── test_assert.h
└── core/
├── test_hls_invariants.c
└── ...


### `test_assert.h`
A minimal assertion helper used by all tests.

- No framework
- No global state
- Immediate failure with file/line reporting

---

## What belongs here

✅ Unit tests for:
- Core domain invariants
- Analysis algorithms
- Adapters (with controlled inputs)

✅ Deterministic tests that:
- Do not require network access
- Do not require real media files (unless explicitly testing adapters)
- Do not depend on FFmpeg unless explicitly intended

---

## What must NOT go here

❌ Integration tests involving real networks  
❌ Long-running or flaky tests  
❌ Tests requiring environment configuration  
❌ Performance benchmarks  
❌ Production logging or CLI code  

If a test requires complex setup, it likely belongs in a **higher-level test suite**, not here.

---

## Adding a New Test

1. Create a new `.c` file under the appropriate subdirectory
2. Write a `main()` function using `ASSERT_*` macros
3. Add the executable to `tests/CMakeLists.txt`
4. Register it with `add_test()`

Example:

```cmake
add_executable(test_example example.c)
target_link_libraries(test_example mediaxray_core)
add_test(NAME example COMMAND test_example)
```

## Running Tests

From the project root:

```shell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Design Principle

> Tests should resemble production code, not a different universe.

If a test cannot be understood without knowing the entire system, it is too complex.

## Why This Matters

This testing approach ensures:

  - Fast feedback
  - High confidence in domain correctness
  - Long-term maintainability
  - Easy debugging with standard tools (gdb, valgrind)
  - A stable core + reliable tests = a scalable system.
