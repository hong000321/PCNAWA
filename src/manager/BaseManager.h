#ifndef BASEMANAGER_H
#define BASEMANAGER_H
#include <memory>
#include <vector>
#include <string>

// 공통 베이스 클래스
template<typename T>
class BaseManager {
protected:
    std::unique_ptr<IRepository<T>> m_repo;
    
public:

    // BaseManager() = default;
    
    // 공통 메서드들
    bool add(const T& item) {
         return m_repo->insert(item); 
    }

    bool removeById(int id) {
         return m_repo->removeById(id); 
    }

    bool update(const T& item) {
         return m_repo->update(item); 
    }

    T* getById(int id) {
         return m_repo->getById(id); 
    }

    const std::vector<T> getAll() const {
         return m_repo->getAll(); 
    }

    int getSize() {
         return m_repo->getSize(); 
    }

    int getLastId() {
         return m_repo->lastId(); 
    }

};

#endif //BASEMANAGER_H