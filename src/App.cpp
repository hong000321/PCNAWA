#include "./service/UserManageService.h"
#include <windows.h>
#include <iostream>

int main() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        g_max_cmd_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        g_max_cmd_lines = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        std::cout << "width: " << g_max_cmd_width << std::endl;
        std::cout << "lines: " << g_max_cmd_lines << std::endl;
    } else {
        std::cerr << "Unable to get console info." << std::endl;
    }


    UserManageService* userManageService = new UserManageService();
    userManageService->start();
    delete userManageService;
    return 0;
}