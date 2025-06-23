/**
 * @file UserManageService.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 사용자 관리 비즈니스 로직과 UI를 처리하는 서비스 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef USERMANAGESERVICE_H
#define USERMANAGESERVICE_H

#include "../manager/UserManager.h"
#include "../view/DisplayTitle.h"
#include "../view/DisplayMenu.h"
#include "../view/DisplayTable.h"
#include "../view/DisplayWidget.h"

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

    /**
     * @brief 사용자 목록을 업데이트하는 메서드
     * @param page : 페이지 번호 (기본값: -1)
     */
    void updateUserList(int page=-1);
    
    /**
     * @brief 사용자 검색 UI를 처리하는 메서드
     * @return bool 성공 여부
     */
    bool searchUserUI();
    
    /**
     * @brief 사용자 업데이트 UI를 처리하는 메서드
     * @return bool 성공 여부
     */
    bool updateUserUI();

    /**
     * @brief 페이지별 사용자 목록을 설정하는 메서드
     * @param page : 페이지 번호
     * @return bool 성공 여부
     */
    bool setUserListByPage(int page);

    // 메뉴 선택 함수들
    /**
     * @brief 이전 페이지로 이동하는 메서드
     * @return int 상태 코드
     */
    int prevPage();
    
    /**
     * @brief ID로 사용자를 선택하는 메서드
     * @return int 상태 코드
     */
    int selectUserById();
    
    /**
     * @brief 이름으로 사용자를 선택하는 메서드
     * @return int 상태 코드
     */
    int selectUserByName();
    
    /**
     * @brief 새 사용자를 추가하는 메서드
     * @return int 상태 코드
     */
    int addUser();
    
    /**
     * @brief 사용자를 삭제하는 메서드
     * @return int 상태 코드
     */
    int delUser();
    
    /**
     * @brief 사용자 테이블 다음 페이지로 이동하는 메서드
     * @return int 상태 코드
     */
    int nextUserTablePage();
    
    /**
     * @brief 사용자 테이블 이전 페이지로 이동하는 메서드
     * @return int 상태 코드
     */
    int prevUserTablePage();

    /**
     * @brief 사용자 페이지를 업데이트하는 메서드
     * @param id : 사용자 ID
     * @return int 상태 코드
     */
    int updateUserPage(int id);
    
    /**
     * @brief ID로 사용자 페이지를 설정하는 메서드
     * @param id : 사용자 ID
     * @return int 상태 코드
     */
    int setUserPageById(int id);

    /**
     * @brief 사용자 정보를 수정하는 메서드
     * @return int 상태 코드
     */
    int modifyUser();
    
    /**
     * @brief 주문을 검색하는 메서드
     * @return int 상태 코드
     */
    int searchOrder();
    
    /**
     * @brief 주문을 수정하는 메서드
     * @return int 상태 코드
     */
    int modifyOrder();
    
    /**
     * @brief 주문을 추가하는 메서드
     * @return int 상태 코드
     */
    int addOrder();
    
    /**
     * @brief 주문을 삭제하는 메서드
     * @return int 상태 코드
     */
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
    
    /**
     * @brief UserManager 참조를 반환하는 메서드
     * @return UserManager& UserManager 참조
     */
    UserManager& getUserManager() { return m_userManager; }
    
    /**
     * @brief UserManager 상수 참조를 반환하는 메서드
     * @return const UserManager& UserManager 상수 참조
     */
    const UserManager& getUserManager() const { return m_userManager; }

    /**
     * @brief 서비스를 시작하는 메서드
     */
    void start();
    
    /**
     * @brief 메뉴를 업데이트하는 메서드
     * @param page : 메뉴 페이지 벡터 참조
     */
    void updateMenu(std::vector<SelectMenu>& page)const;
};

#endif // USERMANAGESERVICE_H