#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <tuple>
#include <ctime>
#include <limits>

#include "Table.h"
#include "Structs.h"
#include "Tool.h"

bool endsWith(const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void q2() {
    // begin
    Table<Part> partTable;
    Table<Supplier> supplierTable;
    Table<PartSupp> partsuppTable;
    Table<Nation> nationTable;
    Table<Region> regionTable;

    partTable.importData("../data/part.tbl");
    supplierTable.importData("../data/supplier.tbl");
    partsuppTable.importData("../data/partsupp.tbl");
    nationTable.importData("../data/nation.tbl");
    regionTable.importData("../data/region.tbl");

    // time
    clock_t start = clock();
    // from
    auto& parts = partTable.getData();
    auto& suppliers = supplierTable.getData();
    auto& partsupps = partsuppTable.getData();
    auto& nations = nationTable.getData();
    auto& regions = regionTable.getData();

    // Nested subquery to calculate minimum supply cost for Asia
    double minSupplyCost = std::numeric_limits<double>::max();
    for(auto& p: parts) {
        for (auto& ps : partsupps) {
            for (auto& s : suppliers) {
                for (auto& n : nations) {
                    for (auto& r : regions) {
                        if ( p.P_PARTKEY == ps.PS_PARTKEY && ps.PS_PARTKEY == s.S_SUPPKEY && s.S_NATIONKEY == n.N_NATIONKEY &&
                            n.N_REGIONKEY == r.R_REGIONKEY && r.R_NAME == "ASIA") {
                            if (ps.PS_SUPPLYCOST < minSupplyCost) {
                                minSupplyCost = ps.PS_SUPPLYCOST;
                            }
                        }
                    }
                }
            }
        }
    }


    // Filtering and Joining logic
    std::vector<std::tuple<double, std::string, std::string, int, std::string, std::string, std::string, std::string>> results;

    for (auto& p : parts) {
        for (auto& ps : partsupps) {
            for (auto& s : suppliers) {
                for (auto& n : nations) {
                    for (auto& r : regions) {
                        if (p.P_PARTKEY == ps.PS_PARTKEY && s.S_SUPPKEY == ps.PS_SUPPKEY &&
                            p.P_SIZE == 43 && endsWith(p.P_TYPE, "COPPER") &&
                            s.S_NATIONKEY == n.N_NATIONKEY && n.N_REGIONKEY == r.R_REGIONKEY &&
                            r.R_NAME == "ASIA" && ps.PS_SUPPLYCOST == minSupplyCost) {
                            results.emplace_back(s.S_ACCTBAL, s.S_NAME, n.N_NAME, p.P_PARTKEY, p.P_MFGR, s.S_ADDRESS, s.S_PHONE, s.S_COMMENT);
                        }
                    }
                }
            }
        }
    }

    // Ordering the results
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return std::tie(std::get<0>(b), std::get<2>(a), std::get<1>(a), std::get<3>(a)) <
               std::tie(std::get<0>(a), std::get<2>(b), std::get<1>(b), std::get<3>(b));
    });

    // time off
    clock_t stop = clock();
    std::cout << "exe time: " << double(stop - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

    // Print results
    std::cout << "q2 results\n";
    for (auto& item : results) {
        std::cout << std::get<0>(item) << "\t" << std::get<1>(item) << "\t" << std::get<2>(item) << "\t"
                  << std::get<3>(item) << "\t" << std::get<4>(item) << "\t" << std::get<5>(item) << "\t"
                  << std::get<6>(item) << "\t" << std::get<7>(item) << std::endl;
    }
}

int main() {
    q2();
    return 0;
}
