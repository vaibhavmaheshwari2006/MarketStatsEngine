#pragma once

#include <string>
#include <unordered_map>
#include <string_view>

struct MarketMetrics {
    double tradedValue = 0.0;
    long long volume = 0;
    double high = -1.0;
    double low = -1.0;
    int trades = 0;
};

class MarketStatsEngine {
private:
    std::unordered_map<std::string, MarketMetrics> metrics_;

public:
    // Process a single row from the CSV
    void processRow(std::string_view row);

    // Process an entire CSV file
    void processFile(const std::string& filepath);

    // Print the results in a formatted table
    void printResults() const;
    
    // Clear the metrics for benchmarking multiple runs
    void clear();
};
