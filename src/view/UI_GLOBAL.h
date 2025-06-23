/**
 * @file UI_GLOBAL.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief text view 출력을 위한 글로벌 설정값 정의
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 * To Do : Singleton Pattern 적용
 */
#ifndef UI_GLOBAL_H
#define UI_GLOBAL_H

#include <vector>
#include <string>
#include <functional>

#define WIDGET_CNT 4

extern int g_max_cmd_lines;
extern int g_max_cmd_width;
extern int g_max_cmd_title_lines;
extern int g_max_cmd_table_lines;
extern int g_max_cmd_menu_lines;

/**
 * @brief 메뉴 선택 시 반환되는 상태 코드 열거형
 */
enum SelectReturn {
    OK,
    BACK,
    FAIL
};

/**
 * @brief 메뉴 아이템 구조체
 */
struct SelectMenu {
    std::string name;                   ///< 메뉴 이름
    std::function<int()> action;        ///< 메뉴 실행 함수
};

#endif // UI_GLOBAL_H