#include "MarketStatsEngine.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

void generateMockData(int rows, const std::vector<std::string>& tickers, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "Timestamp,Ticker,Price,Volume\n"; // Header
    
    std::mt19937 engine(42);
    std::uniform_int_distribution<int> ticker_dist(0, tickers.size() - 1);
    std::uniform_real_distribution<double> price_dist(100.0, 200.0);
    std::uniform_int_distribution<int> volume_dist(1, 10);

    for (int i = 0; i < rows; ++i) {
        file << "09:30:00," 
             << tickers[ticker_dist(engine)] << "," 
             << price_dist(engine) << "," 
             << (volume_dist(engine) * 100) << "\n";
    }
}

void runBenchmark(int rows, const std::vector<std::string>& tickers) {
    std::string filename = "data/benchmark_" + std::to_string(rows) + ".csv";
    std::cout << "Generating " << rows << " rows of mock data...\n";
    generateMockData(rows, tickers, filename);

    MarketStatsEngine engine;

    std::cout << "Processing " << rows << " rows...\n";
    auto start = std::chrono::steady_clock::now();
    engine.processFile(filename);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    double rows_per_sec = rows / elapsed.count();

    std::cout << "--- Benchmark Results ---\n";
    std::cout << "Rows Processed: " << rows << "\n";
    std::cout << "Execution Time: " << elapsed.count() << " seconds\n";
    std::cout << "Rows / Second : " << rows_per_sec << "\n";
    std::cout << "-------------------------\n\n";
}

int main() {
    std::vector<std::string> tickers = {"AAPL", "GOOG", "MSFT", "AMZN", "TSLA"};
    
    std::cout << "Testing with small sample data:\n\n";
    std::string sample_file = "data/sample_market_data.csv";
    generateMockData(20, tickers, sample_file);
    
    MarketStatsEngine engine;
    engine.processFile(sample_file);
    engine.printResults();
    std::cout << "\n";

    std::cout << "Starting Benchmarks...\n\n";
    runBenchmark(100000, tickers);
    runBenchmark(500000, tickers);
    runBenchmark(1000000, tickers);

    return 0;
}
