#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "Table.h"
#include "Structs.h"

void q16() {
    // Load data from tables
    Table<Part> partTable;
    Table<PartSupp> partsuppTable;
    Table<Supplier> supplierTable;

    partTable.importData("../data/part.tbl");
    partsuppTable.importData("../data/partsupp.tbl");
    supplierTable.importData("../data/supplier.tbl");

    // Get data references
    auto& parts = partTable.getData();
    auto& partsupps = partsuppTable.getData();
    auto& suppliers = supplierTable.getData();

    // Create a set of excluded supplier keys
    std::set<int> excludedSuppliers;
    for (const auto& supplier : suppliers) {
        if (supplier.S_COMMENT.find("Customer Complaints") != std::string::npos) {
            excludedSuppliers.insert(supplier.S_SUPPKEY);
        }
    }

    // Mapping part keys to a vector of supplier keys
    std::map<int, std::vector<int>> partSuppliers;
    for (const auto& ps : partsupps) {
        if (excludedSuppliers.count(ps.PS_SUPPKEY) == 0) {
            partSuppliers[ps.PS_PARTKEY].push_back(ps.PS_SUPPKEY);
        }
    }

    // Structure to hold the grouped results
    struct PartInfo {
        std::string brand;
        std::string type;
        int size;
        std::set<int> suppliers;
    };

    std::map<std::tuple<std::string, std::string, int>, PartInfo> groupedParts;

    // Filtering and grouping parts
    std::set<int> sizes = {21, 39, 18, 28, 31, 32, 48, 45};
    for (const auto& part : parts) {
        if (part.P_BRAND != "Brand#33" &&
            part.P_TYPE.substr(0, 17) != "ECONOMY BURNISHED" &&
            sizes.count(part.P_SIZE) > 0) {
            auto key = std::make_tuple(part.P_BRAND, part.P_TYPE, part.P_SIZE);
            auto& info = groupedParts[key];
            info.brand = part.P_BRAND;
            info.type = part.P_TYPE;
            info.size = part.P_SIZE;
            if (partSuppliers.count(part.P_PARTKEY)) {
                info.suppliers.insert(partSuppliers[part.P_PARTKEY].begin(), partSuppliers[part.P_PARTKEY].end());
            }
        }
    }

    // Preparing results for sorting
    std::vector<std::tuple<std::string, std::string, int, int>> results;
    for (const auto& [key, info] : groupedParts) {
        results.emplace_back(info.brand, info.type, info.size, info.suppliers.size());
    }

    // Sorting results
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return std::tie(std::get<3>(b), std::get<0>(a), std::get<1>(a), std::get<2>(a)) <
               std::tie(std::get<3>(a), std::get<0>(b), std::get<1>(b), std::get<2>(b));
    });

    // Displaying results
    std::cout << "Brand\tType\tSize\tSupplier Count\n";
    for (const auto& result : results) {
        std::cout << std::get<0>(result) << "\t" << std::get<1>(result) << "\t"
                  << std::get<2>(result) << "\t" << std::get<3>(result) << std::endl;
    }
}

int main(){
    q16();
}