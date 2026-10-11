// Placeholder benchmark to verify the Google Benchmark setup.
// Replaced by the real throughput/latency benchmarks in M3.

#include <benchmark/benchmark.h>

#include <atomic>

namespace {

void BM_AtomicIncrementRelaxed(benchmark::State& state) {
    std::atomic<long> counter{0};
    for (auto _ : state) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
    benchmark::DoNotOptimize(counter.load());
}
BENCHMARK(BM_AtomicIncrementRelaxed);

void BM_AtomicIncrementSeqCst(benchmark::State& state) {
    std::atomic<long> counter{0};
    for (auto _ : state) {
        counter.fetch_add(1, std::memory_order_seq_cst);
    }
    benchmark::DoNotOptimize(counter.load());
}
BENCHMARK(BM_AtomicIncrementSeqCst);

}  // namespace
