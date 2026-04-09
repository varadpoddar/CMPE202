#ifndef FREQUENCY_STORE_H
#define FREQUENCY_STORE_H

#include <map>
#include <string>

class FrequencyStore {
public:
    explicit FrequencyStore(std::string filePath = "frequencies.dat");

    int getFrequency(const std::string& key) const;
    void increment(const std::string& key);

    bool load();
    bool save() const;

private:
    std::string filePath;
    std::map<std::string, int> frequencies;
};

#endif