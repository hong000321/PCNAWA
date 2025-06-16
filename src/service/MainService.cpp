#include "./service/UserManageService.h"
#include "./service/ProductManageService.h"
#include "./ui/DisplayTitle.h"
#include "./ui/DisplayMenu.h"
#include "./ui/DisplayWidget.h"
#include "./ui/UI_GLOBAL.h"
#include <windows.h>
#include <iostream>

class MainService : public DisplayWidget {
private:
    DisplayTitle* m_title = nullptr;
    DisplayMenu* m_menu = nullptr;
    
    // 메뉴 선택 함수들
    int exitProgram() {
        std::cout << "프로그램을 종료합니다.\n";
        return BACK;  // 프로그램 종료를 위해 BACK 반환
    }
    
    int startUserManagement() {
        UserManageService* userManageService = new UserManageService();
        userManageService->start();
        delete userManageService;
        return OK;
    }
    
    int startProductManagement() {
        ProductManageService* productManageService = new ProductManageService();
        productManageService->start();
        delete productManageService;
        return OK;
    }

    std::vector<SelectMenu> Select_Main_Menu = {
        {"프로그램 종료",     [this]() -> int { return exitProgram(); }},
        {"사용자 관리",       [this]() -> int { return startUserManagement(); }},
        {"상품 관리",         [this]() -> int { return startProductManagement(); }}
    };

    void updateMenu() {
        if (m_menu) {
            m_menu->setMenu(Select_Main_Menu);
        } else {
            std::cerr << "Menu is not initialized." << std::endl;
        }
    }

public:
    MainService() {
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
        m_menu = new DisplayMenu();
        
        // 위젯 추가
        addWidget(m_title);
        addWidget(m_menu);
    }

    ~MainService() {
        // DisplayWidget의 소멸자에서 자동으로 정리됨
    }

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

int main() {
    MainService* mainService = new MainService();
    mainService->start();
    delete mainService;
    
    return 0;
}