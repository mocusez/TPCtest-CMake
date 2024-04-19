#include <string>
#include <chrono>
#include <iostream>

int main() {
    int Int;               // 对应 SQL 中的 INT
    float Float;           // 对应 SQL 中的 FLOAT
    double Double;         // 更高精度的浮点数
    char Char;             // 对应 SQL 中的 CHAR
    char CharArray[25];    // 对应固定长度的 CHAR 类型
    std::string String;    // 对应 SQL 中的 VARCHAR

    const std::chrono::time_point now{std::chrono::system_clock::now()};
    const std::chrono::years_days_months ymd{std::chrono::floor<std::chrono::days>(now)};

    return 0;
}

