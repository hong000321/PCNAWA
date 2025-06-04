#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <iostream>
#include <vector>
#include <string>
#include "DisplayWidget.h"
#include "UI_GLOBAL.h"

class DisplayMenu : public DisplayWidget {
private:
    std::vector<SelectMenu> m_menu;
public:
    DisplayMenu();
    ~DisplayMenu();

    void display(bool clear = true) override;
    void setMenu(const std::vector<SelectMenu>& menu);
};

#endif // DISPLAYMENU_H

