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
    
    int m_currPage = 0;

    void displayUserList();
    bool searchUserUI();
    bool updateUserUI();

    bool setPage(int page);

    // select functions
    // select functions
    int prevPage();
    int searchUser();
    int modifyUser();
    int selectUsertById();
    int selectUserByName();
    int addUser();
    int delUser();
    int nextUserTablePage();
    int prevUserTablePage();

    int searchProduct();
    int modifyProduct();
    int addProduct();
    int delProduct();
    int nextProductTablePage();
    int prevProductTablePage();


    std::vector<SelectMenu> Select_Main_Page = {
        {"뒤로가기",       [this]() -> int { return prevPage();}},
        {"유저 선택(이름)",[this]() -> int { return selectUsertById();}},
        {"유저 선택(ID)",  [this]() -> int { return selectUserByName();}},
        {"유저 추가",      [this]() -> int { return addUser();}},
        {"유저 제거",      [this]() -> int { return delUser();}},
        {"이전 페이지",    [this]() -> int { return nextUserTablePage();}},
        {"다음 페이지",    [this]() -> int { return prevUserTablePage();}}
    };
    
    std::vector<SelectMenu> Select_User_Page = {
        {"뒤로가기",        [this]() -> int { return prevPage(); }},
        {"유저 수정",       [this]() -> int { return modifyUser();}},
        {"주문 검색",       [this]() -> int { return searchProduct(); }},
        {"주문 수정",       [this]() -> int { return modifyProduct(); }},
        {"주문 추가",       [this]() -> int { return addProduct(); }},
        {"주문 제거",       [this]() -> int { return delProduct(); }},
        {"이전 페이지",     [this]() -> int { return nextProductTablePage(); }},
        {"다음 페이지",     [this]() -> int { return prevProductTablePage(); }}
    };

    std::vector<SelectMenu> Select_Null_Page = {};

public:

    UserManageService();
    ~UserManageService() = default;

    void start();
    void updateDisplay();
    void updateTable(int page=-1);
    void updateMenu(std::vector<SelectMenu>& page)const;

};



#endif // USERMANAGESERVICE_H