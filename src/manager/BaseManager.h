/**
 * @file BaseManager.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 모든 Manager 클래스가 공통으로 사용하는 템플릿 베이스 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef BASEMANAGER_H
#define BASEMANAGER_H
#include <memory>
#include <vector>
#include <string>
#include "../repository/IRepository.h"

// 공통 베이스 클래스
template<typename T>
class BaseManager {
protected:
    std::unique_ptr<IRepository<T>> m_repo;
    
public:
    /**
     * @brief 새로운 아이템을 추가
     * @param item 추가할 아이템
     * @return bool 성공 여부
     */
    bool add(const T& item) {
         return m_repo->insert(item); 
    }

    /**
     * @brief ID로 아이템 삭제
     * @param id 삭제할 아이템의 ID
     * @return bool 성공 여부
     */
    bool removeById(int id) {
         return m_repo->removeById(id); 
    }

    /**
     * @brief 아이템 업데이트
     * @param item 업데이트할 아이템
     * @return bool 성공 여부
     */
    bool update(const T& item) {
         return m_repo->update(item); 
    }

    /**
     * @brief ID로 아이템 조회
     * @param id 조회할 아이템의 ID
     * @return T* 아이템 포인터
     */
    T* getById(int id) {
         return m_repo->getById(id); 
    }

    /**
     * @brief 모든 아이템 조회
     * @return const std::vector<T> 모든 아이템 벡터
     */
    const std::vector<T> getAll() const {
         return m_repo->getAll(); 
    }

    /**
     * @brief 저장된 아이템 개수 반환
     * @return int 아이템 개수
     */
    int getSize() {
         return m_repo->getSize(); 
    }

    /**
     * @brief 마지막 ID 반환
     * @return int 마지막 ID
     */
    int getLastId() {
         return m_repo->lastId(); 
    }

};

#endif //BASEMANAGER_H
