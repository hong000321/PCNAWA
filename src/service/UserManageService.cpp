#include "./UserManageService.h"
#include "../models/User.h"
#include "../manager/UserManager.h"
#include "../repository/CsvRepository.h"
#include "../repository/IRepository.h"

UserManageService::UserManageService(){
    std::unique_ptr<IRepository<User>>  repo = std::make_unique<CsvRepository<User>>("./data/user_dummy_data.csv");
    m_userManager = UserManager(std::move(repo)); // 이동 대입 연산자로 소유권 이전
    m_title = new DisplayTitle("home");
    m_table = new DisplayTable();
    m_menu = new DisplayMenu();
    addWidget(m_title);
    addWidget(m_table);
    addWidget(m_menu);
}

void UserManageService::start() {
    m_title->pushTitle("User Management");
    m_title->pushTitle("User List");
    updateMenu(Select_Main_Page);
    updateTable(0, g_max_cmd_table_lines);
    display(true);
}

void UserManageService::updateTable(int start, int end) {
    if (m_table) {
        std::vector<std::string> userStrings = m_userManager.getUsersString(start, end);
        if (userStrings.empty()) {
            userStrings.push_back("No users found.");
        }
        std::string separator = std::string(g_max_cmd_width, '-');
        
        std::cout << "width: " << g_max_cmd_width << std::endl;
        std::cout << "lines: " << g_max_cmd_lines << std::endl;
        userStrings.insert(userStrings.begin(), separator);
        userStrings.insert(userStrings.begin(), m_userManager.getUserTitleString());
        
        m_table->setTable(userStrings);
    }else{
        std::cerr << "Table is not initialized." << std::endl;
    }
}

void UserManageService::updateMenu(std::vector<SelectMenu>& page) const {
    // for(auto & item : page){
    //     std::cout << item.menuInt << ". " << item.menuStr << std::endl;
    // }
    if (m_menu) {
        m_menu->setMenu(page);
    }else{
        std::cerr << "Menu is not initialized." << std::endl;
    }
}
