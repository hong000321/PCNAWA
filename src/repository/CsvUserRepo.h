#ifndef CSVUSERREPO_H
#define CSVUSERREPO_H
#include "BaseCsvRepo.h"
#include "../struct/User.h"
#include <vector>

class CsvUserRepo : public BaseCsvRepository<User>{
    
public:
    CsvUserRepo(const std::string& path); //
    ~CsvUserRepo();
   
protected:
    bool loadFromFile() override;
    bool saveToFile() override;
    bool appendToFile() override;
};

#endif // CSVUSERREPO_H