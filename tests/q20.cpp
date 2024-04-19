#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include "Table.h"
#include "Structs.h"

void q20() {
    // Loading data
    Table<Supplier> supplierTable;
    Table<Nation> nationTable;
    Table<PartSupp> partsuppTable;
    Table<Part> partTable;
    Table<LineItem> lineItemTable;

    supplierTable.importData("../data/supplier.tbl");
    nationTable.importData("../data/nation.tbl");
    partsuppTable.importData("../data/partsupp.tbl");
    partTable.importData("../data/part.tbl");
    lineItemTable.importData("../data/lineitem.tbl");

    // Get data references
    auto& suppliers = supplierTable.getData();
    auto& nations = nationTable.getData();
    auto& partsupps = partsuppTable.getData();
    auto& parts = partTable.getData();
    auto& lineitems = lineItemTable.getData();

    // Step 1: Identify parts with name starting with 'red'
    std::set<int> redParts;
    for (const auto& part : parts) {
        if (part.P_NAME.substr(0, 3) == "red") {
            redParts.insert(part.P_PARTKEY);
        }
    }

    // Step 2: Calculate quantity requirements from lineitem
    std::map<int, double> requiredQuantities;
    for (const auto& lineitem : lineitems) {
        if (lineitem.L_SHIPDATE >= "1994-01-01" && lineitem.L_SHIPDATE < "1995-01-01" && redParts.count(lineitem.L_PARTKEY)) {
            requiredQuantities[lineitem.L_PARTKEY] += lineitem.L_QUANTITY;
        }
    }

    // Step 3: Identify partsupps that meet the criteria
    std::set<int> qualifiedSuppliers;
    for (const auto& partsupp : partsupps) {
        if (redParts.count(partsupp.PS_PARTKEY) && partsupp.PS_AVAILQTY > 0.5 * requiredQuantities[partsupp.PS_PARTKEY]) {
            qualifiedSuppliers.insert(partsupp.PS_SUPPKEY);
        }
    }

    // Step 4: Identify suppliers in Japan
    int japanKey = -1;
    for (const auto& nation : nations) {
        if (nation.N_NAME == "JAPAN") {
            japanKey = nation.N_NATIONKEY;
            break;
        }
    }

    // Step 5: Collecting final results
    std::vector<std::pair<std::string, std::string>> results;  // Supplier name and address
    for (const auto& supplier : suppliers) {
        if (qualifiedSuppliers.count(supplier.S_SUPPKEY) && supplier.S_NATIONKEY == japanKey) {
            results.push_back({supplier.S_NAME, supplier.S_ADDRESS});
        }
    }

    // Step 6: Sort by supplier name
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    // Output the results
    for (const auto& result : results) {
        std::cout << result.first << ", " << result.second << std::endl;
    }
}

int main(){
    q20();
}