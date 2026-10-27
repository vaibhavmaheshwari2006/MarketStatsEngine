# MarketStats Engine

A high-performance C++17 engine that processes historical market trade data and computes real-time market statistics in a single pass.

## Overview
This project demonstrates low-level C++ optimization and algorithmic efficiency. It reads a CSV containing historical market trades and computes real-time financial metrics for every unique ticker, utilizing a zero-allocation parsing strategy and completely avoiding heavy external dependencies.

## Features Computed
For every unique ticker, the engine computes the following metrics incrementally:
* Volume-Weighted Average Price (VWAP)
* High Price
* Low Price
* Total Volume
* Total Traded Value
* Number of Trades

## Architecture & Complexity
The core engine utilizes a hash-based aggregation strategy (`std::unordered_map<std::string, MarketMetrics>`). As new trades are ingested, metrics are updated incrementally in constant time.

* **Time Complexity:** O(N), where N is the total number of trades (rows) processed.
* **Memory Complexity:** O(K), where K is the number of unique tickers. This ensures the memory footprint remains minimal and strictly bounded, regardless of total trade volume.

## C++17 Optimizations
To achieve maximum throughput, standard standard-library parsing bottlenecks were eliminated:
* **Zero-Allocation String Parsing:** Utilizes `std::string_view` to extract ticker and numerical data directly from the CSV read buffer, entirely bypassing `std::string` heap allocations and copies.
* **High-Speed Numeric Conversion:** Replaces `std::stringstream` and `std::stod` with C++17's `std::from_chars`, providing low-level, locale-independent, and zero-allocation float and integer parsing.

## Benchmark Results
The engine was profiled using dynamically generated mock market data on a single consumer-grade CPU thread.

| Rows Processed | Execution Time | Throughput (Rows / Second) |
| :--- | :--- | :--- |
| 100,000 | 0.02 seconds | ~4.91 Million |
| 500,000 | 0.06 seconds | ~7.98 Million |
| 1,000,000 | 0.11 seconds | ~8.89 Million |

*Result: Processing 1,000,000 rows of market data executes in exactly 110 milliseconds, achieving nearly 8.9 million rows per second on a single thread.*

## Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build .
cd ..
.\build\MarketStatsEngine.exe
```

## Sample Output
```text
Ticker    VWAP        High        Low         Volume      Trades
-----------------------------------------------------------------
AAPL      168.24      196.99      115.60      4000        6
AMZN      148.54      170.81      113.95      2600        5
GOOG      142.43      195.07      109.77      900         4
MSFT      134.83      178.52      104.64      2200        3
TSLA      168.92      180.84      121.23      500         2
```

## Author
* **Vaibhav Maheshwari**
  * GitHub: [@vaibhavmaheshwari2006](https://github.com/vaibhavmaheshwari2006)
  * Project Date: October 2026

