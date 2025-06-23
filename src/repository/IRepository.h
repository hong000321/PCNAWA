/**
 * @file IRepository.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 모든 Repository 클래스가 공통으로 사용하는 인터페이스 템플릿 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef IREPOSITORY_H
#define IREPOSITORY_H
#include <vector>
#include <string>
#include <iostream>

template <typename T>
class IRepository {
protected:
    std::vector<T> m_data; // T는 Model(User, Product, Order)
    std::string m_filepath;
    
    /**
     * @brief 파일에서 데이터를 로드하는 순수 가상 함수
     * @param path : 파일 경로
     * @return bool 성공 여부
     */
    virtual bool loadDataFromFile(const std::string& path) = 0;
    
    /**
     * @brief 전체 데이터를 파일에 저장하는 순수 가상 함수
     * @return bool 성공 여부
     */
    virtual bool saveToFile() = 0;
    
    /**
     * @brief 새로운 데이터를 파일에 추가하는 순수 가상 함수
     * @return bool 성공 여부
     */
    virtual bool appendToFile() = 0;
    
public:
    IRepository() = default;
    
    ~IRepository() = default;

    /**
     * @brief 새로운 아이템을 삽입하는 메서드
     * @param item : 삽입할 아이템
     * @return bool 성공 여부
     */
    bool insert(const T& item) {
        m_data.push_back(item);
        appendToFile();
        return true;
    }

    /**
     * @brief 여러 아이템을 한번에 삽입하는 메서드
     * @param items : 삽입할 아이템들의 벡터
     * @return bool 성공 여부
     */
    bool bulkInsert(const std::vector<T>& items) {
        m_data.insert(m_data.end(), items.begin(), items.end());
        saveToFile();
        return true;
    }

    /**
     * @brief 기존 아이템을 업데이트하는 메서드
     * @param item : 업데이트할 아이템
     * @return bool 성공 여부
     */
    bool update(const T& item) {
        for (auto& existingItem : m_data) {
            if (existingItem.id == item.id) {
                existingItem = item;
                saveToFile();
                return true;
            }
        }
        return false;
    }

    /**
     * @brief ID로 아이템을 삭제하는 메서드
     * @param id : 삭제할 아이템의 ID
     * @return bool 성공 여부
     */
    bool removeById(int id) {
        for(auto it=m_data.begin(); it!=m_data.end() ; ++it){
            if(it->id==id){
                m_data.erase(it);
                saveToFile();
                return true;
            }
        }
        return false;
    }

    /**
     * @brief 모든 아이템을 반환하는 메서드
     * @return const std::vector<T>& 모든 아이템의 참조
     */
    const std::vector<T>& getAll() const {
        return m_data;
    }

    /**
     * @brief 범위 내 아이템들을 반환하는 메서드
     * @param start : 시작 인덱스
     * @param end : 끝 인덱스
     * @return std::vector<T> 범위 내 아이템들
     */
    std::vector<T> get(int start, int end) {
        if (start < 0 || end > m_data.size() || start >= end) {
            std::cerr << "Invalid range: start=" << start << ", end=" << end << ", size=" << m_data.size() << std::endl;
            return {};
        }
        return std::vector<T>(m_data.begin() + start, m_data.begin() + end);
    }

    /**
     * @brief ID로 아이템을 검색하는 메서드
     * @param id : 검색할 아이템의 ID
     * @return T* 아이템 포인터 (없으면 nullptr)
     */
    T* getById(int id) {
        for (auto& item : m_data) {
            if (item.id == id) {
                return &item;
            }
        }
        return nullptr;
    }

    /**
     * @brief 모든 아이템을 삭제하는 메서드
     * @return bool 성공 여부
     */
    bool removeAll() {
        m_data.clear();
        saveToFile();
        return true;
    }

    /**
     * @brief 저장된 아이템의 개수를 반환하는 메서드
     * @return int 아이템 개수
     */
    int getSize(){
        return m_data.size();
    }

    /**
     * @brief 마지막 아이템의 ID를 반환하는 메서드
     * @return int 마지막 ID
     */
    int lastId(){
        return m_data.back().id;
    }
};

#endif // IREPOSITORY_H