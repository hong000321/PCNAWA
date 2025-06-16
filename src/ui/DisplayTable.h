#ifndef DISPLAYTABLE_H
#define DISPLAYTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
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
        m_table.resize(g_max_cmd_table_lines);
    }
    void setMetrixTable(const std::vector<std::vector<std::string>>& metTable){
        clearTable();
        for(auto vs : metTable){
            std::stringstream tmpStr;
            tmpStr <<  std::left ;
            for(auto str : vs){
                tmpStr << " |  " << std::setw(15) << str;
            }
            m_table.push_back(tmpStr.str());
        }
        m_table.resize(g_max_cmd_table_lines);
    }

    void clearTable() {
        m_table.clear();
        // m_table.resize(g_max_cmd_table_lines);
    }

};

#endif // DISPLAYTABLE_H
