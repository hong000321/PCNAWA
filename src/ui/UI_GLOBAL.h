#ifndef UI_GLOBAL_H
#define UI_GLOBAL_H

#include <vector>
#include <string>
#define WIDGET_CNT 4
extern int g_max_cmd_lines;
extern int g_max_cmd_width;
extern int g_max_cmd_title_lines;
extern int g_max_cmd_table_lines;
extern int g_max_cmd_menu_lines;

struct SelectMenu {
    int menuInt;
    std::string menuStr;
};

#endif // UI_GLOBAL_H