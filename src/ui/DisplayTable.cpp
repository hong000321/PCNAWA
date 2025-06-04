#include "DisplayTable.h"

DisplayTable::DisplayTable() {
    m_table = std::vector<std::string>(g_max_cmd_table_lines);
}


void DisplayTable::display(bool clear) {
    if (clear) {
        clearDisplay();
    }

    
    // std::cout << "Display Table :" << std::endl;
    
    for (const auto& data : m_table) {
        std::cout << data << std::endl;
    }

    // Display the widgets in the table
    for (const auto& widget : m_widgets) {
        widget->display(false);
        displaySeperator();
    }
}