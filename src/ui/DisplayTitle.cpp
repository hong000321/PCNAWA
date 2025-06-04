
#include "DisplayTitle.h"

DisplayTitle::DisplayTitle(std::string root) : DisplayWidget() {    
    m_title = std::vector<std::string>(g_max_cmd_title_lines);
    m_title.clear();
    m_title.push_back(root);
    // m_title = {"Welcome to the Application", "Version 1.0"};
}

void DisplayTitle::display(bool clear) {
    if (clear) {
        clearDisplay();
    }
    int loopCount = 0;
    displaySeperator();
    // std::cout << "Title Display:" << std::endl;
    for(auto& menuName : m_title){
        loopCount++;
        for(int i = 0; i<loopCount; i++){
            std::cout << "    ";
        }
        std::cout << "⊢ " << menuName  << std::endl; //↳►⌞⊢
    }
    // deleteLines(1);

    // Display the widgets in the title
    for (const auto& widget : m_widgets) {
        widget->display(false);
        displaySeperator();
    }
}


void DisplayTitle::pushTitle(const std::string& newTitle) {
    if (m_title.size() < g_max_cmd_title_lines) {
        m_title.push_back(newTitle);
    } else {
        m_title.erase(m_title.begin());
        m_title.push_back(newTitle);
    }
}

void DisplayTitle::popTitle() {
    if (!m_title.empty()) {
        m_title.pop_back();
    }
}

void DisplayTitle::clearTitle() {
    m_title.clear();
    m_title.resize(g_max_cmd_title_lines);
}