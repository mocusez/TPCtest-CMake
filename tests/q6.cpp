#include <iostream>
#include <vector>
#include <string>
#include <numeric>

// 表的头文件，结构体的头文件
#include "Table.h"
#include "Structs.h"
// 扩展的工具函数
#include "Tool.h"

void q6() {
    // begin
    Table<LineItem> lineItemTable;

    lineItemTable.importData("../data/lineitem.tbl");

    // from
    auto& lineitems = lineItemTable.getData();

    double totalRevenue = 0.0;

    // Process each line item
    for (auto& l : lineitems) {
        if (l.L_SHIPDATE >= "1995-01-01" && l.L_SHIPDATE < "1996-01-01" &&
            l.L_DISCOUNT >= (0.02 - 0.01) && l.L_DISCOUNT <= (0.02 + 0.01) &&
            l.L_QUANTITY < 24) {
            totalRevenue += l.L_EXTENDEDPRICE * l.L_DISCOUNT;
        }
    }

    // Output the results
    std::cout << "Total Revenue: " << totalRevenue << std::endl;
}

int main(){
    q6();
}
