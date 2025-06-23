/**
 * @file MainService.cpp
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 메인 서비스 클래스 구현체 및 프로그램 진입점
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "./service/UserManageService.h"
#include "./service/ProductManageService.h"
#include "./service/ShopService.h"
#include "./view/DisplayTitle.h"
#include "./view/DisplayTable.h"
#include "./view/DisplayMenu.h"
#include "./view/DisplayWidget.h"
#include "./view/UI_GLOBAL.h"
#include <windows.h>
#include <iostream>

class MainService : public DisplayWidget {
private:
    DisplayTitle* m_title = nullptr;
    DisplayTable* m_table = nullptr;
    DisplayMenu* m_menu = nullptr;
    ProductManageService* m_productManageService = nullptr;  // 전역적으로 관리
    UserManageService* m_userManageService = nullptr;
    ShopService* m_shopService = nullptr;
    
    // 메뉴 선택 함수들
    /**
     * @brief 프로그램을 종료하는 메서드
     * @return int 상태 코드 (BACK)
     */
    int exitProgram() {
        std::cout << "프로그램을 종료합니다.\n";
        return BACK;  // 프로그램 종료를 위해 BACK 반환
    }
    
    /**
     * @brief 사용자 관리 서비스를 시작하는 메서드
     * @return int 상태 코드 (OK)
     */
    int startUserManagement() {
        if (!m_userManageService) {
            m_userManageService = new UserManageService();
        }
        m_userManageService->start();
        
        return OK;
    }
    
    /**
     * @brief 상품 관리 서비스를 시작하는 메서드
     * @return int 상태 코드 (OK)
     */
    int startProductManagement() {
        if (!m_productManageService) {
            m_productManageService = new ProductManageService();
        }
        m_productManageService->start();
        return OK;
    }
    
    /**
     * @brief 쇼핑 서비스를 시작하는 메서드
     * @return int 상태 코드 (OK)
     */
    int startShopService() {
        // ProductManageService가 없으면 먼저 생성
        if (!m_productManageService) {
            m_productManageService = new ProductManageService();
        }
        
        // ShopService 생성 시 ProductManager 참조 전달
        if (!m_shopService) {
            m_shopService = new ShopService(&(m_productManageService->getProductManager()));
        }
        m_shopService->start();
        return OK;
    }

    std::vector<SelectMenu> Select_Main_Menu = {
        {"프로그램 종료",     [this]() -> int { return exitProgram(); }},
        {"사용자 관리",       [this]() -> int { return startUserManagement(); }},
        {"상품 관리",         [this]() -> int { return startProductManagement(); }},
        {"쇼핑몰",         [this]() -> int { return startShopService(); }}
    };

    /**
     * @brief 메인 메뉴를 업데이트하는 메서드
     */
    void updateMenu() {
        if (m_menu) {
            m_menu->setMenu(Select_Main_Menu);
        } else {
            std::cerr << "Menu is not initialized." << std::endl;
        }
    }

public:
    /**
     * @brief MainService 생성자 - 콘솔 환경 설정 및 UI 컴포넌트 초기화
     */
    MainService(){
        // 콘솔 크기 설정
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            g_max_cmd_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            g_max_cmd_lines = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            std::cout << "width: " << g_max_cmd_width << std::endl;
            std::cout << "lines: " << g_max_cmd_lines << std::endl;
        } else {
            std::cerr << "Unable to get console info." << std::endl;
            // 기본값 설정
            g_max_cmd_width = 80;
            g_max_cmd_lines = 25;
        }

        // UI 컴포넌트 초기화
        m_title = new DisplayTitle("관리 시스템");
        m_table = new DisplayTable();
        std::vector<std::string> table;
        table.push_back("______        _   _         _    _\n| ___ \\      | \\ | |       | |  | |\n| |_/ /  ___ |  \\| |  __ _ | |  | |  __ _\n|  __/  / __|| . ` | / _` || |/\\| | / _` |\n| |    | (__ | |\\  || (_| |\\  /\\  /| (_| |\n\\_|     \\___|\\_| \\_/ \\__,_| \\/  \\/  \\__,_|\n");
        m_table->setTable(table);
        m_menu = new DisplayMenu();
        
        // 위젯 추가
        addWidget(m_title);
        addWidget(m_table);
        addWidget(m_menu);
    }

    /**
     * @brief MainService 소멸자 - 동적 할당된 서비스들을 정리
     */
    ~MainService() {
        // ShopService 정리
        if (m_shopService) {
            delete m_shopService;
            m_shopService = nullptr;
        }
        
        // ProductManageService 정리
        if (m_productManageService) {
            delete m_productManageService;
            m_productManageService = nullptr;
        }
        
        if (m_userManageService) {
            delete m_userManageService;
            m_userManageService = nullptr;
        }
        // DisplayWidget의 소멸자에서 자동으로 정리됨
    }

    /**
     * @brief 메인 서비스의 메인 루프를 실행하는 메서드
     */
    void start() {
        m_title->pushTitle("메인 메뉴");
        
        while(true) {
            updateMenu();
            display(true);  // 화면 새로고침
            
            int select = getInt("선택: ");
            
            if(select >= Select_Main_Menu.size()) {
                printf("잘못된 선택입니다!!! = %d \n", select);
                getString("계속하려면 Enter를 누르세요...");
                continue;
            }
            
            int ret = Select_Main_Menu[select].action();
            if(ret == BACK) {
                break;  // 프로그램 종료
            }
        }
        
        m_title->popTitle();
    }
};

/**
 * @brief 프로그램의 진입점
 * @return int 프로그램 종료 코드
 */
int main() {
    MainService* mainService = new MainService();
    mainService->start();
    delete mainService;
    
    return 0;
}