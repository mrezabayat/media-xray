# Core Domain Layer

This directory contains the **Core (Domain) Layer** of MediaXray.

The core defines **what the media world is**, not how it is read, decoded, or displayed.

---

## Responsibility

The Core layer is responsible for:

- Defining **domain models**
  - HLS playlists, variants, segments
  - Media frames, streams, timelines
- Defining **domain invariants**
  - What constitutes a valid playlist
  - What constitutes valid timing
- Defining **ports (interfaces)**
  - What capabilities the domain expects from the outside world

The Core layer answers questions like:

> “If a playlist exists in memory, what rules must it obey?”

---

## What belongs here

✅ Plain data structures  
✅ Domain rules and validation  
✅ Interfaces (ports)  
✅ Types shared across the system  

Examples:
- `HLSMediaPlaylist`
- `HLSSegment`
- Timeline consistency rules
- Parser interfaces (no implementation)

---

## What must NOT go here

❌ Parsing logic  
❌ FFmpeg headers or APIs  
❌ File or network I/O  
❌ CLI or UI code  
❌ Logging frameworks  
❌ JSON, XML, or text handling  
❌ Business workflows  

If it depends on **how** data is obtained, it does not belong here.

---

## Design rules

- No external dependencies
- Must compile as a standalone library
- Must be deterministic and testable
- No knowledge of adapters or runtime
- No global state

---

## Dependency direction

Core ← Analysis ← Runtime ← CLI
Core ← Adapters


The Core **never** depends on other layers.

---

## Why this layer exists

Keeping the Core pure allows:

- Fast, reliable unit testing
- Replaceable infrastructure (FFmpeg, custom parsers, mocks)
- Clear reasoning about correctness
- Long-term stability as the system grows

If the Core is correct, the rest of the system can change freely.

---

## Guiding principle

> **The Core is boring — and that’s a feature.**
