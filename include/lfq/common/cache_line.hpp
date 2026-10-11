#pragma once

#include <cstddef>

namespace lfq {

// Size used to separate data written by different threads, to avoid false sharing.
//
// We don't use std::hardware_destructive_interference_size: it is a compile-time
// constant that can differ between compiler flags (GCC warns about this with
// -Winterference-size), and libc++ support arrived late.
//
// Apple Silicon reports 128-byte cache lines. x86-64 uses 64-byte lines, but the
// adjacent-line prefetcher pulls lines in pairs, so 128 is often better there
// too. Start with 64 on x86 and benchmark both.
#if defined(__aarch64__) && defined(__APPLE__)
inline constexpr std::size_t cache_line_size = 128;
#else
inline constexpr std::size_t cache_line_size = 64;
#endif

static_assert((cache_line_size & (cache_line_size - 1)) == 0,
              "cache_line_size must be a power of two");

}  // namespace lfq
