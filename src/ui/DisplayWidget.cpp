#include "DisplayWidget.h"
#include "UI_GLOBAL.h"
#include <string>
#include <sstream>
DisplayWidget::DisplayWidget() {
    // Initialize the widget display
}

DisplayWidget::~DisplayWidget() {
    for (auto& widget : m_widgets) {
        delete widget;
    }
    m_widgets.clear();
}

void DisplayWidget::display(bool clear) {
    if (clear) {
        clearDisplay();
    }
    for (const auto& widget : m_widgets) {
        widget->display(false);
        displaySeperator();
    }
}

void DisplayWidget::clearDisplay() {
    std::cout << "\033[2J\033[1;1H"; // Clear the console
}

void DisplayWidget::displaySeperator() {
    std::cout << std::string(g_max_cmd_width, '=') << std::endl;
}

void DisplayWidget::addWidget(DisplayWidget* widget) {
    m_widgets.push_back(widget);
}

void DisplayWidget::deleteLines(int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << "\033[1A\033[K"; // Move cursor up and clear line
    }
}



std::string DisplayWidget::getString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    
    // 입력 버퍼에 남아있는 개행 문자 제거
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    
    std::getline(std::cin, input);
    return input;

}

int DisplayWidget::getInt(const std::string& prompt){
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        
        try {
            return std::stoi(line);
        } catch (const std::exception&) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
        }
    }
}

double DisplayWidget::getDouble(const std::string& prompt) {
    double input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}