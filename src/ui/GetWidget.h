#ifndef TEXTCMDUI_H
#define TEXTCMDUI_H

#include <iostream>
#include <string>
#include <vector>
#include "UI_GLOBAL.h"

class GetWidget {
private:

public:
    GetWidget();
    ~GetWidget() = default;
    GetWidget(const GetWidget&) = delete;
    std::string& getString(const std::string& prompt);
    int getInt(const std::string& prompt);
    double getDouble(const std::string& prompt);
};

#endif // GETWIDGET_H