#ifndef DISPLAYTABLE_H
#define DISPLAYTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include "DisplayWidget.h"
#include "UI_GLOBAL.h"

class DisplayTable : public DisplayWidget {
    std::vector<std::string> m_table;
public:
    DisplayTable();
    ~DisplayTable();

    void display(bool clear = true) override;
    void setTable(const std::vector<std::string>& table) {
        m_table = table;
    }
    void clearTable() {
        m_table.clear();
        m_table.resize(g_max_cmd_table_lines);
    }

};

#endif // DISPLAYTABLE_H
