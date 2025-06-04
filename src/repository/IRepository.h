#ifndef IREPOSITORY_H
#define IREPOSITORY_H
#include <vector>
#include <string>

template <typename T>
class IRepository {
protected:
    std::vector<T> m_data;
    std::string m_filepath;
    virtual bool loadDataFromFile(const std::string& path) = 0;
    virtual bool saveToFile() = 0;
    virtual bool appendToFile() = 0;
public:
    IRepository() = default;
    
    ~IRepository() = default;

    bool insert(const T& item) {
        m_data.push_back(item);
        appendToFile();
    }

    bool bulkInsert(const std::vector<T>& items) {
        m_data.insert(m_data.end(), items.begin(), items.end());
        saveToFile();
    }

    bool update(const T& item) {
        for (auto& existingItem : m_data) {
            if (existingItem == item) {
                existingItem = item;
                saveToFile();
                return true;
            }
        }
        return false;
    }

    bool removeById(int id) {
        for(auto it=m_data.begin(); it!=m_data.end() ; ++it){
            if(it->id==id){
                m_data.erase(it);
                return true;
            }
        }
        return false;
    }

    std::vector<T>& getAll() {
        return m_data;
    }

    std::vector<T> get(int start, int end) {
        if (start < 0 || end > m_data.size() || start >= end) {
            std::cerr << "Invalid range: start=" << start << ", end=" << end << ", size=" << m_data.size() << std::endl;
            return {};
        }
        return std::vector<T>(m_data.begin() + start, m_data.begin() + end);
    }

    T* getById(int id) {
        for (auto& item : m_data) {
            if (item.id == id) {
                return &item;
            }
        }
        return nullptr;
    }

    bool removeAll() {
        m_data.clear();
        saveToFile();
    }
};

#endif // IREPOSITORY_H