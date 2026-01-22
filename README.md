# MediaXray

MediaXray is a **production-grade media analysis and parsing tool** built on **FFmpeg internals**, designed to provide **deep introspection of HLS playlists and media streams**.  

It is structured using a **Hexagonal (Ports & Adapters) architecture**, ensuring a **clean separation of domain logic, analysis, and infrastructure**, making it **reliable, testable, and maintainable**.

---

## Project Goals

- Analyze **HLS master and media playlists**  
- Validate **segment timing and playlist consistency**  
- Detect **variant drift and alignment issues**  
- Provide a **pure domain model** of media streams  
- Enable **frame-by-frame diagnostics**  

MediaXray is designed to start as a **CLI tool** but can grow into:
- Developer tools  
- SaaS applications  
- Internal infrastructure components  

---

## Directory Structure

```

mediaxray/
├── CMakeLists.txt           # Root build file
├── core/                    # Core Domain Layer (pure C)
├── adapters/                # Adapters for FFmpeg, I/O, parsing
├── analysis/                # Analysis layer (validators, consistency checks)
├── runtime/                 # Application orchestration
├── cli/                     # Command-line interface
└── tests/                   # Unit tests (CTest, pure C)

```

---

## Hexagonal Architecture Overview

MediaXray uses a **layered hexagonal design** with clear dependency rules:

```

CLI / API        <- User interaction
▲
│
Runtime           <- Orchestrates flow
▲
│
Analysis          <- Validators, consistency checks
▲
│
Core              <- Domain models and invariants
▲
│
Adapters          <- FFmpeg parsing, network, file I/O

```

### Layer Responsibilities

#### 1. Core (Domain Layer)
- Defines **what an HLS playlist, segment, or media frame is**  
- Implements **domain rules and invariants** (e.g., valid segment duration, monotonic sequence)  
- Defines **interfaces (ports)** for adapters to implement  
- **Does NOT** perform parsing, decoding, or I/O  
- **Testable in isolation**

#### 2. Analysis Layer
- Contains **algorithms to detect errors or inconsistencies** in media streams  
- Works **only with domain objects**  
- Produces **diagnostic issues** for reporting or logging  
- **Does NOT** know where the data came from

#### 3. Adapters (Infrastructure Layer)
- Handles **parsing**, **FFmpeg demuxing**, and **I/O**  
- Converts **raw data** into domain objects (`Core`)  
- **Implements the ports** defined by Core  
- **Replaceable** (you can swap FFmpeg with a custom parser later)  

#### 4. Runtime / Application
- **Orchestrates** the flow of the application  
- Wires **adapters → core → analysis → CLI/API**  
- **Does NOT** implement domain rules

#### 5. CLI / API
- Handles **user interaction**  
- Formats output and error messages  
- **Does NOT** contain analysis or parsing logic  

---

## Key Principles

- **Core is pure:** no FFmpeg, no I/O, no CLI.  
- **Dependencies flow upward:** Core <- Analysis <- Runtime <- CLI/API. Core <- Adapters  
- **Testability:** Unit tests are written in **pure C** using **CTest**  
- **Replaceable infrastructure:** Adapters can be swapped without changing core logic  
- **Deterministic:** Everything in core and analysis is fully deterministic  

---

## Building the Project

MediaXray uses **CMake** for building. Example:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Running Unit Tests

```bash
ctest --test-dir . --output-on-failure
```

Tests are **pure C**, using a minimal assertion framework, ensuring **core correctness without external dependencies**.

---

## Why This Design Matters

* **Reliability:** Core logic is insulated from FFmpeg quirks
* **Maintainability:** Each layer has a clear responsibility
* **Scalability:** Can extend CLI → SaaS → internal pipeline without rewriting Core
* **Testability:** Domain rules can be tested **in isolation**
* **Industry best practice:** Mirrors architecture used in mature media libraries

---

## Next Steps / TODO

* Implement **Adapters** for FFmpeg HLS parsing
* Add **analysis routines** for segment alignment and variant drift
* Expand **diagnostics reporting**
* Build **CLI commands** for exporting analysis results

---

> **Principle to remember:**
> *“Core is boring — and that’s a feature.”*
> If your domain layer is correct, the rest of the system can change freely.
