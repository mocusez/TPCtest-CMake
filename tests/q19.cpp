#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Table.h"
#include "Structs.h"

void q19() {
    // Import the tables
    Table<Part> partTable;
    Table<LineItem> lineItemTable;

    // Load data from files
    partTable.importData("../data/part.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // from
    auto& parts = partTable.getData();


    auto isIn = [](const std::string& value, const std::initializer_list<std::string>& list) {
        return std::find(list.begin(), list.end(), value) != list.end();
    };

    double totalRevenue = 0.0;

    // Process each line item
    for (const auto& lineItem : lineItemTable.getData()){
        for (const auto& part : parts) {
            if (part.P_PARTKEY == lineItem.L_PARTKEY) {
                bool condition1 = part.P_BRAND == "Brand#34" &&
                                  isIn(part.P_CONTAINER, {"SM CASE", "SM BOX", "SM PACK", "SM PKG"}) &&
                                  lineItem.L_QUANTITY >= 10 && lineItem.L_QUANTITY <= 20 &&
                                  part.P_SIZE >= 1 && part.P_SIZE <= 5 &&
                                  isIn(lineItem.L_SHIPMODE, {"AIR", "AIR REG"}) &&
                                  lineItem.L_SHIPINSTRUCT == "DELIVER IN PERSON";

                bool condition2 = part.P_BRAND == "Brand#23" &&
                                  isIn(part.P_CONTAINER, {"MED BAG", "MED BOX", "MED PKG", "MED PACK"}) &&
                                  lineItem.L_QUANTITY >= 19 && lineItem.L_QUANTITY <= 29 &&
                                  part.P_SIZE >= 1 && part.P_SIZE <= 10 &&
                                  isIn(lineItem.L_SHIPMODE, {"AIR", "AIR REG"}) &&
                                  lineItem.L_SHIPINSTRUCT == "DELIVER IN PERSON";

                bool condition3 = part.P_BRAND == "Brand#33" &&
                                  isIn(part.P_CONTAINER, {"LG CASE", "LG BOX", "LG PACK", "LG PKG"}) &&
                                  lineItem.L_QUANTITY >= 30 && lineItem.L_QUANTITY <= 40 &&
                                  part.P_SIZE >= 1 && part.P_SIZE <= 15 &&
                                  isIn(lineItem.L_SHIPMODE, {"AIR", "AIR REG"}) &&
                                  lineItem.L_SHIPINSTRUCT == "DELIVER IN PERSON";

                if (condition1 || condition2 || condition3) {
                    totalRevenue += lineItem.L_EXTENDEDPRICE * (1 - lineItem.L_DISCOUNT);
                }
            }
        }
    }

    // Output total revenue
    std::cout << "Total Revenue: " << totalRevenue << std::endl;
}

int main(){
    q19();
}
