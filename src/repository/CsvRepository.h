#ifndef BASECSVREPO_H
#define BASECSVREPO_H

#include "IRepository.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>


template <typename T>
class CsvRepository : public IRepository<T> {
protected:
    std::string m_filepath;
    bool loadDataFromFile(const std::string& path) override {
        std::ifstream file(path);
        if (file.is_open()) {
            std::string line;
            int lineCount = 0;
            while (std::getline(file, line)) {
                if(lineCount == 0){
                    lineCount++; // Skip header line
                    continue; // Skip the first line if it's a header
                }
                std::istringstream ss(line);

                T obj;
                obj.fromCsv(ss.str());
                m_data.push_back(obj);
            }
            file.close();
        } else {
            std::cerr << "Could not open file: " << path << std::endl;
            return false;
        }
        return true;
    }

public:
    CsvRepository(const std::string& path) : IRepository<T>() {
        m_filepath = path;
        loadDataFromFile(m_filepath);
    }
    
    bool saveToFile() override {
        std::ofstream file(m_filepath);
        if (!file.is_open()) {
            std::cerr << "Could not open file for writing: " << m_filepath << std::endl;
            return false;
        }
        for (const auto& item : m_data) {
            file << item.toCsv() << std::endl;
        }
        file.close();
        return true;
    }
    bool appendToFile() override {
        std::ofstream file(m_filepath, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Could not open file for appending: " << m_filepath << std::endl;
            return false;
        }
        const auto& item = m_data.back();
        file << item.toCsv() << std::endl;
        file.close();
        return true;
    }
};

#endif // BASECSVREPO_H