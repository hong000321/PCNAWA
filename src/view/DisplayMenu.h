/**
 * @file DisplayMenu.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 메뉴 표시를 담당하는 위젯 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <iostream>
#include <vector>
#include <string>
#include "DisplayWidget.h"
#include "UI_GLOBAL.h"

class DisplayMenu : public DisplayWidget {
private:
    std::vector<SelectMenu> m_menu;

public:
    DisplayMenu();
    ~DisplayMenu();

    /**
     * @brief 메뉴를 화면에 표시하는 메서드
     * @param clear : 화면 지우기 여부 (기본값: true)
     */
    void display(bool clear = true) override;
    
    /**
     * @brief 메뉴 데이터를 설정하는 메서드
     * @param menu : 설정할 메뉴 데이터 벡터
     */
    void setMenu(const std::vector<SelectMenu>& menu);
};

#endif // DISPLAYMENU_H