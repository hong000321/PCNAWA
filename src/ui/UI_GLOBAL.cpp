#include "UI_GLOBAL.h"
int g_max_cmd_lines = 50;
int g_max_cmd_width = 150;
int g_max_cmd_title_lines = 3;
int g_max_cmd_table_lines = 25;
int g_max_cmd_menu_lines = g_max_cmd_lines - g_max_cmd_table_lines - g_max_cmd_title_lines - WIDGET_CNT*2;