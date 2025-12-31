# MediaXray

MediaXray is a high-performance media pipeline inspection engine. It analyzes HLS/DASH streams at manifest, packet, and frame levels to detect timing issues, regressions, and structural errors, producing diffable, CI-friendly reports with actionable findings.

## Build

Linux/macOS/Windows:

```bash
conan install . --build=missing
cmake --preset conan-debug
cmake --build build --preset conan-debug
```

## Run

```bash
./build/media-xray --help
./build/media-xray --version
./build/media-xray analyze <input>
```

## Test

```bash
ctest --preset conan-debug
```
