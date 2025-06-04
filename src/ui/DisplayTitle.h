#ifndef DISPLAYTITLE_H
#define DISPLAYTITLE_H

#include <iostream>
#include <vector>
#include <string>
#include "DisplayWidget.h"
#include "UI_GLOBAL.h"

class DisplayTitle : public DisplayWidget {
private:
    std::vector<std::string> m_title;

    // void displayTitle();
public:
    DisplayTitle(std::string root = "/");
    ~DisplayTitle();

    // using DisplayWidget::display;
    // using DisplayWidget::clearDisplay;
    // using DisplayWidget::addWidget;

    void display(bool clear = true) override;
    void pushTitle(const std::string& newTitle);
    void popTitle();
    void clearTitle();


};

#endif // DISPLAYTITLE_H
