/**
 * @file CsvRepository.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief CSV 파일을 다루는 Repository 구현체 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

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
    /**
     * @brief CSV 파일에서 데이터를 로드하는 메서드
     * @param path : CSV 파일 경로
     * @return bool 성공 여부
     */
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
                this->m_data.push_back(obj);
            }
            file.close();
        } else {
            std::cerr << "Could not open file: " << path << std::endl;
            return false;
        }
        return true;
    }

public:
    /**
     * @brief CSV Repository 생성자
     * @param path : CSV 파일 경로
     */
    CsvRepository(const std::string& path) : IRepository<T>() {
        this->m_filepath = path;
        loadDataFromFile(this->m_filepath);
    }
    
    /**
     * @brief 전체 데이터를 CSV 파일에 저장하는 메서드
     * @return bool 성공 여부
     */
    bool saveToFile() override {
        std::ofstream file(this->m_filepath);
        if (!file.is_open()) {
            std::cerr << "Could not open file for writing: " << this->m_filepath << std::endl;
            return false;
        }
        for (const auto& item : this->m_data) {
            file << item.toCsv() << std::endl;
        }
        file.close();
        return true;
    }
    
    /**
     * @brief 새로운 데이터를 CSV 파일에 추가하는 메서드
     * @return bool 성공 여부
     */
    bool appendToFile() override {
        std::ofstream file(this->m_filepath, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Could not open file for appending: " << this->m_filepath << std::endl;
            return false;
        }
        const auto& item = this->m_data.back();
        file << item.toCsv() << std::endl;
        file.close();
        return true;
    }
};

#endif // BASECSVREPO_H