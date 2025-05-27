#ifndef IREPOSITORY_H
#define IREPOSITORY_H
#include <vector>

template <typename T>
class IRepository {
public:

    virtual bool insert(const T& item) = 0;
    virtual bool bulkInsert(const std::vector<T>& items) = 0;
    virtual std::vector<T>& getAll() const = 0;
    virtual bool removeId(int id) = 0;
    virtual bool removeAll() = 0;

    virtual ~IRepository() = default;
};

#endif // IREPOSITORY_H