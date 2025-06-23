/**
 * @file Model.h
 * @author Dae O Hong  (hong000321@gmail.com)
 * @brief 각 모델들이 공통으로 사용하는 함수 정의
 * @version 0.1
 * @date 2025-06-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

struct Model {
public:
    /**
     * @brief 모델의 값들을 cmd 출력에 맞춰 표 형태의 string 으로 반환
     * @return std::string 
     */
    virtual std::string getMemberValueString() const = 0;

    /**
     * @brief 모델의 타이틀들을 cmd 출력에 맞춰 표 형태의 string 으로 반환
     * @return std::string 
     */
    virtual std::string getMemberNameString() const = 0;
    
    /**
     * @brief 멤버 변수를 CSV 형식으로 변환하는 메서드
     * @return std::string 
     */
    virtual std::string toCsv() const = 0;

    /**
     * @brief CSV 형식으로부터 객체를 초기화하는 메서드
     * @param csv : csv에서 받은 로우데이터 string
     */
    virtual void fromCsv(const std::string& csv) = 0;
};

#endif // MODEL_H