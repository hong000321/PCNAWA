/**
 * @file DisplayWidget.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 모든 UI 위젯의 기본 클래스 정의
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <iostream>
#include <vector>
#include <string>

class DisplayWidget {
protected:
    std::vector<DisplayWidget*> m_widgets;

public:
    DisplayWidget();
    ~DisplayWidget();
    
    /**
     * @brief 위젯을 화면에 표시하는 순수 가상 함수
     * @param clear : 화면 지우기 여부 (기본값: true)
     */
    virtual void display(bool clear = true);
    
    /**
     * @brief 화면을 지우는 메서드
     */
    void clearDisplay();
    
    /**
     * @brief 구분선을 표시하는 메서드
     */
    void displaySeperator();
    
    /**
     * @brief 자식 위젯을 추가하는 메서드
     * @param widget : 추가할 위젯 포인터
     */
    void addWidget(DisplayWidget* widget);
    
    /**
     * @brief 지정된 수만큼 줄을 삭제하는 메서드
     * @param count : 삭제할 줄 수
     */
    void deleteLines(int count);
    
    /**
     * @brief 사용자로부터 문자열 입력을 받는 메서드
     * @param prompt : 입력 프롬프트 (기본값: "선택 : ")
     * @return std::string 입력받은 문자열
     */
    std::string getString(const std::string& prompt = "선택 : ");
    
    /**
     * @brief 사용자로부터 정수 입력을 받는 메서드
     * @param prompt : 입력 프롬프트
     * @return int 입력받은 정수
     */
    int getInt(const std::string& prompt);
    
    /**
     * @brief 사용자로부터 실수 입력을 받는 메서드
     * @param prompt : 입력 프롬프트
     * @return double 입력받은 실수
     */
    double getDouble(const std::string& prompt);
};

#endif // DISPLAYWIDGET_H