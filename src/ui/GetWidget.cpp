#include "GetWidget.h"

GetWidget::GetWidget(){
}


std::string& GetWidget::getString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int GetWidget::getInt(const std::string& prompt){
    int input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

double GetWidget::getDouble(const std::string& prompt) {
    double input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}