#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <iostream>
#include <vector>
#include <string>

class DisplayWidget {
protected:
    std::vector<DisplayWidget*> m_widgets;
public:
    DisplayWidget();
    ~DisplayWidget();
    virtual void display(bool clear = true);
    void clearDisplay();
    void displaySeperator();
    void addWidget(DisplayWidget* widget);
    void deleteLines(int count);

};

#endif // DISPLAYWIDGET_H