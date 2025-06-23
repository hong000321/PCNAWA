/**
 * @file UserManager.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 사용자 관련 비즈니스 로직을 처리하는 매니저 클래스
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "../repository/CsvRepository.h"
#include "../models/User.h"
#include "BaseManager.h"
#include <memory>
#include <vector>
#include <string>

class UserManager : public BaseManager<User> {
public:
    UserManager() = default;
    UserManager(std::unique_ptr<IRepository<User>> repo);
    
    UserManager& operator=(UserManager&& other) noexcept;
    
    ~UserManager() = default;

    // 복사 절대 불가
    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;

    /**
     * @brief 사용자 목록을 cmd 출력에 맞춰 표 형태의 string 배열로 반환
     * @param start : 시작 인덱스 (기본값: 0)
     * @param end : 끝 인덱스 (기본값: 10)
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getUsersString(int start = 0, int end = 10) const;
    
    /**
     * @brief 사용자 테이블의 타이틀들을 cmd 출력에 맞춰 표 형태의 string으로 반환
     * @return std::string 
     */
    std::string getUserTitleString() const;
    
    /**
     * @brief 이름으로 사용자를 검색하는 메서드
     * @param name : 검색할 사용자 이름
     * @return User* 
     */
    User* getUserByName(const std::string& name);
};

#endif // USERMANAGER_H