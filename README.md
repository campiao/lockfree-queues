# lockfree-queues

[![CI](https://github.com/campiao/lockfree-queues/actions/workflows/ci.yml/badge.svg)](https://github.com/campiao/lockfree-queues/actions/workflows/ci.yml)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

Header-only, lock-free **SPSC** and **MPMC** queues and a **low-latency async logger** in C++23, built step by step and benchmarked at each step.

The aim is to understand what makes inter-thread communication fast: memory ordering, cache coherence, false sharing, and avoiding allocations and syscalls on the hot path.

> **Status:** work in progress. The build, test and CI setup is done. The queues are next. See [Roadmap](#roadmap).

## Components

| Component | Description | Status |
|---|---|---|
| SPSC queue | Bounded ring buffer, built in versions from a mutex baseline to cached head/tail indices | Planned |
| MPMC queue | Bounded queue with a sequence number per slot (Vyukov design) | Planned |
| Async logger | The hot path stores raw arguments and a TSC timestamp. Formatting and I/O run on a background thread | Planned |

## Design goals

- **No allocation, locks, exceptions or syscalls on the hot path**
- **Correctness first:** every test runs under ThreadSanitizer and AddressSanitizer + UBSan in CI
- **Meatrics:** latency is reported as percentiles (p50 / p99 / p99.9) and compared with established libraries

## Results

Coming soon. Throughput and latency charts, plus the step-by-step SPSC optimization story, will go here.

## Building

Requires CMake ≥ 3.25, Ninja, and a C++23 compiler (GCC ≥ 14 or Clang ≥ 18).

```sh
cmake --preset debug             # or: release, tsan, asan
cmake --build --preset debug
ctest --preset debug
```

| Preset | Purpose |
|---|---|
| `debug` | Development build |
| `release` | Optimized with `-march=native`, used for benchmarks |
| `tsan` | ThreadSanitizer |
| `asan` | AddressSanitizer + UndefinedBehaviorSanitizer |

To pick a compiler, pass `-DCMAKE_CXX_COMPILER=...` or add your own presets in a `CMakeUserPresets.json` (gitignored).

### Using it in another project

The library is header-only and has no dependencies:

```cmake
include(FetchContent)
FetchContent_Declare(lfq
    GIT_REPOSITORY https://github.com/campiao/lockfree-queues.git
    GIT_TAG main)
FetchContent_MakeAvailable(lfq)

target_link_libraries(your_target PRIVATE lfq::lfq)
```

Tests and benchmarks are only built when this is the top-level project.

## Project layout

```
include/lfq/   header-only library
tests/         unit and stress tests (GoogleTest)
bench/         benchmarks (Google Benchmark + custom latency harnesses)
scripts/       benchmark runner and plotting
results/       benchmark charts
```

## Roadmap

- [x] M1: Project skeleton (CMake presets, sanitizers, CI on GCC and Clang)
- [ ] M2: SPSC v0–v2 (mutex → seq_cst → acquire/release)
- [ ] M3: Benchmark harness (throughput, ping-pong latency, thread pinning)
- [ ] M4: SPSC v3–v4 (cache-line padding, cached indices) with `perf` evidence
- [ ] M5: Comparisons with Boost, rigtorp and moodycamel
- [ ] M6: MPMC queue
- [ ] M7: Async logger
- [ ] M8: Results write-up

## License

[MIT](LICENSE)
