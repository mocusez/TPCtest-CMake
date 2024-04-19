#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>

// Include the necessary header files
#include "Table.h"
#include "Structs.h"

void q11() {
    // Import
    Table<PartSupp> partSuppTable;
    Table<Supplier> supplierTable;
    Table<Nation> nationTable;

    // Load data
    partSuppTable.importData("../data/partsupp.tbl");
    supplierTable.importData("../data/supplier.tbl");
    nationTable.importData("../data/nation.tbl");

    //from 
    auto& partSupps = partSuppTable.getData();
    auto& suppliers = supplierTable.getData();
    auto& nations = nationTable.getData();

    // where 
    std::unordered_map<int, std::string> nationMap;
    for (const auto& n : nations) {
        nationMap[n.N_NATIONKEY] = n.N_NAME;
    }

    // join
    double totalValue = 0;
    std::unordered_map<int, double> partValues;
    for (const auto& ps : partSupps) {
        for (const auto& s : suppliers) {
            if (ps.PS_SUPPKEY == s.S_SUPPKEY && nationMap[s.S_NATIONKEY] == "SAUDI ARABIA") {
                double value = ps.PS_SUPPLYCOST * ps.PS_AVAILQTY;
                partValues[ps.PS_PARTKEY] += value;
                totalValue += value;
            }
        }
    }

    // Calculate the threshold based on total value
    double threshold = totalValue * 0.0001000000;

    // Filter parts above the threshold
    std::vector<std::pair<int, double>> filteredParts;
    for (const auto& pv : partValues) {
        if (pv.second > threshold) {
            filteredParts.push_back(pv);
        }
    }

    // Sort the results by value descending
    std::sort(filteredParts.begin(), filteredParts.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Output the results
    std::cout << "PartKey\tValue\n";
    for (const auto& res : filteredParts) {
        std::cout << res.first << "\t" << res.second << std::endl;
    }
}

int main(){
    q11();
}

