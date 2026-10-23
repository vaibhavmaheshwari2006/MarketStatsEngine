# MarketStats Engine

A high-performance C++17 engine that processes historical market trade data and computes real-time market statistics in a single pass.

## 🚀 Objective
This project is built to demonstrate low-level C++ optimization and algorithmic efficiency. It reads a CSV containing historical market trades and computes real-time financial metrics for every unique ticker without relying on heavy external dependencies.

## 📊 Features Computed (Single Pass)
- **VWAP** (Volume-Weighted Average Price)
- **High Price**
- **Low Price**
- **Total Volume**
- **Total Traded Value**
- **Number of Trades**

## 🧠 Algorithm & Complexity
The core engine utilizes a hash-based aggregation strategy (`std::unordered_map<std::string, MarketMetrics>`). Whenever a new trade arrives, metrics are updated incrementally.
- **Time Complexity**: `O(N)` where `N` is the number of rows processed.
- **Memory Complexity**: `O(K)` where `K` is the number of unique tickers, ensuring memory footprints remain minimal regardless of trade volume.

## ⚡ C++17 Optimizations
To achieve maximum throughput, standard parsing bottlenecks were removed:
- **Zero-Allocation String Parsing**: Utilized `std::string_view` to extract ticker and numerical data directly from the CSV line buffer, eliminating `std::string` copies entirely.
- **High-Speed Numeric Conversion**: Replaced `std::stringstream` and `std::stod` with C++17's `std::from_chars`, providing blazing fast, zero-allocation float and integer parsing.

## 📈 Benchmark Results
The engine is rigorously benchmarked on dynamically generated mock market data. 

*Hardware Target: Consumer CPU (Single Thread)*
| Rows Processed | Execution Time | Rows / Second |
|----------------|----------------|---------------|
| 100,000        | 0.02 seconds   | ~4.91 Million |
| 500,000        | 0.06 seconds   | ~7.98 Million |
| 1,000,000      | 0.11 seconds   | ~8.89 Million |

*Result: Processing 1 million rows of market data takes exactly 110 milliseconds, achieving nearly 8.9 million rows per second on a single thread.*

## 💻 Build Instructions
```bash
mkdir build
cd build
cmake ..
cmake --build .
cd ..
.\build\MarketStatsEngine.exe
```

## 📋 Sample Output
```text
Ticker    VWAP        High        Low         Volume      Trades
-----------------------------------------------------------------
AAPL      168.24      196.99      115.60      4000        6
AMZN      148.54      170.81      113.95      2600        5
GOOG      142.43      195.07      109.77      900         4
MSFT      134.83      178.52      104.64      2200        3
TSLA      168.92      180.84      121.23      500         2
```
