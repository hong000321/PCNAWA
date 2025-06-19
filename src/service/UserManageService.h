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
    int m_currId = 0;
    std::vector<std::vector<std::string>> m_strMet;

    void updateUserList(int page=-1);
    bool searchUserUI();
    bool updateUserUI();

    bool setUserListByPage(int page);

    // select functions
    // select functions
    int prevPage();
    int selectUserById();
    int selectUserByName();
    int addUser();
    int delUser();
    int nextUserTablePage();
    int prevUserTablePage();

    int updateUserPage(int id);
    int setUserPageById(int id);

    int modifyUser();
    int searchOrder();
    int modifyOrder();
    int addOrder();
    int delOrder();


    std::vector<SelectMenu> Select_Main_Page = {
        {"뒤로가기",       [this]() -> int { return prevPage();}},
        {"유저 선택(이름)",[this]() -> int { return selectUserByName();}},
        {"유저 선택(ID)",  [this]() -> int { return selectUserById();}},
        {"유저 추가",      [this]() -> int { return addUser();}},
        {"유저 제거",      [this]() -> int { return delUser();}},
        {"이전 페이지",    [this]() -> int { return prevUserTablePage();}},
        {"다음 페이지",    [this]() -> int { return nextUserTablePage();}}
    };
    
    std::vector<SelectMenu> Select_User_Page = {
        {"뒤로가기",        [this]() -> int { return prevPage(); }},
        {"유저 수정",       [this]() -> int { return modifyUser();}},
        {"주문 검색",       [this]() -> int { return searchOrder(); }},
    };

    std::vector<SelectMenu> Select_Order_Page = {
        {"뒤로가기",        [this]() -> int { return prevPage(); }},
        {"주문 수정",       [this]() -> int { return modifyOrder(); }},
        {"주문 추가",       [this]() -> int { return addOrder(); }},
        {"주문 제거",       [this]() -> int { return delOrder(); }},
    };

    std::vector<SelectMenu> Select_Null_Page = {};

public:

    UserManageService();
    ~UserManageService() = default;
    UserManager& getUserManager() { return m_userManager; }
    const UserManager& getUserManager() const { return m_userManager; }

    void start();
    void updateMenu(std::vector<SelectMenu>& page)const;

};



#endif // USERMANAGESERVICE_H