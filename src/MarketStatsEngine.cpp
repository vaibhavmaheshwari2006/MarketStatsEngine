// MarketStatsEngine
// Author: Vaibhav Maheshwari (vaibhavmaheshwari2006)
// Date: October 2026

#include "MarketStatsEngine.h"
#include <fstream>
#include <iostream>
#include <charconv>
#include <iomanip>
#include <algorithm>
#include <system_error>

void MarketStatsEngine::processRow(std::string_view row) {
    // Expected format: Timestamp,Ticker,Price,Volume
    // Example: 09:30:01,AAPL,184.52,100

    size_t pos1 = row.find(',');
    if (pos1 == std::string_view::npos) return;

    size_t pos2 = row.find(',', pos1 + 1);
    if (pos2 == std::string_view::npos) return;

    size_t pos3 = row.find(',', pos2 + 1);
    if (pos3 == std::string_view::npos) return;

    std::string_view ticker_view = row.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string_view price_view = row.substr(pos2 + 1, pos3 - pos2 - 1);
    std::string_view volume_view = row.substr(pos3 + 1);

    double price = 0.0;
    auto price_res = std::from_chars(price_view.data(), price_view.data() + price_view.size(), price);
    if (price_res.ec != std::errc()) return; // skip malformed

    long long volume = 0;
    auto vol_res = std::from_chars(volume_view.data(), volume_view.data() + volume_view.size(), volume);
    if (vol_res.ec != std::errc()) return; // skip malformed

    // Update metrics
    std::string ticker(ticker_view); // Allocation required for unordered_map key
    auto& metric = metrics_[ticker];

    metric.tradedValue += price * volume;
    metric.volume += volume;
    
    if (metric.trades == 0) {
        metric.high = price;
        metric.low = price;
    } else {
        metric.high = std::max(metric.high, price);
        metric.low = std::min(metric.low, price);
    }
    metric.trades++;
}

void MarketStatsEngine::processFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << "\n";
        return;
    }

    std::string line;
    // Skip the header to prevent from_chars from failing
    if (std::getline(file, line)) {
        // Skipped header
    }

    while (std::getline(file, line)) {
        if (!line.empty()) {
            processRow(line);
        }
    }
}

void MarketStatsEngine::printResults() const {
    std::cout << std::left << std::setw(10) << "Ticker" 
              << std::setw(12) << "VWAP" 
              << std::setw(12) << "High" 
              << std::setw(12) << "Low" 
              << std::setw(12) << "Volume" 
              << "Trades\n";
    std::cout << "-----------------------------------------------------------------\n";

    for (const auto& [ticker, metric] : metrics_) {
        double vwap = metric.volume > 0 ? (metric.tradedValue / metric.volume) : 0.0;
        std::cout << std::left << std::setw(10) << ticker 
                  << std::fixed << std::setprecision(2)
                  << std::setw(12) << vwap 
                  << std::setw(12) << metric.high 
                  << std::setw(12) << metric.low 
                  << std::setw(12) << metric.volume 
                  << metric.trades << "\n";
    }
}

void MarketStatsEngine::clear() {
    metrics_.clear();
}
