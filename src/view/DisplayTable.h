/**
 * @file DisplayTable.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 테이블 형태의 데이터 표시를 담당하는 위젯 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

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

    /**
     * @brief 테이블을 화면에 표시하는 메서드
     * @param clear : 화면 지우기 여부 (기본값: true)
     */
    void display(bool clear = true) override;
    
    /**
     * @brief 테이블 데이터를 설정하는 메서드
     * @param table : 설정할 테이블 데이터 벡터
     */
    void setTable(const std::vector<std::string>& table) {
        m_table = table;
        m_table.resize(g_max_cmd_table_lines);
    }
    
    /**
     * @brief 2차원 배열 형태의 테이블 데이터를 설정하는 메서드
     * @param metTable : 설정할 2차원 테이블 데이터
     */
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

    /**
     * @brief 테이블 데이터를 지우는 메서드
     */
    void clearTable() {
        m_table.clear();
    }
};

#endif // DISPLAYTABLE_H
