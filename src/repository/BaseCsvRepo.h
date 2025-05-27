#ifndef BASECSVREPO_H
#define BASECSVREPO_H

#include "IRepository.h"
#include <vector>
#include <string>

template <typename T>
class BaseCsvRepository : public IRepository<T> {
protected:
    std::vector<T> data;
    std::string filepath;

public:
    BaseCsvRepository(const std::string& path) : filepath(path) {
        loadFromFile();
    }

    bool insert(const T& item) override {
        data.push_back(item);
        appendToFile();
    }

    bool bulkInsert(const std::vector<T>& items) override {
        data.insert(data.end(), items.begin(), items.end());
        saveToFile();
    }

    std::vector<T>& getAll() const override {
        return data;
    }

    bool removeId(int id) override {
        for(auto it=data.begin(); it!=data.end() ; ++it){
            if(it->id==id){
                data.erase(it);
                return true;
            }
        }
        return false;
    }

    bool removeAll() override {
        data.clear();
        saveToFile();
    }

protected:
    virtual bool loadFromFile() = 0;
    virtual bool saveToFile() = 0;
    virtual bool appendToFile() = 0;
};

#endif // BASECSVREPO_H