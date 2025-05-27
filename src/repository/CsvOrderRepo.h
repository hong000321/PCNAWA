#ifndef CSVORDERREPO_H
#define CSVORDERREPO_H
#include "BaseCsvRepo.h"
#include "../struct/Order.h"
#include <vector>

class CsvOrderRepo : public BaseCsvRepository<Order>{

public:
    CsvOrderRepo(const std::string& path);
    ~CsvOrderRepo();

protected:
    bool loadFromFile() override;
    bool saveToFile() override;
    bool appendToFile() override;
};


#endif // CSVORDERREPO_H