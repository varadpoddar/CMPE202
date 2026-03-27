#include "FrequencyStore.h"

#include <fstream>
#include <sstream>

FrequencyStore::FrequencyStore(std::string filePathValue) : filePath(std::move(filePathValue)) {}

int FrequencyStore::getFrequency(const std::string& key) const {
    auto found = frequencies.find(key);
    if (found == frequencies.end()) {
        return 0;
    }

    return found->second;
}

void FrequencyStore::increment(const std::string& key) {
    ++frequencies[key];
}

bool FrequencyStore::load() {
    frequencies.clear();

    std::ifstream input(filePath);
    if (!input.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream parser(line);
        std::string key;
        int count = 0;

        if (!(parser >> key >> count)) {
            continue;
        }

        if (count > 0) {
            frequencies[key] = count;
        }
    }

    return true;
}

bool FrequencyStore::save() const {
    std::ofstream output(filePath, std::ios::trunc);
    if (!output.is_open()) {
        return false;
    }

    for (const auto& entry : frequencies) {
        output << entry.first << ' ' << entry.second << '\n';
    }

    return true;
}