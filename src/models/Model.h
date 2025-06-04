#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

struct Model {
public:
    virtual std::string getMemberValueString() const = 0;
    virtual std::string getMemberNameString() const = 0;
};

#endif // MODEL_H