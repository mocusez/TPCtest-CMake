#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>


#include "Table.h"
#include "Structs.h"

void q17() {
    // Import 
    Table<Part> partTable;
    Table<LineItem> lineItemTable;

    // Load data
    partTable.importData("../data/part.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // from
    auto& parts = partTable.getData();
    auto& lineItems = lineItemTable.getData();

    // Map to store average quantities for each part
    std::unordered_map<int, double> avgQuantities;

    // First pass
    for (const auto& part : parts) {
        std::vector<double> quantities;
        for (const auto& lineItem : lineItems) {
            if (lineItem.L_PARTKEY == part.P_PARTKEY) {
                quantities.push_back(lineItem.L_QUANTITY);
            }
        }
        if (!quantities.empty()) {
            double avgQuantity = std::accumulate(quantities.begin(), quantities.end(), 0.0) / quantities.size();
            avgQuantities[part.P_PARTKEY] = 0.2 * avgQuantity;
        }
    }

    // Second pass
    double totalExtendedPrice = 0;
    for (const auto& part : parts) {
        if (part.P_BRAND == "Brand#34" && part.P_CONTAINER == "MED CASE") {
            for (const auto& lineItem : lineItems) {
                if (lineItem.L_PARTKEY == part.P_PARTKEY && lineItem.L_QUANTITY < avgQuantities[part.P_PARTKEY]) {
                    totalExtendedPrice += lineItem.L_EXTENDEDPRICE;
                }
            }
        }
    }

    // Calculate average yearly price
    double avgYearly = totalExtendedPrice / 7.0;

    // Output result
    std::cout << "Average Yearly: " << avgYearly << std::endl;
}

int main(){
    q17();
}
