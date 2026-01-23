# Analysis Layer (Use-Case Layer)

The **Analysis layer** is responsible for **reasoning about media streams** using the **Core domain objects**.  
It implements **use-cases / validators / analyzers** that inspect playlists, variants, and segments for correctness and consistency.

## Responsibility

The Analysis layer:

- Receives **Core domain objects**:
  - `HLSMediaPlaylist`
  - `HLSMasterPlaylist`
  - `MediaTimeline`
- Performs **validation / consistency checks**:
  - Segment timing validation
  - Playlist sequence and alignment checks
  - Variant alignment checks
- Produces **diagnostic issues**:
  - `DiagnosticIssue[]` describing errors or warnings
- Does **not** perform parsing, decoding, or I/O
- Can be fully **unit tested in isolation**

## Directory Structure

```
analysis/
├── CMakeLists.txt
├── segment_timing_validator.c
├── segment_timing_validator.h
├── variant_alignment_analyzer.c
├── variant_alignment_analyzer.h
├── playlist_consistency_checker.c
├── playlist_consistency_checker.h
└── diagnostics.h        <-- optional shared helper
```

## Design Rules

- **Depends only on Core**  
- **Pure, deterministic functions**  
- **No external I/O**  
- **Single responsibility per module**
- Validators return **diagnostic data only**, not side effects

## Example Validators

| Validator | Description |
|--|-|
| `validate_segment_timing` | Ensures segments respect target duration and cumulative timing |
| `validate_variant_alignment` | Checks that variants in a master playlist are aligned in sequence and timing |
| `validate_playlist_consistency` | Detects gaps, missing segments, or sequence inconsistencies in a playlist |

## Writing Tests

Tests for Analysis are **pure C** using the shared `test_assert.h`:

```c
#include "test_assert.h"
#include "core/hls/hls_types.h"
#include "analysis/segment_timing_validator.h"

int main(void) {
    HLSSegment segments[] = { {"s1.ts", 4.0, 1}, {"s2.ts", 6.0, 2} };
    HLSMediaPlaylist p = { segments, 2, 4.0, 1, 1 };

    DiagnosticIssue* issues;
    int count;
    validate_segment_timing(&p, &issues, &count);

    ASSERT_TRUE(count == 1);
    free(issues);
}
```

## What belongs here

✅ Use-case functions that reason about **Core objects**
✅ Deterministic diagnostic reporting
✅ Validators for playlist and media correctness

## What does NOT belong here

❌ Parsing logic (FFmpeg, network, or files)
❌ CLI or runtime orchestration
❌ Non-deterministic operations (file I/O, system calls)

## How to integrate

* Link `mediaxray_analysis` to your runtime or CLI layer
* Use validators to produce **diagnostic reports** before presenting to users
* Can be combined with **Adapters** to feed real HLS playlists

## Principle

> **Analysis layer = the reasoning brain**
> Core defines the objects. Analysis reasons about them. Adapters bring the objects to life.
