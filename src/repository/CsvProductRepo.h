#ifndef CSVPRODUCTREPO_H
#define CSVPRODUCTREPO_H
#include "BaseCsvRepo.h"
#include "../struct/Product.h"
#include <vector>

class CsvProductRepo : public BaseCsvRepository<Product>{

public:
    CsvProductRepo(const std::string path);
    ~CsvProductRepo();
   
protected:
    bool loadFromFile() override;
    bool saveToFile() override;
    bool appendToFile() override;
}; 

#endif // CSVPRODUCTREPO_H