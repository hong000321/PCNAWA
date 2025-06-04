#include "DisplayWidget.h"
#include "UI_GLOBAL.h"

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