#include "DisplayMenu.h"

DisplayMenu::DisplayMenu() {
}

void DisplayMenu::display(bool clear) {
    if (clear) {
        clearDisplay();
    }
    int lineCount = 0;
    std::cout << "Menu Options:" << std::endl;
    for (const auto& menu : m_menu) {
        lineCount++;
        if (menu.menuInt < 0 || menu.menuInt >= g_max_cmd_menu_lines) {
            std::cerr << "Invalid menu option: " << menu.menuInt << std::endl;
            continue;
        }
        std::cout << menu.menuInt << ". " << menu.menuStr << std::endl;

    }
    for(int i = lineCount; i < g_max_cmd_menu_lines; i++) {
        std::cout << std::endl;
    }
    
    // Display the widgets in the menu
    for (const auto& widget : m_widgets) {
        widget->display(false);
        displaySeperator();
    }
}


void DisplayMenu::setMenu(const std::vector<SelectMenu>& menu) {
    m_menu = menu;
}