#ifndef USERMANAGESERVICE_H
#define USERMANAGESERVICE_H

#include "../manager/UserManager.h"
#include "../ui/DisplayTitle.h"
#include "../ui/DisplayMenu.h"
#include "../ui/DisplayTable.h"
#include "../ui/DisplayWidget.h"

#include <map>
#include <vector>

#define USER_CSV_PATH "./user.csv"

class UserManageService : public DisplayWidget {
    // UserManageService는 DisplayWidget을 상속받아 사용자 관리 UI를 구현합니다.
    // 사용자 목록을 표시하고, 사용자 검색, 수정, 추가, 제거 등의 기능을 제공합니다.
    // DisplayWidget을 통해 콘솔 기반의 사용자 인터페이스를 제공합니다.
private:
    UserManager m_userManager;
    DisplayTitle* m_title = nullptr;
    DisplayTable* m_table = nullptr;
    DisplayMenu* m_menu = nullptr;
    void displayUserList();
    bool searchUserUI();
    bool updateUserUI();
public:
    std::vector<SelectMenu> Select_Main_Page = {
        {0,"뒤로가기"},
        {1,"유저 검색"},
        {2,"유저 수정"},
        {3,"유저 주문 목록"},
        {4,"유저 선택"},
        {5,"유저 추가"},
        // {6,"유저 여러 명 추가"},
        {6,"유저 제거"},
        // {7,"유저 여러 명 제거"},
        // {8,"유저 전체 제거"},
        {7,"이전 페이지"},
        {8,"다음 페이지"}
    };
    
    std::vector<SelectMenu> Select_Order_Page = {
        {0,"뒤로가기"},
        {1,"주문 검색"},
        {2,"주문 수정"},
        {3,"주문 추가"},
        {4,"주문 제거"},
        {5,"주문 전체 제거"},
        {6,"유저 주문 목록"},
        {7,"이전 페이지"},
        {8,"다음 페이지"}
    };

    UserManageService();
    ~UserManageService() = default;

    void start();
    void updateDisplay();
    void updateTable(int start, int end);
    void updateMenu(std::vector<SelectMenu>& page)const;
    

};



#endif // USERMANAGESERVICE_H