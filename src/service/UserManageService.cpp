#include "./UserManageService.h"
#include "../models/User.h"
#include "../manager/UserManager.h"
#include "../repository/CsvRepository.h"
#include "../repository/IRepository.h"
#include <ctime>
#include <limits>
UserManageService::UserManageService(){
    std::unique_ptr<IRepository<User>>  repo(new CsvRepository<User>("../../data/user_dummy_data.csv"));
    m_userManager = UserManager(std::move(repo)); // 이동 대입 연산자로 소유권 이전
    m_title = new DisplayTitle("User Management");

    // m_title->pushTitle("User Management");
    m_table = new DisplayTable();
    m_menu = new DisplayMenu();
    addWidget(m_title);
    addWidget(m_table);
    addWidget(m_menu);
}

void UserManageService::start() {
    m_title->pushTitle("User List");
    
    int depth = 0;
    while(1){
        updateMenu(Select_Main_Page);
        updateUserList();
        display(true);
        int select = getInt("선택 : ");
        if(select >= Select_Main_Page.size()){
            printf("invalid select!!! = %d \n",select);
            continue;
        }
        int ret = Select_Main_Page[select].action();
        if(ret==BACK){
            break;
        }
    }
    m_title->popTitle();
    m_title->popTitle();
}

void UserManageService::updateUserList(int page) {
    bool ret = false;
    if(page < 0)
        ret = setUserListByPage(m_currPage);
    else
        ret = setUserListByPage(page);
    if(ret){
        std::cerr << "updateTable Failed";
    }
}

void UserManageService::updateMenu(std::vector<SelectMenu>& page) const {
    if (m_menu) {
        m_menu->setMenu(page);
    }else{
        std::cerr << "Menu is not initialized." << std::endl;
    }
}

bool UserManageService::setUserListByPage(int page){
    if (m_table) {
        int max_lines = (g_max_cmd_table_lines-2);
        int remain_size = m_userManager.getNumOfUser() - page*max_lines;
        if(remain_size>=max_lines){
            remain_size = max_lines;
        }else if(remain_size <= 0){
            return false;
        }
        int start = page*max_lines;
        int end = page*max_lines + remain_size;
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

int UserManageService::updateUserPage(int id){
    User *user = m_userManager.getUserById(id);
    if(user==NULL){
        return FAIL;
    }
    m_strMet.clear();
    m_strMet.push_back({"User ID",std::to_string(id)});
    m_strMet.push_back({"User Name",user->name});
    m_strMet.push_back({"User email",user->email});
    m_strMet.push_back({"User pwd",user->password});
    m_strMet.push_back({"User permission",std::to_string(user->permissionLevel)});
    return OK;
}


int UserManageService::setUserPageById(int id){
    m_title->pushTitle("Edit User");
    int ret = -1;
    
    while(1){
        ret = updateUserPage(id);
        if(ret != OK){
            printf("fail to update user page!!! \n");
        }
        m_table->setMetrixTable(m_strMet);
        updateMenu(Select_User_Page);
        display(true);
        int select = getInt("선택 : ");
        if(select >= Select_User_Page.size()){
            printf("invalid select!!! = %d \n",select);
            continue;
        }
        
        int ret = Select_User_Page[select].action();
        if(ret==BACK){
            break;
        }
    }
    m_title->popTitle();
    return OK;
}

int UserManageService::prevPage(){
    return BACK;
}

int UserManageService::selectUserById(){
    m_currId = getInt("사용자 ID를 입력해주세요 : ");
    if(m_currId<=0){
        return FAIL;
    }
    setUserPageById(m_currId);
    
    return OK;
}

int UserManageService::selectUserByName(){
    std::string name = getString("사용자명을 입력해주세요 : ");
    User *user = m_userManager.getUserByName(name);
    if(user==NULL){
        return FAIL;
    }
    setUserPageById(user->id);
    return OK;
}

int UserManageService::addUser(){
    User user;
    user.id = m_userManager.getLastId()+1;
    user.name = getString("사용자명을 입력해주세요 : ");
    user.email = getString("이메일 주소를 입력해주세요 : ");
    user.password = getString("패스워드를 입력해주세요 : ");
    user.permissionLevel = getInt("사용자 권한을 입력해주세요(User=0, Admin=1, Super=2) : ");
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&now, "%Y-%m-%d");
    user.date = ss.str();
    m_userManager.addUser(user);
    return 0;
}

int UserManageService::delUser(){
    int id = getInt("삭제할 사용자 ID를 입력해주세요 : ");
    m_userManager.deleteUser(id);
    return 0;
}

int UserManageService::nextUserTablePage(){
    updateUserList(++m_currPage);
    return OK;
}

int UserManageService::prevUserTablePage(){
    if(m_currPage==0)
        m_currPage=1;
    updateUserList(--m_currPage);
    return OK;
}

// user page select 
int UserManageService::modifyUser(){
    User *origUser = m_userManager.getUserById(m_currId);
    User user;
    std::string tmpStr;
    user.id = origUser->id;
    
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    tmpStr = "사용자명을 입력해주세요(" + origUser->name + ") -> ";
    user.name = getString(tmpStr);
    tmpStr = "이메일 주소를 입력해주세요(" + origUser->email + ") -> ";
    user.email = getString(tmpStr);
    tmpStr = "패스워드를 입력해주세요(" + origUser->password + ") -> ";
    user.password = getString(tmpStr);
    tmpStr = "사용자 권한을 입력해주세요(User=0, Admin=1, Super=2)(" + std::to_string(origUser->permissionLevel) + ") -> ";
    user.permissionLevel = getInt(tmpStr);
    std::time_t t = std::time(nullptr);
    std::tm now = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&now, "%Y-%m-%d");
    user.date = ss.str();
    m_userManager.updateUser(user);
    return OK;
}

int UserManageService::searchOrder(){
    return 0;
}

int UserManageService::modifyOrder(){
    return 0;
}

int UserManageService::addOrder(){
    return 0;
}

int UserManageService::delOrder(){
    return 0;
}
