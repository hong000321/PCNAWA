/**
 * @file DisplayTitle.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 타이틀 표시를 담당하는 위젯 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DISPLAYTITLE_H
#define DISPLAYTITLE_H

#include <iostream>
#include <vector>
#include <string>
#include "DisplayWidget.h"
#include "UI_GLOBAL.h"

class DisplayTitle : public DisplayWidget {
private:
    std::vector<std::string> m_title;

public:
    /**
     * @brief DisplayTitle 생성자
     * @param root : 루트 타이틀 이름 (기본값: "/")
     */
    DisplayTitle(std::string root = "/");
    ~DisplayTitle();

    /**
     * @brief 타이틀을 화면에 표시하는 메서드
     * @param clear : 화면 지우기 여부 (기본값: true)
     */
    void display(bool clear = true) override;
    
    /**
     * @brief 새로운 타이틀을 스택에 추가하는 메서드
     * @param newTitle : 추가할 타이틀 이름
     */
    void pushTitle(const std::string& newTitle);
    
    /**
     * @brief 타이틀 스택에서 마지막 타이틀을 제거하는 메서드
     */
    void popTitle();
    
    /**
     * @brief 모든 타이틀을 지우는 메서드
     */
    void clearTitle();
    
    /**
     * @brief 타이틀 스택의 크기를 반환하는 메서드
     * @return int 타이틀 스택 크기
     */
    int getTitleStackSize();
};

#endif // DISPLAYTITLE_H