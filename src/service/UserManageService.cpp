#include "./UserManageService.h"
#include "../models/User.h"
#include "../manager/UserManager.h"
#include "../repository/CsvRepository.h"
#include "../repository/IRepository.h"

UserManageService::UserManageService(){
    std::unique_ptr<IRepository<User>>  repo(new CsvRepository<User>("../../data/user_dummy_data.csv"));
    m_userManager = UserManager(std::move(repo)); // 이동 대입 연산자로 소유권 이전
    m_title = new DisplayTitle("User Management");
    m_table = new DisplayTable();
    m_menu = new DisplayMenu();
    addWidget(m_title);
    addWidget(m_table);
    addWidget(m_menu);
}

void UserManageService::start() {
    m_title->pushTitle("User List");
    updateMenu(Select_Main_Page);
    updateTable();
    display(true);
    int depth = 0;
    while(1){
        int select = getInt("Select Num : ");
        int ret = Select_Main_Page[select].action();
        if(ret==BACK){
            break;
        }
    }
}

void UserManageService::updateTable(int page) {
    bool ret = false;
    if(page < 0)
        ret = setPage(m_currPage);
    else
        ret = setPage(page);
    if(ret){
        std::cerr << "updateTable Failed";
    }
}

void UserManageService::updateMenu(std::vector<SelectMenu>& page) const {
    // for(auto & item : page){
    //     std::cout << item.menuInt << ". " << item.name << std::endl;
    // }
    if (m_menu) {
        m_menu->setMenu(page);
    }else{
        std::cerr << "Menu is not initialized." << std::endl;
    }
}

bool UserManageService::setPage(int page){
    if (m_table) {
        int remain_size = m_userManager.getNumOfUser() - page*25;
        if(remain_size>=25){
            remain_size = 25;
        }else if(remain_size <= 0){
            return false;
        }
        int start = page*g_max_cmd_table_lines;
        int end = page*g_max_cmd_table_lines + remain_size;
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
        return false;
    }


    return true;
}


// ============================ funcstion of Select ============================
int UserManageService::prevPage(){
    return BACK;
}

int UserManageService::searchUser(){
    return 0;
}

int UserManageService::modifyUser(){
    return 0;
}

int UserManageService::selectUsertById(){
    return 0;
}

int UserManageService::selectUserByName(){
    return 0;
}

int UserManageService::addUser(){
    return 0;
}

int UserManageService::delUser(){
    return 0;
}

int UserManageService::nextUserTablePage(){
    return 0;
}

int UserManageService::prevUserTablePage(){
    return 0;
}

int UserManageService::searchProduct(){
    return 0;
}

int UserManageService::modifyProduct(){
    return 0;
}

int UserManageService::addProduct(){
    return 0;
}

int UserManageService::delProduct(){
    return 0;
}

int UserManageService::nextProductTablePage(){
    return 0;
}

int UserManageService::prevProductTablePage(){
    return 0;
}
