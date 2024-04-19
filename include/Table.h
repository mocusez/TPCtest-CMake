#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Structs.h"
#include <unordered_map>
/*
 * Table.h
 * 定义一个模板类Table，用于存储数据
    * 该类包含以下成员函数：
    * @setColumnNames : 设置列名
    * @importData: 从文件中导入数据
    * @addRow: 添加一行数据
    * @getData: 获取数据
    * @getColumnNames: 获取列名
*/






// 定义一个模板类Table，用于存储数据
template<typename T>
class Table {
private:
    std::vector<T> data; // 用于存储数据
    std::vector<std::string> columnNames; // 存储列名

    // hash map
    std::unordered_map<int, T> dataMap;
public:
    Table() {}

    // 导入数据
    void importData(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "无法打开文件：" << path << std::endl;
            return;
        }

        std::string line;
        while (getline(file, line)) {
            T t = convertToT<T>(line);
            data.push_back(t);
        }
        file.close();
    }

    // 添加列名
    void setColumnNames(const std::vector<std::string>& names) {
        columnNames = names;
    }

    // 获取数据
    const std::vector<T>& getData() const {
        return data;
    }

    // 获取列名
    const std::vector<std::string>& getColumnNames() const {
        return columnNames;
    }

    // 行列转置

    // 主键索引,key为vector的行号
    const std::unordered_map<int, T> buildIndex() {
        for (int i = 0; i < data.size(); i++) {
            dataMap[i] = data[i];
        }
        return dataMap;
    }

    // 次键索引
    std::unordered_map<int, int> buildIndex(const std::string& columnName) {
        std::unordered_map<int, int> indexMap;
        for (int i = 0; i < data.size(); i++) {
            // 假设getFieldValue能够根据columnName从data[i]中获取对应的字段值
            int fieldValue = data[i].columnName;
            indexMap[fieldValue] = i;
        }
        return indexMap;
    }
};
#endif